
#ifndef ING__2P4G__H
#define ING__2P4G__H
#include "stdint.h"

typedef enum
{
    MODE_BLE,
    MODE_2G4,
} comm_mode_t;

#define MODE_MASTER  0x0
#define MODE_SLAVE   0x1

#define LLE_PHY_1M          0x0
#define LLE_PHY_2M          0x1
#define LLE_PHY_CODED_S2    0x2
#define LLE_PHY_CODED_S8    0x3

#define HCLK_frequency      112000000
#define MAX_RX_PAYLOAD_LEN  32

typedef enum
{
    //event callback
    ING2P4G_CB_EVENT,

    //Receive callback
    ING2P4G_CB_RX,

    ING2P4G_CB_EVT_MAX
} ing2p4g_callback_type_t;

typedef enum
{
    ING2P4G_STATE_IDLE,
    ING2P4G_STATE_TX,
    ING2P4G_STATE_RX
} ing2p4g_state_type_t;

typedef struct
{
    uint8_t   Mode;         //Master or Slave
    uint32_t  AccAddr;      //Access Address
    uint8_t   PHY;          //PHY, 0:1M, 1:2M, 2:Coded S2, 3:Coded S8
    uint16_t  Channel;      //Channel, exp:2402
    uint8_t   TXPOW;        //Tx power idx, 0~63
    uint8_t   WhiteEn;      //white enable, 0 or 1
    uint8_t   WhiteIdx;     //white index, 0~39
    uint32_t  CRCInit;      //CRC initial value, 3Bytes
    uint32_t  TimeOut;      //Slave rx timeout, 14Bits, Unit 625us
    uint8_t   RxPktIntEn;   //Rx packet intterupt enable
    uint8_t   RxPktIntThres;//Rx packet intterupt threshold
} ING2P4G_Config_t;

typedef struct
{
    uint8_t   DataLen;        //Data length
    uint8_t   Data[256];      //Data Pointer
} ING2P4G_RxPacket;

typedef void (*f_ing2p4g_cb)(void);

/**
 ****************************************************************************************
 * @brief register callback function for ing2.4g event
 *
 * @param[in] type                 the event, see ing2p4g_callback_type_t
 * @param[in] f                    the callback function
 ****************************************************************************************
 */
void ing2p4g_set_irq_callback(ing2p4g_callback_type_t type, f_ing2p4g_cb f);

/**
 ****************************************************************************************
 * @brief clear the rx interrupt flag, used int the callback of rx interrupt
 ****************************************************************************************
 */
void ing2p4g_clear_rx_int(void);

/**
 ****************************************************************************************
 * @brief clear the event interrupt flag, used int the callback of event interrupt
 ****************************************************************************************
 */
void ing2p4g_clear_event_int(void);

/**
 ****************************************************************************************
 * @brief get the communication status, if communication over, get the received data
 *
 * @param[out] rxpacket        the pointer to struct to store the received data
 *                             see ING2P4G_RxPacket
 *
 * @return                     the status of communication
 *                             0: communication ok
 *                             1: crc error, have received a packet of data, but crc failed
 *                             2: sync error, didn't receive a packet within excepted time
 ****************************************************************************************
 */
uint8_t ing2p4g_get_rx_data(ING2P4G_RxPacket *rx_packet);

/**
 ****************************************************************************************
 * @brief start a RX event for ing2.4g slave, and set the ack data
 *
 * @param[in] len              the length of the ack data, should be less than MAX_RX_PAYLOAD_LEN
 *                             if greater than MAX_RX_PAYLOAD_LEN, set to MAX_RX_PAYLOAD_LEN
 * @param[in] data             the pointer to the ack data
 *
 * @retrun                     the result of RX:
 *                             0: rx success
 *                             1: failed, for the device is in TX state now
 *                             2: failed, for the device is in RX state now
 ****************************************************************************************
 */
uint8_t ing2p4g_start_2p4g_rx(uint8_t len, uint8_t *data);

