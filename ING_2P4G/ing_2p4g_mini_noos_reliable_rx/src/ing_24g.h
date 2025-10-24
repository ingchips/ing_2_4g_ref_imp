#ifndef _ING_24G_H_
#define _ING_24G_H_

#include "stdint.h"
#include "ing_2p4g.h"

#define PACKET_HEADER_MD_BIT_POS   0x00
#define PACKET_HEADER_SN_BIT_POS   0x01
#define PACKET_HEADER_NESN_BIT_POS 0x02

#define ING24G_HOP_CHANNEL_NUM     6
#define ING24G_HOP_BEGIN_CNT       1
#define ING24G_HOP_STOP_CNT        8

#define PACKET_DATA_SIZE  40
#define PACKET_FIFO_SIZE  40

typedef void (*ing24g_event_cb)(uint8_t event, uint8_t *data, uint8_t len);

typedef enum
{
    ING24G_EVENT_CONNECTING = 0,
    ING24G_EVENT_CONNECTED,
    ING24G_EVENT_DISCONNECT,
    ING24G_EVENT_TX_DONE,
    ING24G_EVENT_RECEIVE,
} ing24g_event_e;

typedef struct 
{
    uint8_t len;
    uint8_t data[PACKET_DATA_SIZE - 1];
} ing24g_packet_ele_t;

typedef struct
{
    ing24g_packet_ele_t packet[PACKET_FIFO_SIZE];
    uint8_t head;
    uint8_t tail;
    uint8_t ready_send;
    uint8_t is_send;
} ing24g_packet_fifo_t;

typedef struct
{
    uint16_t     channel_hop[ING24G_HOP_CHANNEL_NUM];
    uint16_t     current_channel;
    uint16_t     hop_cnt;
    uint8_t      error_cnt;
} ing_24g_ch_hot_t;

typedef enum
{
    ING24G_STATE_IDLE,
    ING24G_STATE_CONNECT,
    ING24G_STATE_COMMNUICATING,
    ING24G_STATE_FRE_HOPPING,
    ING24G_STATE_MAX
} ing24g_state_e;

typedef struct __attribute__((packed)) {
    ing24g_state_e state;
    ing24g_event_cb event_callback;
    uint8_t is_recv_empty;
} ing24g_observed_t;

uint8_t ing24g_send_data(uint8_t *data, uint8_t len);
void ing24g_do_switch_to_2p4g(void);
void ing24g_init(ing24g_event_cb event_cb);

#endif
