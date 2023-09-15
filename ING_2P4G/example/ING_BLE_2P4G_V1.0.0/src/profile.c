#include <stdio.h>
#include "platform_api.h"
#include "att_db.h"
#include "gap.h"
#include "btstack_event.h"
#include "btstack_defines.h"
#include "bluetooth_hci.h"
#include "profile.h"
#include "TEST_2P4G.h"

// GATT characteristic handles
#include "../data/gatt.const"

const static uint8_t adv_data[] = {
    #include "../data/advertising.adv"
};

#include "../data/advertising.const"

const static uint8_t scan_data[] = {
    #include "../data/scan_response.adv"
};

#include "../data/scan_response.const"

const static uint8_t profile_data[] = {
    #include "../data/gatt.profile"
};


const static ext_adv_set_en_t adv_sets_en[] = { {.handle = 0, .duration = 0, .max_events = 0} };

#define INVALIDE_HANDLE     0xffff

enum
{
    BLE_STA_IDLE = 0x00,
    BLE_STA_ADV  = 0x01,
    BLE_STA_CON  = 0x02,
    BLE_STA_SCAN = 0x04,
};

typedef struct __attribute__((packed)){
    hci_con_handle_t con_handle;
    uint8_t state;
    uint8_t adv_starting;
    uint8_t adv_stopping;
    uint8_t disconn_starting;
    uint8_t switching_to_24g;
    uint8_t switching_to_BLE;
} BleStatus_t;

static BleStatus_t bleSta = {
    .con_handle = INVALIDE_HANDLE,
    .state = BLE_STA_IDLE,
    .adv_starting = 0,
    .adv_stopping = 0,
    .disconn_starting = 0,
    .switching_to_24g = 0,
    .switching_to_BLE = 0,
};

// ================================================================================
// You can use ble_status_set( BLE_STATE_ADV | BLE_STATE_SCAN );
static void ble_status_set(uint8_t sta){
    if (sta == BLE_STA_IDLE){
        bleSta.state = BLE_STA_IDLE;
    } else {
        bleSta.state |= sta;
    }
}

static void ble_status_clear(uint8_t sta){
    bleSta.state &= (~sta);
}

static uint8_t ble_status_get(void){
    return bleSta.state;
}

// ================================================================================
static void ble_adv_set(uint8_t en){
    if (en){
        ble_status_set(BLE_STA_ADV);
        gap_set_ext_adv_enable(1, sizeof(adv_sets_en) / sizeof(adv_sets_en[0]), adv_sets_en);
        bleSta.adv_starting = 1;
    } else {
        gap_set_ext_adv_enable(0, sizeof(adv_sets_en) / sizeof(adv_sets_en[0]), adv_sets_en);
        bleSta.adv_stopping = 1;
    }
}

static void ble_disconn_trigger(void){
    if (INVALIDE_HANDLE != bleSta.con_handle){
        gap_disconnect(bleSta.con_handle);
        bleSta.disconn_starting = 1;
    }
}

// ================================================================================
void ble_switch_to_2p4g_trigger(void){
    platform_printf("%s:%x\n", __func__, ble_status_get());
    if (ble_status_get() == BLE_STA_IDLE){
        ing24g_test_do_switch_to_2p4g();
        return;
    }

    bleSta.switching_to_24g = 1;

    // check advertisement.
    if (ble_status_get() & BLE_STA_ADV){
        // stop advertisement.
        ble_adv_set(0);
    }

    // check connection.
    if(ble_status_get() & BLE_STA_CON){
        // stop connection.
        ble_disconn_trigger();
    }

    // check scan.
    if(ble_status_get() & BLE_STA_SCAN){
        // stop scanning.
    }
}

static uint8_t ble_switch_to_2p4g_check(void){
    platform_printf("%s: %d\n", __func__, bleSta.switching_to_24g);
    if (bleSta.switching_to_24g)
    {
        bleSta.switching_to_24g = 0;
        ing24g_test_do_switch_to_2p4g();
        return 1;
    }
    return 0;
}

static void ble_disconnect_handler(void){
    platform_printf("%s\n", __func__);

    if (bleSta.disconn_starting){
        bleSta.disconn_starting = 0;
        ble_switch_to_2p4g_check();
    } else {
        // start adv.
        ble_adv_set(1);
    }
}

static void ble_connect_handler(uint16_t conn_handle){
    platform_printf("%s\n", __func__);
    if (bleSta.switching_to_24g){
        ble_disconn_trigger();
    }
}

// HCI_SUBEVENT_LE_ADVERTISING_SET_TERMINATED : https://ingchips.github.io/application-notes/pg_ble_stack_cn/ch-adv.html
// Actively stopping the broadcast does not trigger this callback
static void ble_adv_stopped_handler(void){
    platform_printf("%s\n", __func__);
    ble_status_clear(BLE_STA_ADV);
    ble_switch_to_2p4g_check();
}

static void ble_adv_startted_handler(void){
    platform_printf("%s\n", __func__);
    ble_status_set(BLE_STA_ADV);
}

//gap_set_ext_adv_enable cmd send to hci complete will trigger HCI_LE_SET_EXT_ADV_EN_CMD_OPCODE event.
static void ble_adv_set_complete_handler(void){
    platform_printf("%s\n", __func__);
    if (bleSta.adv_stopping){
        bleSta.adv_stopping = 0;
        ble_adv_stopped_handler();
    }
    if (bleSta.adv_starting){
        bleSta.adv_starting = 0;
        ble_adv_startted_handler();
    }
}

