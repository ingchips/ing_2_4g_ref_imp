#include "uart_console.h"

#include "ingsoc.h"

#include <stdio.h>
#include <string.h>

#include "platform_api.h"
#include "bluetooth.h"
#include "sm.h"

#include "btstack_mt.h"
#include "port_gen_os_driver.h"
#include "ing_24g.h"


#define GEN_OS          ((const gen_os_driver_t *)os_impl_get_driver())

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
                            "h/?                      show this\n"
                            ;

void cmd_help(const char *param)
{
    tx_data(help, strlen(help) + 1);
}

void cmd_print_version_inst(const char *param)
{
    platform_printf("Software Ver : %d\n", 1);
}

static uint8_t test_enable = 0;
void cmd_send_test(const char *param)
{
    platform_printf("start test\n");
    test_enable = 1;
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
        .cmd = "version",
        .handler = cmd_print_version_inst,
    },
    {
        .cmd = "send_test",
        .handler = cmd_send_test,
    },
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
    char buf[56];
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
static volatile uint8_t loop_console_flag = 0;

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

static uint8_t test_data[] = {0, 2, 3};
void loop_uart_console(void)
{
    static uint64_t last_us_time = 0;
    static uint16_t cnt = 0;
    static uint8_t temp = 0;
    if(loop_console_flag)
    {
        handle_command(input.buf);
        input.size = 0;
        input.busy = 0;
        loop_console_flag = 0;
    }

    if(test_enable)
    {
        if(platform_get_us_time() - last_us_time > 1000) // 1 ms
        {
            last_us_time = platform_get_us_time();
            test_data[0] = temp; // Update the first byte with the count
            if(ing24g_send_data(test_data, sizeof(test_data)) == 0)
            {
                temp++;
                cnt++;
                if(cnt == 1000)
                {
                    cnt = 0;
                    temp = 0;
                    test_enable = 0;
                    platform_printf("test end\n");
                }
            }
        }
    }
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
        loop_console_flag = 1;
//        GEN_OS->event_set(cmd_event);
//        printf("handle\n");
//        handle_command(input.buf);
//        input.size = 0;
//        input.busy = 0;
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