/**
 ****************************************************************************************
 * @brief start a TX event for master, and configure the data to be sent
 *
 * @param[in] len              the length of the ack data, must be less than MAX_RX_PAYLOAD_LEN
 *                             if greater than MAX_RX_PAYLOAD_LEN, set to MAX_RX_PAYLOAD_LEN
 * @param[in] data             the pointer to the ack data
 *
 * @retrun                     the result of TX:
 *                             0: tx success
 *                             1: failed, for the device is in TX state now
 *                             2: failed, for the device is in RX state now
 ****************************************************************************************
 */
uint8_t ing2p4g_start_2p4g_tx(uint8_t len, uint8_t *data);

/**
 ****************************************************************************************
 * @brief set the channle for the ing2.4g master/slave
 *
 * @param[in] Channel          the channel, should be within 2300 to 2500MHz, 1MHz for a step
 *
 * @retrun                     the result of set channel:
 *                             0: set success
 *                             1: failed, for the device is in TX state now
 *                             2: failed, for the device is in RX state now
 *                             3: failed, for param channel out of range
 ****************************************************************************************
 */
uint8_t ing2p4g_set_channel(uint16_t channel);

/**
 ****************************************************************************************
 * @brief set the TX power for the master/slave
 *
 * @param[in] tx_power         the TX power, should be within 0 to 63, 1 for a step
 *                             if tx_power greater than 63, set to 63
 *
 * @retrun                     the result of set TX power:
 *                             0: set success
 *                             1: failed, for the device is in TX state now
 *                             2: failed, for the device is in RX state now
 ****************************************************************************************
 */
uint8_t ing2p4g_set_tx_power(uint8_t tx_power);

/**
 ****************************************************************************************
 * @brief set the access address for the master/slave
 *
 * @param[in] AccAddr          the 32 bits access address
 *
 * @retrun                     the result of set access address:
 *                             0: set success
 *                             1: failed, for the device is in TX state now
 *                             2: failed, for the device is in RX state now
 ****************************************************************************************
 */
uint8_t ing2p4g_set_access_address(uint32_t access_addr);

/**
 ****************************************************************************************
 * @brief set the phy for the master/slave
 *
 * @param[in] phy              the phy to be set:
 *                             LLE_PHY_1M          0x0
 *                             LLE_PHY_2M          0x1
 *                             LLE_PHY_CODED_S2    0x2
 *                             LLE_PHY_CODED_S8    0x3
 *
 * @retrun                     the result of set phy:
 *                             0: set success
 *                             1: failed, for the device is in TX state now
 *                             2: failed, for the device is in RX state now
 ****************************************************************************************
 */
uint8_t ing2p4g_set_phy(uint8_t phy);

/**
 ****************************************************************************************
 * @brief set timeout for the slave RX event
 *
 * @param[in] time_out         Range:0-10000
 *                             timeout = N*625us(0-6.25s)
 *
 * @retrun                     the result of set timeout:
 *                             0: set success
 *                             1: failed, for the device is in TX state now
 *                             2: failed, for the device is in RX state now
 ****************************************************************************************
 */
uint8_t ing2p4g_set_rx_timeout(uint32_t time_out);

/**
 ****************************************************************************************
 * @brief init BLE and ing2.4g dual mode
 ****************************************************************************************
 */
void ing2p4g_init_dual_mode(void);

/**
 ****************************************************************************************
 * @brief get the state of ing2.4g
 *
 * @retrun                     the state of ing2p4g:
 *                             0: idle
 *                             1: TX state
 *                             2: RX state
 ****************************************************************************************
 */
uint8_t ing2p4g_get_state(void);

/**
 ****************************************************************************************
 * @brief switch from BLE to 2.4g
 *
 * @param[in] config           the config of 2.4g, see ING2P4G_Config_t
 *
 ****************************************************************************************
 */
void ing2p4g_switch_to_2G4(ING2P4G_Config_t *config);

/**
 ****************************************************************************************
 * @brief switch to BLE
 * 
 * @return                     the result of switching to BLE:
 *                             0   : switch success
 *                             else: failed, return the state of ing2.4g, see ing2p4g_state_type_t
 ****************************************************************************************
 */
uint8_t ing2p4g_switch_to_BLE(void);

#endif
