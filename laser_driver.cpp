#include "laser_driver.h"

Laser_Driver::Laser_Driver(QObject *parent): QObject(parent)
{
    uart_port=new QSerialPort;
    parser=new Laser_Data_Parser;
    handler=new laser_handler;
    qRegisterMetaType<laser_data_message_t>("laser_data_message_t");
}

Laser_Driver::~Laser_Driver(){
    delete uart_port;
    delete parser;
}

void Laser_Driver::reset(){
    parser->laser_data_status_buffer.data_sub_state=LASER_DATA_FIRSTBYTE;
    parser->laser_data_status_buffer.parse_state=LASER_DATA_PARSE_STATE_IDLE;
    parser->laser_data_status_buffer.parse_error=0;
}

bool Laser_Driver::parse_data(QByteArray buffer,laser_message &mesurement){
    laser_data_message_t msg;
    laser_data_status_t status;

    uint8_t total_number=0;
    for(int i=0;i<buffer.length();i++){
    if(parser->laser_data_parse_char(buffer.at(i),&msg,&status)==LASER_DATA_PACKET_OK)
    {
        Q_EMIT get_laser_packet(msg);
        if(status.parse_error>10)Q_EMIT error_out(ERROR_BAD_CONNECTION);
        total_number++;
        if(handler->process_packet(&msg,mesurement))
        {
        return true;
        }
    }
    }
    return false;
}
