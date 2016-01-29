/****************************************************************************
**
**
****************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "laser_driver.h"
#include "laser_view.h"
#include <QtCore/QtGlobal>

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>

QT_BEGIN_NAMESPACE

class QLabel;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class Console;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void about();
    void writeData(const QByteArray &data);
    void readData();
    void startSimulation();

    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();

private:
    void showStatusMessage(const QString &message);
    Laser_View *laser_viewer;
    Ui::MainWindow *ui;
    QLabel *status;
    Console *console;
    Laser_Driver *laser;
    SettingsDialog *settings;
    QSerialPort *serial;
};

#endif // MAINWINDOW_H
