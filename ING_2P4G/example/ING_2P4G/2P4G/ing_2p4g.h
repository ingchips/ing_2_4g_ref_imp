
#ifndef ING__2P4G__H
#define ING__2P4G__H
#include "stdint.h"

typedef enum
{
    MODE_BLE,
    MODE_2G4
} comm_mode_t;

//#define MODE_MASTER         0x0
//#define MODE_SLAVE          0x1

#define LLE_PHY_1M          0x0
#define LLE_PHY_2M          0x1
#define LLE_PHY_CODED_S2    0x2
#define LLE_PHY_CODED_S8    0x3

#define MAX_RX_PAYLOAD_LEN  255


typedef enum
{
    MODE_MASTER,
    MODE_SLAVE
} ing2p4g_work_mode_t;

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
} ing2p4g_work_state_t;

typedef enum
{
    ING2P4G_SUCCESS,            /* <=> Operate success. */
    ING2P4G_MODE_ERROR,         /* <=> It is not in 2.4G/BLE mode. */
    ING2P4G_CRC_ERROR,          /* <=> Received crc value error. */
    ING2P4G_ERROR_TIMEOUT,      /* <=> TX/RX timeout. */
    ING2P4G_ERROR_TX_GOING,     /* <=> TX procedure is going. */
    ING2P4G_ERROR_RX_GOING,     /* <=> RX procedure is going */
    ING2P4G_PARAM_ERROR,        /* <=> Input parameters out of range */
} ing2p4g_status_t;

typedef struct
{
    uint8_t   Mode;             /* <=> Master or Slave */
    uint32_t  AccAddr;          /* <=> Access Address */
    uint8_t   PHY;              /* <=> PHY, 0:1M, 1:2M, 2:Coded S2, 3:Coded S8 */
    uint16_t  Channel;          /* <=> Channel, exp:2402 */
    uint8_t   TXPOW;            /* <=> Tx power idx, 0~63 */
    uint8_t   WhiteEn;          /* <=> white enable, 0 or 1 */
    uint8_t   WhiteIdx;         /* <=> white index, 0~39 */
    uint32_t  CRCInit;          /* <=> CRC initial value, 3Bytes */
    uint32_t  TimeOut;          /* <=> Slave rx timeout, 14Bits, Unit 625us */
    uint8_t   RxPktIntEn;       /* <=> Rx packet intterupt enable */
} ING2P4G_Config_t;

typedef struct
{
    uint8_t   DataLen;
    uint8_t   Data[256];
} ING2P4G_RxPacket;

typedef void (*f_ing2p4g_cb)(void);

/**
 ****************************************************************************************
 * @brief register callback function for ing2.4g event
 *
 * @param[in] type                 The event, see ing2p4g_callback_type_t
 * @param[in] f                    The callback function
 ****************************************************************************************
 */
void ing2p4g_set_irq_callback(ing2p4g_callback_type_t type, f_ing2p4g_cb f);

