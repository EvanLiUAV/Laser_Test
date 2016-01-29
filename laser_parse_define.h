#ifndef LASER_PARSE_DEFINE
#define LASER_PARSE_DEFINE

typedef signed char int8_t;
typedef unsigned char   uint8_t;
typedef short  int16_t;
typedef unsigned short  uint16_t;
typedef int  int32_t;
typedef unsigned   uint32_t;
typedef long long  int64_t;
typedef unsigned long long   uint64_t;


#define PACKAGE_STX_FIRST 0xCE//0xCE
#define PACKAGE_STX_SECOND 0xFA//0xFA
#define PACKAGE_STX 64206//0xFACE
#define MAXIMUM_DATA_LENGTH 144//Maximum number of one package

/*********************************************************
 *                    Packet state                       *
 * *******************************************************/
typedef enum {
    LASER_DATA_PACKET_INCOMPLETE=0,
    LASER_DATA_PACKET_OK=1,
    LASER_DATA_PACKET_BAD_CHECK_SUM=2
} laser_data_packet_t;

/*********************************************************
 *            State enum for parsing data                *
 * *******************************************************/
typedef enum {
    LASER_DATA_PARSE_STATE_IDLE=0,
    LASER_DATA_PARSE_STATE_GOT_STX,
    LASER_DATA_PARSE_STATE_GOT_LENGTH,
    LASER_DATA_PARSE_STATE_GOT_BEGIN_ANGLE,
    LASER_DATA_PARSE_STATE_GOT_ALL_DATA
} laser_data_parse_state_t; ///< The state machine for the comm parser

/*********************************************************
 *                Double byte data state                 *
 * *******************************************************/
typedef enum {
    LASER_DATA_FIRSTBYTE=0,
    LASER_DATA_SECONDBYTE
} laser_data_sub_state_t;

/*********************************************************
 *           Struct for saving parsing states            *
 * *******************************************************/

typedef struct {
    uint8_t msg_received;               ///< Number of received messages
    uint8_t parse_error;                ///< Number of parse errors
    laser_data_parse_state_t parse_state;  ///< Parsing state machine
    laser_data_sub_state_t data_sub_state;
    uint16_t packet_idx;
    uint16_t  packet_rx_success_count;   ///< Received packets
    uint16_t  packet_rx_drop_count;      ///< Number of packet drops
} laser_data_status_t;

/*********************************************************
 *                   Laser data struct                   *
 * *******************************************************/
typedef struct{
    uint16_t checksum; ///< Sum of all other data
    uint16_t checksum_ack;
    uint16_t len;     ///< Length of payload
    uint16_t begin_angle;///<Begin angle of this packet
    uint16_t distance[MAXIMUM_DATA_LENGTH];///<Distance data of each measure
} laser_data_message_t;

typedef enum {
    ERROR_BAD_CONNECTION=0,
    ERROR_BAD_DATA,
    ERROR_BAD_FRAME
} error_state_t; ///< The state machine for the comm parser


#endif // LASER_PARSE_DEFINE