static void ble_scan_start_handler(void){
    platform_printf("%s\n", __func__);

}

static void ble_scan_stop_handler(void){
    platform_printf("%s\n", __func__);

}

static void ing2p4g_switch_to_ble_mode_complete(void){
    platform_printf("Switch to BLE mode complete.\n");
    ble_adv_set(1);
}

static void ble_hci_reset_handler(void){
    platform_printf("%s\n", __func__);
    if (bleSta.switching_to_BLE){
        bleSta.switching_to_BLE = 0;
        ing2p4g_switch_to_ble_mode_complete();
    }
}

void ing2p4g_switch_to_ble_mode_start(void){
    bleSta.switching_to_BLE = 1;
}


// ================================================================================
        
static uint16_t att_read_callback(hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t offset,
                                  uint8_t * buffer, uint16_t buffer_size)
{
    switch (att_handle)
    {

    default:
        return 0;
    }
}

static int att_write_callback(hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t transaction_mode,
                              uint16_t offset, const uint8_t *buffer, uint16_t buffer_size)
{
    switch (att_handle)
    {

    default:
        return 0;
    }
}



static void user_msg_handler(uint32_t msg_id, void *data, uint16_t size)
{
    switch (msg_id)
    {
    default:
        ;
    }
}

static void setup_adv(void)
{
    static const bd_addr_t rand_addr = { 0xDD, 0x28, 0x1C, 0xD8, 0x69, 0x67 };
    gap_set_adv_set_random_addr(0, rand_addr);
    gap_set_ext_adv_para(0,
                            CONNECTABLE_ADV_BIT | SCANNABLE_ADV_BIT | LEGACY_PDU_BIT,
                            800, 800,            // Primary_Advertising_Interval_Min, Primary_Advertising_Interval_Max
                            PRIMARY_ADV_ALL_CHANNELS,  // Primary_Advertising_Channel_Map
                            BD_ADDR_TYPE_LE_RANDOM,    // Own_Address_Type
                            BD_ADDR_TYPE_LE_PUBLIC,    // Peer_Address_Type (ignore)
                            NULL,                      // Peer_Address      (ignore)
                            ADV_FILTER_ALLOW_ALL,      // Advertising_Filter_Policy
                            100,                       // Advertising_Tx_Power
                            PHY_1M,                    // Primary_Advertising_PHY
                            0,                         // Secondary_Advertising_Max_Skip
                            PHY_1M,                    // Secondary_Advertising_PHY
                            0x00,                      // Advertising_SID
                            0x00);                     // Scan_Request_Notification_Enable
    gap_set_ext_adv_data(0, sizeof(adv_data), (uint8_t*)adv_data);
    gap_set_ext_scan_response_data(0, sizeof(scan_data), (uint8_t*)scan_data);
    ble_adv_set(1);
}

static void user_packet_handler(uint8_t packet_type, uint16_t channel, const uint8_t *packet, uint16_t size)
{
    
    uint8_t event = hci_event_packet_get_type(packet);
    const btstack_user_msg_t *p_user_msg;
    if (packet_type != HCI_EVENT_PACKET) return;

    switch (event)
    {
    case BTSTACK_EVENT_STATE:
        if (btstack_event_state_get_state(packet) != HCI_STATE_WORKING)
            break;
        
        setup_adv();
        break;

    case HCI_EVENT_COMMAND_COMPLETE:
        switch (hci_event_command_complete_get_command_opcode(packet))
        {
            case HCI_RESET_CMD_OPCODE:            
            {
                ble_status_set(BLE_STA_IDLE);
                ble_hci_reset_handler();
                break;
            }
            case HCI_LE_SET_EXT_ADV_EN_CMD_OPCODE:
            {
                ble_adv_set_complete_handler();
                break;
            }
            default:
                break;
        }
        break;

    case HCI_EVENT_LE_META:
        switch (hci_event_le_meta_get_subevent_code(packet))
        {
        case HCI_SUBEVENT_LE_ENHANCED_CONNECTION_COMPLETE:
            bleSta.con_handle = decode_hci_le_meta_event(packet, le_meta_event_enh_create_conn_complete_t)->handle;
            att_set_db(bleSta.con_handle, profile_data);
            ble_status_set(BLE_STA_CON);
            ble_connect_handler(bleSta.con_handle);
            break;
        case HCI_SUBEVENT_LE_ADVERTISING_SET_TERMINATED:
            ble_adv_stopped_handler();
            break;
        default:
            break;
        }

        break;

    case HCI_EVENT_DISCONNECTION_COMPLETE:
        bleSta.con_handle = INVALIDE_HANDLE;
        ble_status_clear(BLE_STA_CON);
        ble_disconnect_handler();
        break;

    case ATT_EVENT_CAN_SEND_NOW:
        // add your code
        break;

    case BTSTACK_EVENT_USER_MSG:
        p_user_msg = hci_event_packet_get_user_msg(packet);
        user_msg_handler(p_user_msg->msg_id, p_user_msg->data, p_user_msg->len);
        break;

    default:
        break;
    }
}


static btstack_packet_callback_registration_t hci_event_callback_registration;

uint32_t setup_profile(void *data, void *user_data)
{
    platform_printf("setup profile\n");

    // Note: security has not been enabled.
    att_server_init(att_read_callback, att_write_callback);
    hci_event_callback_registration.callback = &user_packet_handler;
    hci_add_event_handler(&hci_event_callback_registration);
    att_server_register_packet_handler(&user_packet_handler);
    return 0;
}
