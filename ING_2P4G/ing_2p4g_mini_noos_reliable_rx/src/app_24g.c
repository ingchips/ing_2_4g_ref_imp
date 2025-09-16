#include "app_24g.h"
#include "platform_api.h"
#include "ing_24g.h"

static void app_2g4_event_handle(uint8_t event, uint8_t *data, uint8_t len)
{
    static uint16_t recv_cnt = 0;
    static uint8_t expect_idx = 0;
    static uint8_t last_data = 0;
    switch (event) {
		case ING24G_EVENT_CONNECTED: {
            platform_printf("ING24G_EVENT_CONNECTED\n");
			recv_cnt = 0;
			expect_idx = 0;
        } break;
        case ING24G_EVENT_DISCONNECT: {
            platform_printf("ING24G_EVENT_DISCONNECT\n");
        } break;
        case ING24G_EVENT_RECEIVE: {
            // platform_printf("receive data: %d\n", len);
            if(expect_idx != data[1])
            {
                // platform_printf("receive data error, expect idx: %d, receive idx: %d, last_sn : %d, cur_sn : %d, last_data : %d, len : %d\n", expect_idx, data[1], last_sn, data[0], last_data, len);
            }
            expect_idx = data[1] + 1;
            last_data = data[1];
            recv_cnt++;
            if(recv_cnt % 1000 == 0)
            {
                expect_idx = 0;
                last_data = 0;
                platform_printf("receive cnt: %d\n", recv_cnt);
            }
        } break;
    }
}

void app_24g_init(void)
{
    ing24g_init(app_2g4_event_handle);
}
