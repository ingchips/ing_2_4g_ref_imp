#include "uart_console.h"

#include "ingsoc.h"

#include <stdio.h>
#include <string.h>

#include "platform_api.h"
#include "bluetooth.h"
#include "sm.h"

#include "btstack_mt.h"
#include "port_gen_os_driver.h"

#include "ing_2p4g.h"
#include "TEST_2P4G.h"

#include "profile.h"

#define GEN_OS          ((const gen_os_driver_t *)platform_get_gen_os_driver())

#ifdef TRACE_TO_FLASH
#include "trace.h"
#endif

typedef void (*f_cmd_handler)(const char *param);

int adv_tx_power = 100;

typedef struct
{
    const char *cmd;
    f_cmd_handler handler;
} cmd_t;

const static char error[] = "error";
static char buffer[100] = {0};

static void tx_data(const char *d, const uint16_t len);

static const char help[] =  "commands:\n"
                            "h/?                                 show this\n"
                            "ble                                 switch to ble\n"
                            "2g4                                 switch to 2.4g\n"
                            "state                               get 2.4g state\n"
                            "mode                                get 2.4g work mode\n"
                            "phy                                 set phy\n"
                            "aa                                  set access address\n"
                            "power                               set tx power\n"
                            "channel                             set channel\n"
                            "txcon                               2.4g tx continus\n"
                            "txone                               tx one packet with x payload\n"
                            "stopcon                             stop 2.4g continus tx/rx\n"
                            "rxcon                               2.4g rx contiuns\n"
                            "rxone                               rx one packet with x payload\n"
                            "timeout                             set rx timeout\n"
                            "rxdata                              get rx data\n"
                            "rxint                               clear rx interrupt\n"
                            "eventint                            clear tx interrupt\n"
                            ;

void cmd_help(const char *param)
{
    tx_data(help, strlen(help) + 1);
}

void cmd_switch_to_ble(const char *param)
{
    continus_2g4_txrx_off();
    ing24g_test_switch_mode_trigger(MODE_BLE);
}

void cmd_switch_to_2g4(const char *param)
{
    ing24g_test_switch_mode_trigger(MODE_2G4);
}

void cmd_get_2g4_state(const char *param)
{
    ing2p4g_work_state_t state;
    ing2p4g_status_t return_state;
    return_state = ing2p4g_get_state(&state);
    if(return_state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2g4 state.\r\n");
        return;
    }
    switch(state)
    {
        case 0:
            platform_printf("ING2P4G_STATE_IDLE.\r\n");
            break;
        case 1:
            platform_printf("ING2P4G_STATE_TX.\r\n");
            break;
        case 2:
            platform_printf("ING2P4G_STATE_RX.\r\n");
            break;
        default:
            platform_printf("Unknown ing2p4g state.\r\n");
            break;
    }
}

void cmd_get_2g4_work_mode(const char *param)
{
    ing2p4g_status_t state;
    ing2p4g_work_mode_t mode;
    state = ing2p4g_get_2g4_work_mode(&mode);
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2g4 state.\r\n");
        return;
    }
    switch(mode)
    {
        case 0:
            platform_printf("Work mode Master.\r\n");
            break;
        case 1:
            platform_printf("Work mode Slave.\r\n");
            break;
        default:
            platform_printf("Unknown ing2p4g work Mode.\r\n");
            break;
    }
}

void cmd_phy_set(const char *param)
{
    static uint8_t phy = 1;
    ing2p4g_status_t state;
    state = ing2p4g_set_phy(phy);
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
    }
    else
    {
        platform_printf("phy:%d set result:%d.\r\n", phy, state);
        if(state == ING2P4G_SUCCESS)
            phy = (phy ? 0:1);
    }
}

