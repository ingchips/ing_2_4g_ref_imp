#include <stdio.h>
#include "platform_api.h"
#include "att_db.h"
#include "gap.h"
#include "btstack_event.h"
#include "btstack_defines.h"
#include "bluetooth_hci.h"
#include "profile.h"

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

#include "../2P4G/ing_2p4g.h"
#include "../2P4G/BLE_2p4g_Switch.h"

#define INVALIDE_HANDLE     0xffff

#define USER_MSG_SWITCH_MODE        1

static uint8_t switching_to_2g4 = 0;
static hci_con_handle_t con_handle = INVALIDE_HANDLE;
static ING2P4G_Config_S ing2p4g_config;

void ing_2p4g_config_init(void)
{
    #if DEF_MASTER
    ing2p4g_config.Mode          = MODE_MASTER;
    #else
    ing2p4g_config.Mode          = MODE_SLAVE;
    #endif
    ing2p4g_config.AccAddr       = 0x12345678;
    ing2p4g_config.PHY           = LLE_PHY_2M;
    ing2p4g_config.Channel       = 2400;
    ing2p4g_config.TXPOW         = 63;
    ing2p4g_config.WhiteEn       = 0x1;
    ing2p4g_config.WhiteIdx      = 0x0;
    ing2p4g_config.CRCInit       = 0x123456;
    ing2p4g_config.TimeOut       = 1600;//10000;//6.25s
    ing2p4g_config.RxPktIntEn    = 1;
    ing2p4g_config.RxPktIntThres = 1;
}
        
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


const static ext_adv_set_en_t adv_sets_en[] = { {.handle = 0, .duration = 0, .max_events = 0} };

static void user_msg_handler(uint32_t msg_id, void *data, uint16_t size)
{
    switch (msg_id)
    {
    case USER_MSG_SWITCH_MODE:
        {
            switch ((comm_mode_t)size)
            {
                case MODE_2G4:
                {
                    BLE_state_type_t state_now = BLE_state_get();
                    switching_to_2g4 = 1;
                    if (state_now == BLE_STATE_ADV)
                        gap_set_ext_adv_enable(0, sizeof(adv_sets_en) / sizeof(adv_sets_en[0]), adv_sets_en);
                    else if(state_now == BLE_STATE_CON)
                    {
                        if (INVALIDE_HANDLE != con_handle)
                            gap_disconnect(con_handle);
                    }
                    else if(state_now == BLE_STATE_IDLE)
                    {}
                    break;
                }
                case MODE_BLE:
                {
                    switch_to_BLE();
                    break;
                }
            }
        }
        break;
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
    gap_set_ext_adv_enable(1, sizeof(adv_sets_en) / sizeof(adv_sets_en[0]), adv_sets_en);
    BLE_state_set(BLE_STATE_ADV);
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
                if (0 == BLE_2p4g_siwtch_get_initializing_state())
                {
                    setup_adv();
                }
                break;
            }
            case HCI_LE_SET_EXT_ADV_EN_CMD_OPCODE:
            {
                if (switching_to_2g4)
                {
                    switching_to_2g4 = 0;
                    switch_to_2G4(&ing2p4g_config);
                }
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
            con_handle = decode_hci_le_meta_event(packet, le_meta_event_enh_create_conn_complete_t)->handle;
            att_set_db(con_handle, profile_data);
            BLE_state_set(BLE_STATE_CON);
            if (switching_to_2g4)
            {
                switching_to_2g4 = 0;
                gap_disconnect(con_handle);
            }
            break;
        case HCI_SUBEVENT_LE_ADVERTISING_SET_TERMINATED:
            if (switching_to_2g4)
            {
                switching_to_2g4 = 0;
                switch_to_2G4(&ing2p4g_config);
            }
            break;
        default:
            break;
        }

        break;

    case HCI_EVENT_DISCONNECTION_COMPLETE:
        con_handle = INVALIDE_HANDLE;
        if (switching_to_2g4 == 0)
        {
            BLE_state_set(BLE_STATE_ADV);
            gap_set_ext_adv_enable(1, sizeof(adv_sets_en) / sizeof(adv_sets_en[0]), adv_sets_en);
        }
        else
        {
            switch_to_2G4(&ing2p4g_config);
        }
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
    ing_2p4g_config_init();

    // Note: security has not been enabled.
    att_server_init(att_read_callback, att_write_callback);
    hci_event_callback_registration.callback = &user_packet_handler;
    hci_add_event_handler(&hci_event_callback_registration);
    att_server_register_packet_handler(&user_packet_handler);
    
    ble_profile_init();
    return 0;
}

void switch_mode(comm_mode_t mode)
{
    btstack_push_user_msg(USER_MSG_SWITCH_MODE, NULL, mode);
}



