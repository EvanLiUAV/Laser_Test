#ifndef LASER_HANDLER_H
#define LASER_HANDLER_H
#include "laser_data_parser.h"
#include "laser_message.h"

class laser_handler
{
public:
    laser_handler();
    bool process_packet(laser_data_message_t *packet,laser_message &msg);
private:
    laser_message laser_msg_buff;
};

#endif // LASER_HANDLER_H
