/****************************************************************************
**
** Copyright (C) 2012 Denis Shienkov <denis.shienkov@gmail.com>
** Copyright (C) 2012 Laszlo Papp <lpapp@kde.org>
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "console.h"

#include <QScrollBar>

#include <QtCore/QDebug>
#define DOWN_SAMPLE 4
Console::Console(QWidget *parent)
    : QPlainTextEdit(parent)
    , localEchoEnabled(false)
{
    document()->setMaximumBlockCount(100);
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);
    bar = verticalScrollBar();
}

void Console::putData(const QByteArray &data)
{
    insertPlainText(QString(data));

    bar->setValue(bar->maximum());
}

void Console::putData(const QString &str){
    insertPlainText(str);
    bar->setValue(bar->maximum());
}

void Console::putData(const laser_message &msg){
    std::string str;

    str=" Reference Coordinate: ";
    str+=msg.Header.frame;
    str+="\n";
    char buff[15000];
    sprintf(buff," Frame sequence:%ld\n Frame begin angle:%3.1f\n Frame length:%d \n"
            ,msg.Header.seq
            ,msg.Data.angle_min
            ,msg.Data.sample_number);

    str+=buff;
    sprintf(buff,"begin_angle=%3.2f;\n",msg.Data.angle_min);
    cmd=buff;
    sprintf(buff,"angle_increment=%3.2f;\n",msg.Data.angle_increment*DOWN_SAMPLE);
    cmd+=buff;
    cmd+="temp=new Array(";
    for(int i=0;i<msg.Data.sample_number;i++)
    {
        if((i%DOWN_SAMPLE)==0){sprintf(buff,"%3.2f,",msg.Data.ranges.at(i));
        cmd+=buff;}
    }
    cmd.pop_back();
    cmd+=");";
    //qDebug(cmd.c_str());
    str+="\n";
    insertPlainText(QString(str.c_str()));
    bar->setValue(bar->maximum());
}


void Console::setLocalEchoEnabled(bool set)
{
    localEchoEnabled = set;
}

void Console::print_error(int error_type){
    switch (error_type) {
    case ERROR_BAD_CONNECTION:
        insertPlainText(QString("Bad connection condition!"));
        bar->setValue(bar->maximum());
        break;
    default:
        break;
    }
}


void Console::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        break;
    default:
        if (localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
        emit getData(e->text().toLocal8Bit());
    }
}

void Console::mousePressEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    setFocus();
}

void Console::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

void Console::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