/**
 ****************************************************************************************
 * @brief clear the rx interrupt flag, used int the callback of rx interrupt
 *
 * @return                     The status of communication
 *                             ING2P4G_SUCCESS          : communication ok
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_clear_rx_int(void);

/**
 ****************************************************************************************
 * @brief clear the event interrupt flag, used int the callback of event interrupt
 *
 * @return                     The status of communication
 *                             ING2P4G_SUCCESS          : communication ok
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_clear_event_int(void);

/**
 ****************************************************************************************
 * @brief get the communication status, if communication over, get the received data
 *
 * @param[out] rxpacket        The pointer to struct to store the received data
 *                             see ING2P4G_RxPacket
 *
 * @return                     The status of communication
 *                             ING2P4G_SUCCESS          : communication ok
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 *                             ING2P4G_CRC_ERROR        : failed, crc error, have received a packet of data, but crc failed
 *                             ING2P4G_ERROR_TIMEOUT    : failed, sync error, didn't receive a packet within excepted time
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_get_rx_data(ING2P4G_RxPacket *rx_packet);

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
ing2p4g_status_t ing2p4g_set_rx_timeout(uint32_t time_out);

/**
 ****************************************************************************************
 * @brief start a RX event for ing2.4g slave, and set the ack data
 * @note  make sure the work mode of 2.4g is MODE_MASETR, or you can set it by ing2p4g_set_2g4_work_mode
 * 
 * @param[in] len              The length of the ack data, should be less than MAX_RX_PAYLOAD_LEN
 *                             if greater than MAX_RX_PAYLOAD_LEN, set to MAX_RX_PAYLOAD_LEN
 * @param[in] data             The pointer to the ack data
 *
 * @retrun                     The result of RX:
 *                             ING2P4G_SUCCESS          : rx success
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 *                             ING2P4G_ERROR_TX_GOING   : failed, for the device is in TX state now
 *                             ING2P4G_ERROR_RX_GOING   : failed, for the device is in RX state now
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_start_2p4g_rx(uint8_t len, uint8_t *data);

/**
 ****************************************************************************************
 * @brief start a TX event for master, and configure the data to be sent
 * @note  make sure the work mode of 2.4g is MODE_MASETR, or you can set it by ing2p4g_set_2g4_work_mode
 * 
 * @param[in] len              The length of the ack data, must be less than MAX_RX_PAYLOAD_LEN
 *                             if greater than MAX_RX_PAYLOAD_LEN, set to MAX_RX_PAYLOAD_LEN
 * @param[in] data             The pointer to the ack data
 *
 * @retrun                     The result of TX:
 *                             ING2P4G_SUCCESS          : tx success
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 *                             ING2P4G_ERROR_TX_GOING   : failed, for the device is in TX state now
 *                             ING2P4G_ERROR_RX_GOING   : failed, for the device is in RX state now
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_start_2p4g_tx(uint8_t len, uint8_t *data);

/**
 ****************************************************************************************
 * @brief set the channel for the master/slave
 *
 * @param[in] Channel          The channel, should be within 2300 to 2500MHz, 1MHz for a step
 *
 * @retrun                     The result of set channel:
 *                             ING2P4G_SUCCESS          : set success
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 *                             ING2P4G_ERROR_TX_GOING   : failed, for the device is in TX state now
 *                             ING2P4G_ERROR_RX_GOING   : failed, for the device is in RX state now
 *                             ING2P4G_PARAM_ERROR      : failed, for param channel out of range
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_set_channel(uint16_t channel);

/**
 ****************************************************************************************
 * @brief set the TX power for the master/slave
 *
 * @param[in] tx_power         The TX power, should be within 0 to 63, 1 for a step
 *                             if tx_power greater than 63, set to 63
 *
 * @retrun                     The result of set TX power:
 *                             ING2P4G_SUCCESS          : set success
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 *                             ING2P4G_ERROR_TX_GOING   : failed, for the device is in TX state now
 *                             ING2P4G_ERROR_RX_GOING   : failed, for the device is in RX state now
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_set_tx_power(uint8_t tx_power);

/**
 ****************************************************************************************
 * @brief set the access address for the master/slave
 *
 * @param[in] AccAddr          The 32 bits access address
 *
 * @retrun                     The result of set access address:
 *                             ING2P4G_SUCCESS          : set success
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 *                             ING2P4G_ERROR_TX_GOING   : failed, for the device is in TX state now
 *                             ING2P4G_ERROR_RX_GOING   : failed, for the device is in RX state now
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_set_access_address(uint32_t access_addr);

/**
 ****************************************************************************************
 * @brief set the phy for the master/slave
 *
 * @param[in] phy              The phy to be set:
 *                             LLE_PHY_1M          0x0
 *                             LLE_PHY_2M          0x1
 *                             LLE_PHY_CODED_S2    0x2
 *                             LLE_PHY_CODED_S8    0x3
 *
 * @retrun                     The result of set phy:
 *                             ING2P4G_SUCCESS          : set success
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 *                             ING2P4G_ERROR_TX_GOING   : failed, for the device is in TX state now
 *                             ING2P4G_ERROR_RX_GOING   : failed, for the device is in RX state now
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_set_phy(uint8_t phy);

/**
 ****************************************************************************************
 * @brief get the state of ing2.4g, reference: ing2p4g_work_state_t
 * @note This function can only be called at 2.4G mode.
 * @param[out] state           The state of ing2p4g:
 *                             ING2P4G_STATE_IDLE       : idle
 *                             ING2P4G_STATE_TX         : TX state
 *                             ING2P4G_STATE_RX         : RX state
 * 
 * @retrun                     The result of get state:
 *                             ING2P4G_SUCCESS          : success
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_get_state(ing2p4g_work_state_t * state);

/**
 ****************************************************************************************
 * @brief switch from BLE to 2.4g
 * @note  Before calling this function, ensure that the BLE is idle (for example, the 
 *        BLE cannot be in the state of broadcast, connection, scan, etc.), otherwise 
 *        the operation will fail. 
 *
 * @param[in] config           The config of 2.4g, see ING2P4G_Config_t
 * 
 * @retrun                     The result of switch:
 *                             ING2P4G_SUCCESS          : success
 *                             ING2P4G_MODE_ERROR       : failed, It is not in BLE mode.
 *
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_switch_to_2G4(ING2P4G_Config_t *config);

/**
 ****************************************************************************************
 * @brief switch to BLE
 * @note  Before calling this function, you must ensure that 2.4G is idle, otherwise, switching to 
 *        BLE mode will fail. See Return value for details. When you successfully switch to BLE mode, 
 *        a HCI_RESET_CMD_OPCODE event is generated, because at the end of this function, btstack_reset() 
 *        is called to reset the ble protocol stack.
 * 
 * @return                     The result of switching to BLE:
 *                             ING2P4G_SUCCESS          : switch success
 *                             ING2P4G_MODE_ERROR       : failed, It is not in 2.4G mode.
 *                             ING2P4G_ERROR_TX_GOING   : failed, for the device is in TX state now
 *                             ING2P4G_ERROR_RX_GOING   : failed, for the device is in RX state now
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_switch_to_BLE(void);

/**
 ****************************************************************************************
 * @brief Init BLE and ing2.4g dual mode. 
 * @note  In 2.4G projects, even if you do not switch to 2.4G mode, this function will be forced to 
 *        initialize so that BLE can work properly. Otherwise, the interrupt system may be corrupted 
 *        because the startup file (startup_ing91600.s) has been changed. 
 ****************************************************************************************
 */
