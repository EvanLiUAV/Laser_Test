/****************************************************
 *                     Qt Driver                    *
 ****************************************************/
#ifndef LASER_DRIVER_H
#define LASER_DRIVER_H
#include "laser_data_parser.h"
#include "laser_handler.h"
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>




class Laser_Driver : public QObject
{
    Q_OBJECT
public:
    explicit Laser_Driver(QObject *parent = 0);
    ~Laser_Driver();
    QSerialPort *uart_port;
    bool parse_data(QByteArray buffer,laser_message &mesurement);
    void reset();

private:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };
    laser_handler *handler;
    Laser_Data_Parser *parser;
Q_SIGNALS:
    void get_laser_packet(laser_data_message_t msg);
    void error_out(int);

};

#endif // LASER_DRIVER_H
