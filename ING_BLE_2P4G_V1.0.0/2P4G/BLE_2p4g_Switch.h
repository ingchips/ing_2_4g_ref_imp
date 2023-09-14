
#ifndef BLE__2P4G__SWITCH__H
#define BLE__2P4G__SWITCH__H
#include "stdint.h"
#include "ing_2p4g.h"

 /****************************************************************************************
 * for the ing2.4g and BLE dual mode 
 * 
 * 
 ****************************************************************************************/
typedef enum
{
    BLE_STATE_IDLE,
    BLE_STATE_ADV,
    BLE_STATE_CON,
    BLE_STATE_SCAN,
} BLE_state_type_t;

typedef enum
{
    MODE_BLE,
    MODE_2G4,
} comm_mode_t;

/**
 ****************************************************************************************
 * @brief  get the state of BLE
 * 
 * @retrun                      the state of BLE, see BLE_state_type_t
 ****************************************************************************************
 */
uint8_t BLE_state_get(void);

/**
 ****************************************************************************************
 * @brief set the state of BLE
 * 
 * @para[in]                    the state to be set, see BLE_state_type_t
 ****************************************************************************************
 */
void BLE_state_set(BLE_state_type_t state);

/**
 ****************************************************************************************
 * @brief get the ble initializing state
 * 
 * @retrun                     the state of whether BLE is initializing
 ****************************************************************************************
 */
uint8_t BLE_2p4g_siwtch_get_initializing_state(void);

/**
 ****************************************************************************************
 * @brief switch from BLE to 2.4g
 *
 * @param[in] config           the config of 2.4g, see ING2P4G_Config_S
 *
 ****************************************************************************************
 */
void switch_to_2G4(ING2P4G_Config_S *config);

/**
 ****************************************************************************************
 * @brief switch to BLE
 * 
 * @return                     the result of switching to BLE:
 *                             0   : switch success
 *                             else: failed, return the state of ing2.4g, see ing2p4g_state_type_t
 ****************************************************************************************
 */
uint8_t switch_to_BLE(void);

/**
 ****************************************************************************************
 * @brief get the state of the device, whether at BLE or ing2.4g
 * 
 * @return                     the state of the device:
 *                             0: BLE
 *                             1: ing2.4g
 ****************************************************************************************
 */
uint8_t ing_ble_2p4g_state_get();

/**
 ****************************************************************************************
 * @brief porfile init when dual mode used, should be called after stack is init
 ****************************************************************************************
 */
void ble_profile_init(void);
#endif
