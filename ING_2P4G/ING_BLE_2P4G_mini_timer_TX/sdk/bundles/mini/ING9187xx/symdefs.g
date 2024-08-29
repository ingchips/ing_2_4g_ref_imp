att_dispatch_client_can_send_now = 0x00005791;
att_dispatch_client_request_can_send_now_event = 0x00005797;
att_dispatch_register_client = 0x0000579d;
att_dispatch_register_server = 0x000057b1;
att_dispatch_server_can_send_now = 0x000057c5;
att_dispatch_server_request_can_send_now_event = 0x000057cb;
att_emit_general_event = 0x0000587d;
att_server_can_send_packet_now = 0x00005fa5;
att_server_deferred_read_response = 0x00005fa9;
att_server_get_mtu = 0x00005fc1;
att_server_indicate = 0x0000602d;
att_server_init = 0x000060b1;
att_server_notify = 0x000060ed;
att_server_register_packet_handler = 0x00006205;
att_server_request_can_send_now_event = 0x00006237;
att_set_db = 0x00006253;
att_set_read_callback = 0x00006265;
att_set_write_callback = 0x00006271;
bd_addr_cmp = 0x000063e1;
bd_addr_copy = 0x000063e7;
bd_addr_to_str = 0x000063f1;
big_endian_read_16 = 0x00006429;
big_endian_read_32 = 0x00006431;
big_endian_store_16 = 0x00006445;
big_endian_store_32 = 0x00006451;
btstack_config = 0x000065a5;
btstack_get_capabilities = 0x000065b1;
btstack_memory_pool_create = 0x000066fb;
btstack_memory_pool_free = 0x00006725;
btstack_memory_pool_get = 0x00006785;
btstack_push_user_msg = 0x000067ed;
btstack_push_user_runnable = 0x000067f9;
btstack_reset = 0x00006805;
char_for_nibble = 0x00006ae9;
eTaskConfirmSleepModeStatus = 0x00006d9d;
gap_add_dev_to_periodic_list = 0x0000736d;
gap_add_whitelist = 0x0000737d;
gap_aes_encrypt = 0x00007389;
gap_clear_white_lists = 0x000073c1;
gap_clr_adv_set = 0x000073cd;
gap_clr_periodic_adv_list = 0x000073d9;
gap_create_connection_cancel = 0x000073e5;
gap_disconnect = 0x000073f1;
gap_disconnect2 = 0x000073f9;
gap_disconnect_all = 0x00007425;
gap_ext_create_connection = 0x00007465;
gap_get_connection_parameter_range = 0x0000753d;
gap_le_read_channel_map = 0x00007575;
gap_periodic_adv_create_sync = 0x000075d5;
gap_periodic_adv_create_sync_cancel = 0x000075f9;
gap_periodic_adv_term_sync = 0x00007605;
gap_read_periodic_adv_list_size = 0x0000768d;
gap_read_phy = 0x00007699;
gap_read_remote_used_features = 0x000076a5;
gap_read_remote_version = 0x000076b1;
gap_read_rssi = 0x000076bd;
gap_read_white_lists_size = 0x000076c9;
gap_remove_whitelist = 0x000076d5;
gap_rmv_adv_set = 0x00007751;
gap_rmv_dev_from_periodic_list = 0x0000775d;
gap_rx_test_v2 = 0x0000776d;
gap_set_adv_set_random_addr = 0x000077a5;
gap_set_callback_for_next_hci = 0x000077c9;
gap_set_connection_parameter_range = 0x000077e9;
gap_set_data_length = 0x00007801;
gap_set_def_phy = 0x00007819;
gap_set_ext_adv_data = 0x00007829;
gap_set_ext_adv_enable = 0x00007841;
gap_set_ext_adv_para = 0x000078b1;
gap_set_ext_scan_enable = 0x00007979;
gap_set_ext_scan_para = 0x00007991;
gap_set_ext_scan_response_data = 0x00007a31;
gap_set_host_channel_classification = 0x00007a49;
gap_set_periodic_adv_data = 0x00007a59;
gap_set_periodic_adv_enable = 0x00007ac9;
gap_set_periodic_adv_para = 0x00007ad9;
gap_set_phy = 0x00007af1;
gap_set_random_device_address = 0x00007b0d;
gap_start_ccm = 0x00007b29;
gap_test_end = 0x00007b71;
gap_tx_test_v2 = 0x00007b7d;
gap_tx_test_v4 = 0x00007b95;
gap_update_connection_parameters = 0x00007bb9;
gap_vendor_tx_continuous_wave = 0x00007bf9;
gatt_client_cancel_write = 0x00008121;
gatt_client_discover_characteristic_descriptors = 0x00008147;
gatt_client_discover_characteristics_for_handle_range_by_uuid128 = 0x00008187;
gatt_client_discover_characteristics_for_handle_range_by_uuid16 = 0x000081d7;
gatt_client_discover_characteristics_for_service = 0x00008227;
gatt_client_discover_primary_services = 0x0000825d;
gatt_client_discover_primary_services_by_uuid128 = 0x0000828f;
gatt_client_discover_primary_services_by_uuid16 = 0x000082d3;
gatt_client_execute_write = 0x0000830f;
gatt_client_find_included_services_for_service = 0x00008335;
gatt_client_get_mtu = 0x00008363;
gatt_client_is_ready = 0x00008409;
gatt_client_listen_for_characteristic_value_updates = 0x0000841f;
gatt_client_prepare_write = 0x0000843f;
gatt_client_read_characteristic_descriptor_using_descriptor_handle = 0x0000847b;
gatt_client_read_long_characteristic_descriptor_using_descriptor_handle = 0x000084a5;
gatt_client_read_long_characteristic_descriptor_using_descriptor_handle_with_offset = 0x000084ab;
gatt_client_read_long_value_of_characteristic_using_value_handle = 0x000084d9;
gatt_client_read_long_value_of_characteristic_using_value_handle_with_offset = 0x000084df;
gatt_client_read_multiple_characteristic_values = 0x0000850d;
gatt_client_read_value_of_characteristic_using_value_handle = 0x0000853d;
gatt_client_read_value_of_characteristics_by_uuid128 = 0x0000856b;
gatt_client_read_value_of_characteristics_by_uuid16 = 0x000085b7;
gatt_client_register_handler = 0x00008601;
gatt_client_reliable_write_long_value_of_characteristic = 0x0000860d;
gatt_client_signed_write_without_response = 0x00008a11;
gatt_client_write_characteristic_descriptor_using_descriptor_handle = 0x00008ad5;
gatt_client_write_client_characteristic_configuration = 0x00008b0f;
gatt_client_write_long_characteristic_descriptor_using_descriptor_handle = 0x00008b61;
gatt_client_write_long_characteristic_descriptor_using_descriptor_handle_with_offset = 0x00008b71;
gatt_client_write_long_value_of_characteristic = 0x00008bad;
gatt_client_write_long_value_of_characteristic_with_offset = 0x00008bbd;
gatt_client_write_value_of_characteristic = 0x00008bf9;
gatt_client_write_value_of_characteristic_without_response = 0x00008c2f;
hci_add_event_handler = 0x0000a141;
hci_power_control = 0x0000a8c1;
hci_register_acl_packet_handler = 0x0000aa75;
kv_commit = 0x0000b1ad;
kv_get = 0x0000b209;
kv_init = 0x0000b215;
kv_init_backend = 0x0000b291;
kv_put = 0x0000b2a5;
kv_remove = 0x0000b2b1;
kv_remove_all = 0x0000b2e5;
kv_value_modified = 0x0000b315;
kv_value_modified_of_key = 0x0000b331;
kv_visit = 0x0000b33d;
l2cap_add_event_handler = 0x0000b3cd;
l2cap_can_send_packet_now = 0x0000b3dd;
l2cap_create_le_credit_based_connection_request = 0x0000b599;
l2cap_credit_based_send = 0x0000b6dd;
l2cap_credit_based_send_continue = 0x0000b709;
l2cap_disconnect = 0x0000b785;
l2cap_get_le_credit_based_connection_credits = 0x0000b9cd;
l2cap_get_peer_mtu_for_local_cid = 0x0000b9e9;
l2cap_init = 0x0000bda9;
l2cap_le_send_flow_control_credit = 0x0000be9d;
l2cap_max_le_mtu = 0x0000c199;
l2cap_register_packet_handler = 0x0000c2c1;
l2cap_register_service = 0x0000c2cd;
l2cap_request_can_send_now_event = 0x0000c3dd;
l2cap_request_connection_parameter_update = 0x0000c3f7;
l2cap_send_echo_request = 0x0000c8c5;
l2cap_unregister_service = 0x0000c985;
le_device_db_add = 0x0000c9dd;
le_device_db_find = 0x0000cab5;
le_device_db_from_key = 0x0000cae1;
le_device_db_iter_cur = 0x0000cae9;
le_device_db_iter_cur_key = 0x0000caed;
le_device_db_iter_init = 0x0000caf1;
le_device_db_iter_next = 0x0000caf9;
le_device_db_remove_key = 0x0000cb1f;
ll_aes_encrypt = 0x0000cb4d;
ll_config = 0x0000cbc9;
ll_free = 0x0000cbff;
ll_get_capabilities = 0x0000cc09;
ll_get_heap_free_size = 0x0000cc29;
ll_get_states = 0x0000cc39;
ll_hint_on_ce_len = 0x0000ccd5;
ll_legacy_adv_set_interval = 0x0000cd0d;
ll_malloc = 0x0000cd1d;
ll_query_timing_info = 0x0000ce55;
ll_register_hci_acl_previewer = 0x0000cea1;
ll_scan_set_fixed_channel = 0x0000cf05;
ll_set_adv_access_address = 0x0000d11d;
ll_set_adv_coded_scheme = 0x0000d129;
ll_set_conn_acl_report_latency = 0x0000d151;
ll_set_conn_coded_scheme = 0x0000d17d;
ll_set_conn_latency = 0x0000d1a5;
ll_set_conn_tx_power = 0x0000d1d1;
ll_set_def_antenna = 0x0000d215;
ll_set_initiating_coded_scheme = 0x0000d231;
ll_set_max_conn_number = 0x0000d23d;
nibble_for_char = 0x0001d521;
platform_calibrate_rt_clk = 0x0001d5b3;
platform_call_on_stack = 0x00004183;
platform_cancel_us_timer = 0x0001d5b7;
platform_config = 0x0001d5cd;
platform_create_us_timer = 0x0001d6f1;
platform_delete_timer = 0x0001d705;
platform_enable_irq = 0x0001d70d;
platform_get_current_task = 0x0001d745;
platform_get_gen_os_driver = 0x0001d769;
platform_get_heap_status = 0x0001d771;
platform_get_link_layer_interf = 0x0001d789;
platform_get_task_handle = 0x0001d791;
platform_get_timer_counter = 0x0001d7b1;
platform_get_us_time = 0x0001d7b5;
platform_get_version = 0x0001d7b9;
platform_hrng = 0x0001d7c1;
platform_install_isr_stack = 0x0001d7c9;
platform_install_task_stack = 0x0001d7d5;
platform_patch_rf_init_data = 0x0001d80d;
platform_printf = 0x0001d819;
platform_raise_assertion = 0x0001d82d;
platform_rand = 0x0001d841;
platform_read_info = 0x0001d845;
platform_read_persistent_reg = 0x0001d875;
platform_reset = 0x0001d885;
platform_rt_rc_auto_tune = 0x0001d8a9;
platform_rt_rc_auto_tune2 = 0x0001d8b1;
platform_rt_rc_tune = 0x0001d92d;
platform_set_abs_timer = 0x0001d951;
platform_set_evt_callback = 0x0001d955;
platform_set_evt_callback_table = 0x0001d969;
platform_set_irq_callback = 0x0001d975;
platform_set_irq_callback_table = 0x0001d991;
platform_set_rf_clk_source = 0x0001d99d;
platform_set_rf_init_data = 0x0001d9a9;
platform_set_rf_power_mapping = 0x0001d9b5;
platform_set_timer = 0x0001d9c1;
platform_shutdown = 0x0001d9c5;
platform_switch_app = 0x0001d9c9;
platform_trace_raw = 0x0001d9f5;
platform_write_persistent_reg = 0x0001da0d;
printf_hexdump = 0x0001dbc1;
pvPortMalloc = 0x0001e6ad;
pvTaskIncrementMutexHeldCount = 0x0001e795;
pvTimerGetTimerID = 0x0001e7ad;
pxPortInitialiseStack = 0x0001e7d9;
reverse_128 = 0x0001e981;
reverse_24 = 0x0001e987;
reverse_256 = 0x0001e98d;
reverse_48 = 0x0001e993;
reverse_56 = 0x0001e999;
reverse_64 = 0x0001e99f;
reverse_bd_addr = 0x0001e9a5;
reverse_bytes = 0x0001e9ab;
sm_add_event_handler = 0x0001eb49;
sm_address_resolution_lookup = 0x0001eca1;
sm_authenticated = 0x0001f049;
sm_authorization_decline = 0x0001f057;
sm_authorization_grant = 0x0001f077;
sm_authorization_state = 0x0001f097;
sm_bonding_decline = 0x0001f0b1;
sm_config = 0x0001f50d;
sm_config_conn = 0x0001f541;
sm_encryption_key_size = 0x0001f6fb;
sm_just_works_confirm = 0x0001fc91;
sm_le_device_key = 0x0001ffc9;
sm_passkey_input = 0x0002005f;
sm_private_random_address_generation_get = 0x00020435;
sm_private_random_address_generation_get_mode = 0x0002043d;
sm_private_random_address_generation_set_mode = 0x00020449;
sm_private_random_address_generation_set_update_period = 0x00020471;
sm_register_external_ltk_callback = 0x000205ad;
sm_register_oob_data_callback = 0x000205b9;
sm_request_pairing = 0x000205c5;
sm_send_security_request = 0x000210b3;
sm_set_accepted_stk_generation_methods = 0x000210d9;
sm_set_authentication_requirements = 0x000210e5;
sm_set_encryption_key_size_range = 0x000210f5;
sscanf_bd_addr = 0x00021441;
sysSetPublicDeviceAddr = 0x0002182d;
uuid128_to_str = 0x00021e99;
uuid_add_bluetooth_prefix = 0x00021ef1;
uuid_has_bluetooth_prefix = 0x00021f11;
uxListRemove = 0x00021f2d;
uxQueueMessagesWaiting = 0x00021f55;
uxQueueMessagesWaitingFromISR = 0x00021f7d;
uxQueueSpacesAvailable = 0x00021f99;
uxTaskGetStackHighWaterMark = 0x00021fc5;
uxTaskPriorityGet = 0x00021fe5;
uxTaskPriorityGetFromISR = 0x00022001;
vListInitialise = 0x000220c7;
vListInitialiseItem = 0x000220dd;
vListInsert = 0x000220e3;
vListInsertEnd = 0x00022113;
vPortEndScheduler = 0x0002212d;
vPortEnterCritical = 0x00022159;
vPortExitCritical = 0x0002219d;
vPortFree = 0x000221d1;
vPortSuppressTicksAndSleep = 0x00022265;
vPortValidateInterruptPriority = 0x0002238d;
vQueueDelete = 0x000223e9;
vQueueWaitForMessageRestricted = 0x00022415;
vTaskDelay = 0x0002245d;
vTaskInternalSetTimeOutState = 0x000224a9;
vTaskMissedYield = 0x000224b9;
vTaskPlaceOnEventList = 0x000224c5;
vTaskPlaceOnEventListRestricted = 0x000224fd;
vTaskPriorityDisinheritAfterTimeout = 0x0002253d;
vTaskPrioritySet = 0x000225e9;
vTaskResume = 0x000226b1;
vTaskStartScheduler = 0x00022735;
vTaskStepTick = 0x000227c5;
vTaskSuspend = 0x000227f5;
vTaskSuspendAll = 0x000228b1;
vTaskSwitchContext = 0x000228c1;
xPortStartScheduler = 0x00022969;
xQueueAddToSet = 0x00022a31;
xQueueCreateCountingSemaphore = 0x00022a55;
xQueueCreateCountingSemaphoreStatic = 0x00022a91;
xQueueCreateMutex = 0x00022ad5;
xQueueCreateMutexStatic = 0x00022aeb;
xQueueCreateSet = 0x00022b05;
xQueueGenericCreate = 0x00022b0d;
xQueueGenericCreateStatic = 0x00022b59;
xQueueGenericReset = 0x00022bc1;
xQueueGenericSend = 0x00022c4d;
xQueueGenericSendFromISR = 0x00022db9;
xQueueGiveFromISR = 0x00022e79;
xQueueGiveMutexRecursive = 0x00022f1d;
xQueueIsQueueEmptyFromISR = 0x00022f5d;
xQueueIsQueueFullFromISR = 0x00022f81;
xQueuePeek = 0x00022fa9;
xQueuePeekFromISR = 0x000230d1;
xQueueReceive = 0x0002313d;
xQueueReceiveFromISR = 0x00023269;
xQueueRemoveFromSet = 0x000232fd;
xQueueSelectFromSet = 0x0002331f;
xQueueSelectFromSetFromISR = 0x00023331;
xQueueSemaphoreTake = 0x00023345;
xQueueTakeMutexRecursive = 0x000234b1;
xTaskCheckForTimeOut = 0x000234f5;
xTaskCreate = 0x00023565;
xTaskCreateStatic = 0x000235c1;
xTaskGetCurrentTaskHandle = 0x00023631;
xTaskGetSchedulerState = 0x0002363d;
xTaskGetTickCount = 0x00023659;
xTaskGetTickCountFromISR = 0x00023665;
xTaskIncrementTick = 0x00023675;
xTaskPriorityDisinherit = 0x00023741;
xTaskPriorityInherit = 0x000237d5;
xTaskRemoveFromEventList = 0x00023869;
xTaskResumeAll = 0x000238e9;
xTaskResumeFromISR = 0x000239b1;
xTimerCreate = 0x00023a3d;
xTimerCreateStatic = 0x00023a71;
xTimerCreateTimerTask = 0x00023aa9;
xTimerGenericCommand = 0x00023b15;
xTimerGetExpiryTime = 0x00023b85;
xTimerGetTimerDaemonTaskHandle = 0x00023ba5;
