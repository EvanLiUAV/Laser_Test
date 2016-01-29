/****************************************************************************
**
**
****************************************************************************/

#ifndef CONSOLE_H
#define CONSOLE_H
#include "laser_message.h"
#include <QPlainTextEdit>

class Console : public QPlainTextEdit
{
    Q_OBJECT

signals:
    void getData(const QByteArray &data);

public:
    explicit Console(QWidget *parent = 0);

    void putData(const QByteArray &data);
    void putData(const QString &str);
    void putData(const laser_message &msg);

    void setLocalEchoEnabled(bool set);
    std::string cmd;
protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

private:
    bool localEchoEnabled;
    QScrollBar *bar;
public slots:
    void print_error(int);

};

#endif // CONSOLE_H