void cmd_access_address_set(const char *param)
{
    static uint32_t aa = 0x12345611;
    ing2p4g_status_t state;
    state = ing2p4g_set_access_address(aa);
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
    }
    else
    {
        platform_printf("aa:%4x set result:%d.\r\n", aa, state);
        if(state == ING2P4G_SUCCESS)
            aa += 0x10;
    }
}

void cmd_power_set(const char *param)
{
    ing2p4g_status_t state;
    static uint8_t power = 65;
    state = ing2p4g_set_tx_power(power);
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
    }
    else
    {
        platform_printf("power:%d set resutl:%d.\r\n", power, state);
        if(state == ING2P4G_SUCCESS)
            power -= 10;
    }
}

void cmd_channel_set(const char *param)
{
    ing2p4g_status_t state;
    static uint16_t channel = 2380;
    state = ing2p4g_set_channel(channel);
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
    }
    else
    {
        platform_printf("channel: %d set result:%d.\r\n", channel, state);
        if(state == ING2P4G_SUCCESS)
            channel += 5;
    }
}

void cmd_rx_timeout_set(const char *param)
{
    ing2p4g_status_t state;
    static uint32_t timeout = 1000;
    state = ing2p4g_set_rx_timeout(timeout);
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
    }
    else
    {
        platform_printf("timeout:%d set result:%d\r\n", timeout, state);
        if(state == ING2P4G_SUCCESS)
            timeout += 1000;
    }
}

void cmd_rx_data_get(const char *param)
{
    ing2p4g_status_t state;
    uint16_t i;
    static ING2P4G_RxPacket rx_packet;
    state = ing2p4g_get_rx_data(&rx_packet);
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
        return;
    }
    if(state == ING2P4G_SUCCESS)
    {
        platform_printf("Rx data:");
        for(i=0; i< rx_packet.DataLen; i++)
            platform_printf("%d ",rx_packet.Data[i]);
        platform_printf(".\r\n");
    }
    else
    {
        platform_printf("data get failed:%d.\r\n", state);
    }
}

void cmd_rx_interrupt_clear(const char *param)
{
    ing2p4g_status_t state = ing2p4g_clear_rx_int();
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
    }
    else
    {
        platform_printf("rx clear:%d.\r\n", state);
    }
}

void cmd_event_interrupt_clear(const char *param)
{
    ing2p4g_status_t state = ing2p4g_clear_event_int();
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
    }
    else
    {
        platform_printf("event clear:%d.\r\n", state);
    }
}

static uint8_t ing2g4_tx_data[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}; 
static uint8_t rx_data[256];
static uint8_t ing2g4_len = 10;
static ING2P4G_RxPacket RxPkt111;
extern uint8_t continus_2g4;
static uint32_t test_tick_us[4];
void cmd_tx_one_packet(const char *param)
{
    ing2p4g_status_t state;
    ing2p4g_set_2g4_work_mode(MODE_MASTER);
    test_tick_us[0] = platform_get_us_time();
    if(test_master_ack_get())
    {
        state = ing2p4g_start_2p4g_tx(ing2g4_len, ing2g4_tx_data);
    }
    else{
        ing2p4g_start_2p4g_tx_noack(ing2g4_len, ing2g4_tx_data);
    }
    test_tick_us[1] = platform_get_us_time();
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
    }
    else
    {
        platform_printf("tx result:%d, tx:%dus.\r\n", state, test_tick_us[1]-test_tick_us[0]);
    }
}

void cmd_tx_continus(const char *param)
{
    ing2p4g_status_t state;
    ing2p4g_set_2g4_work_mode(MODE_MASTER);
    continus_2g4_txrx_on();
    // gpio_pluse_num1(1);
    if(test_master_ack_get())
    {
        state = ing2p4g_start_2p4g_tx(ing2g4_len, ing2g4_tx_data);
    }
    else{
        ing2p4g_start_2p4g_tx_noack(ing2g4_len, ing2g4_tx_data);
    }
    // if(state == ING2P4G_MODE_ERROR)
    // {
    //     platform_printf("Not in 2.4g mode.\r\n");
    // }
    // else
    // {
    //     platform_printf("tx continus result:%d.\r\n", state);
    //     if(state != ING2P4G_SUCCESS)
    //     {
    //         continus_2g4_txrx_off();    
    //     }
    // }
}