void ing2p4g_init_dual_mode(void);

/**
 ****************************************************************************************
 * @brief get the state of the device, reference: comm_mode_t
 *
 * @retrun                     The result of get state:
 *                             0          : MODE_BLE
 *                             1          : MODE_2G4.
 ****************************************************************************************
 */
uint8_t ing_ble_2p4g_state_get(void);

/**
 ****************************************************************************************
 * @brief get the work mode of the ing2.4g, reference: ing2p4g_work_mode_t
 * @note  It's OK to be called when TX/RX going
 *
 * @param[out] state           The work mode of ing2.4g:
 *                                                    0: MODE_MASTER
 *                                                    1: MODE_SLAVE
 * @return                     The result of reading the work mode of ing2.4g:
 *                             ING2P4G_SUCCESS         : success
 *                             ING2P4G_MODE_ERROR      : failed, It is not in 2.4G mode.
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_get_2g4_work_mode(ing2p4g_work_mode_t *mode);

/**
 ****************************************************************************************
 * @brief set the work mode of the ing2.4g, reference: ing2p4g_work_mode_t
 *
 * @param[in] state            The work mode of ing2.4g:
 *                                                    0: MODE_MASTER
 *                                                    1: MODE_SLAVE
 *                             ING2P4G_STATE_RX        : RX state
 * @return                     The result of reading the work mode of ing2.4g:
 *                             ING2P4G_SUCCESS         : success
 *                             ING2P4G_MODE_ERROR      : failed, It is not in 2.4G mode.
 *                             ING2P4G_ERROR_TX_GOING   : failed, for the device is in TX state now
 *                             ING2P4G_ERROR_RX_GOING   : failed, for the device is in RX state now
 ****************************************************************************************
 */
ing2p4g_status_t ing2p4g_set_2g4_work_mode(ing2p4g_work_mode_t mode);

/**
 ****************************************************************************************
 * @brief listen for the RSSI of a set frequency
 * @note  We could calculate the power with the equation: 
 *                Pdbm = 20*log10(RSSI) - GRX
 *        The RSSI is the output param RSSI
 *        The GRX is a constant decided by the param RX_GAIN
 *             RX_GAIN     0       1     2       3      4       5
 *           GRX(1M phy)  51.0   67.4   79.9   94.4   105.8   117.4
 *           GRX(2M phy)  52.9   69.4   81.9   96.4   107.8   119.4 
 *
 * @param[in]   Freq           the frequency to listen:
 * @param[out]  RSSI           
 * @param[out]  RX_GAIN 
 *                             
 * @return                     The result of reading the work mode of ing2.4g:
 *                             ING2P4G_SUCCESS         : success
 *                             ING2P4G_MODE_ERROR      : failed, It is not in 2.4G mode.
 *                             ING2P4G_ERROR_TX_GOING   : failed, for the device is in TX state now
 *                             ING2P4G_ERROR_RX_GOING   : failed, for the device is in RX state now
 ****************************************************************************************
 */
ing2p4g_status_t RSSI_LISTEN(uint16_t Freq, uint16_t *RSSI, uint16_t *RX_GAIN);
#endif
