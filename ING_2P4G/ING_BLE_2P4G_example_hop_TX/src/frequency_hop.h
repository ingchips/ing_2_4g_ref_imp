#ifndef __TEST_2P4G_H
#define __TEST_2P4G_H

#include "stdint.h"
#include "ing_2p4g.h"

#define APP_2G4_HOP_CHANNEL_NUM        5
#define APP_2G4_HOP_TX_BEGIN_NUM       3

typedef struct
{
    uint16_t     channel_hop[APP_2G4_HOP_CHANNEL_NUM];
    uint16_t     current_channel;
    uint16_t     hop_cnt;
    uint8_t      peer_packet_cnt;
} app_2g4_ch_hop_t;

#endif