void cmd_rx_one_packet(const char *param)
{
    ing2p4g_status_t state;
    ing2p4g_set_2g4_work_mode(MODE_SLAVE);
    test_tick_us[2] = platform_get_us_time();
    if(test_slave_ack_get())
    {
        state = ing2p4g_start_2p4g_rx(ing2g4_len, ing2g4_tx_data);
    }
    else{
        state = ing2p4g_start_2p4g_rx_noack();
    }
    test_tick_us[3] = platform_get_us_time();
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
    }
    else
    {
        platform_printf("rx result:%d, rx:%dus.\r\n", state, test_tick_us[3]-test_tick_us[2]);
    }
}

void cmd_rx_continus(const char *param)
{
    ing2p4g_status_t state;
    ing2p4g_set_2g4_work_mode(MODE_SLAVE);
    continus_2g4_txrx_on();
    if(test_slave_ack_get())
    {
        state = ing2p4g_start_2p4g_rx(ing2g4_len, ing2g4_tx_data);
    }
    else{
        state = ing2p4g_start_2p4g_rx_noack();
    }
    if(state == ING2P4G_MODE_ERROR)
    {
        platform_printf("Not in 2.4g mode.\r\n");
    }
    else
    {
        platform_printf("rx continus result:%d.\r\n", state);
        if(state != ING2P4G_SUCCESS)
        {
            continus_2g4_txrx_off();    
        }
    }
}

void cmd_stop_continus(const char *param)
{
    if(ing_ble_2p4g_state_get() == 0)
    {
        platform_printf("Not in 2.4g mode.\r\n");
        return;
    }
    else
    {
        continus_2g4_txrx_off();
        platform_printf("stop continus.\r\n");
    }
    
}


void cmd_shutdown(const char *param)
{
    platform_printf("shutdown\r\n");
    GIO_EnableRetentionGroupB(1);
    platform_shutdown(0, NULL, 0);
}



void cmd_test_inst1(const char *param)
{
    static uint8_t master_ack_en = 0;
    test_master_ack_en(master_ack_en);
    platform_printf("master ack:%d\n", master_ack_en);
    master_ack_en = !master_ack_en;
}

void cmd_test_inst2(const char *param)
{
    static uint8_t slave_ack_en = 0;
    test_slave_ack_en(slave_ack_en);
    platform_printf("slave ack:%d\n", slave_ack_en);
    slave_ack_en = !slave_ack_en;
}


static cmd_t cmds[] =
{
    {
        .cmd = "h",
        .handler = cmd_help
    },
    {
        .cmd = "?",
        .handler = cmd_help
    },
    {
        .cmd = "ble",
        .handler = cmd_switch_to_ble
    },
    {
        .cmd = "2g4",
        .handler = cmd_switch_to_2g4
    },
    {
        .cmd = "state",
        .handler = cmd_get_2g4_state
    },    
    {
        .cmd = "mode",
        .handler = cmd_get_2g4_work_mode
    },
    {
        .cmd = "phy",
        .handler = cmd_phy_set
    },
    {
        .cmd = "aa",
        .handler = cmd_access_address_set
    },
    {
        .cmd = "power",
        .handler = cmd_power_set
    },
    {
        .cmd = "channel",
        .handler = cmd_channel_set
    },
    {
        .cmd = "txone",
        .handler = cmd_tx_one_packet
    },
    {
        .cmd = "txcon",
        .handler = cmd_tx_continus
    },
    {
        .cmd = "rxone",
        .handler = cmd_rx_one_packet
    },
    {
        .cmd = "rxcon",
        .handler = cmd_rx_continus
    },
    {
        .cmd = "stopcon",
        .handler = cmd_stop_continus
    },
    {
        .cmd = "timeout",
        .handler = cmd_rx_timeout_set
    },
    {
        .cmd = "rxdata",
        .handler = cmd_rx_data_get
    },
    {
        .cmd = "rxint",
        .handler = cmd_rx_interrupt_clear
    },
    {
        .cmd = "eventint",
        .handler = cmd_event_interrupt_clear
    },
    {
        .cmd = "test1",
        .handler = cmd_test_inst1
    },
    {
        .cmd = "test2",
        .handler = cmd_test_inst2
    },
    {
        .cmd = "shutdown",
        .handler = cmd_shutdown
    }
};

