#include "laser_handler.h"

laser_handler::laser_handler()
{
    laser_msg_buff.Header.frame="laser_base";
    laser_msg_buff.Header.seq=0;
    laser_msg_buff.Data.range_max=0;
    laser_msg_buff.Data.range_min=65535;
    laser_msg_buff.Data.sample_number=0;
}

bool laser_handler::process_packet(laser_data_message_t *packet,laser_message &msg){
    static int packet_num=0;
    bool flag=false;
    /*******************push range imformation in to one frame*******************/
    float range;
    for(int i=0;i<packet->len;i++)
    {
        range=(float)packet->distance[i]/100.0;
        laser_msg_buff.Data.ranges.push_back(range);
        if(range<laser_msg_buff.Data.range_min)laser_msg_buff.Data.range_min=range;
        if(range>laser_msg_buff.Data.range_max)laser_msg_buff.Data.range_max=range;
    }
    /*****************************************************************************/



    packet_num++;//Frame number increase;

    /****************************Begin of one frame*******************************/
    if(packet_num==1)
    {
        laser_msg_buff.Data.angle_min=(float)packet->begin_angle/10.0f;
        return flag;
    }
    /*****************************************************************************/


    /******************************End of one frame*******************************/
    if(packet_num==10)
    {
        packet_num=0;
        laser_msg_buff.Data.angle_max=((float)packet->begin_angle+360.0f)/10.0f;
        laser_msg_buff.Data.sample_number=laser_msg_buff.Data.ranges.size();
        flag=true;
        msg=laser_msg_buff;
        laser_msg_buff.Header.seq++;
        laser_msg_buff.Data.ranges.clear();
        laser_msg_buff.Data.angle_increment=36.0/float(packet->len);
        laser_msg_buff.Data.range_max=0;
        laser_msg_buff.Data.range_min=65535;
        laser_msg_buff.Data.sample_number=0;
        return flag;
    }
    /*****************************************************************************/

    return flag;
}