void handle_command(char *cmd_line)
{
    static const char unknow_cmd[] =  "unknown command\n";
    char *param = cmd_line;
    int i;
    while (*param)
    {
        if (*param == ' ')
        {
            *param = '\0';
            param++;
            break;
        }
        else
            param++;
    }

    for (i = 0; i < sizeof(cmds) / sizeof(cmds[0]); i++)
    {
        if (strcasecmp(cmds[i].cmd, cmd_line) == 0)
            break;
    }
    if (i >= sizeof(cmds) / sizeof(cmds[0]))
        goto show_help;

    cmds[i].handler(param);
    return;

show_help:
    tx_data(unknow_cmd, strlen(unknow_cmd) + 1);
    cmd_help(NULL);
}

typedef struct
{
    uint8_t busy;
    uint16_t size;
    char buf[712];
} str_buf_t;

str_buf_t input = {0};
str_buf_t output = {0};

/*
void handle_command()
{
    tx_data("response: ", 10);
    tx_data(input.buf, input.size);
}
*/

static void append_data(str_buf_t *buf, const char *d, const uint16_t len)
{
    if (buf->size + len > sizeof(buf->buf))
        buf->size = 0;

    if (buf->size + len <= sizeof(buf->buf))
    {
        memcpy(buf->buf + buf->size, d, len);
        buf->size += len;
    }
}

static gen_handle_t cmd_event = NULL;

static void console_task_entry(void *_)
{
    while (1)
    {
        GEN_OS->event_wait(cmd_event);

        handle_command(input.buf);
        input.size = 0;
        input.busy = 0;
    }
}

void uart_console_start(void)
{
    cmd_event = GEN_OS->event_create();
    GEN_OS->task_create("console",
        console_task_entry,
        NULL,
        1024,
        GEN_TASK_PRIORITY_LOW);
}

void console_rx_data(const char *d, uint8_t len)
{
    if (input.busy)
    {
        return;
    }

    if (0 == input.size)
    {
        while ((len > 0) && ((*d == '\r') || (*d == '\n')))
        {
            d++;
            len--;
        }
    }
    if (len == 0) return;

    append_data(&input, d, len);

    if ((input.size > 0) &&
        ((input.buf[input.size - 1] == '\r') || (input.buf[input.size - 1] == '\n')))
    {
        int16_t t = input.size - 2;
        while ((t > 0) && ((input.buf[t] == '\r') || (input.buf[t] == '\n'))) t--;
        input.buf[t + 1] = '\0';
        input.busy = 1;
        GEN_OS->event_set(cmd_event);
    }
}

extern void stack_notify_tx_data(void);

static void tx_data(const char *d, const uint16_t len)
{
    if ((output.size == 0) && (d[len - 1] == '\0'))
    {
        puts(d);
        return;
    }

    append_data(&output, d, len);

    if ((output.size > 0) && (output.buf[output.size - 1] == '\0'))
    {
        puts(output.buf);
        output.size = 0;
    }
}

uint8_t *console_get_clear_tx_data(uint16_t *len)
{
    *len = output.size;
    output.size = 0;
    return (uint8_t *)output.buf;
}
