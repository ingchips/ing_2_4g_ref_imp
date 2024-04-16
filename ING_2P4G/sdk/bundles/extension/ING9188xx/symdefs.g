att_dispatch_client_can_send_now = 0x000058bd;
att_dispatch_client_request_can_send_now_event = 0x000058c3;
att_dispatch_register_client = 0x000058c9;
att_dispatch_register_server = 0x000058dd;
att_dispatch_server_can_send_now = 0x000058f1;
att_dispatch_server_request_can_send_now_event = 0x000058f7;
att_emit_general_event = 0x000059a9;
att_server_can_send_packet_now = 0x000060dd;
att_server_deferred_read_response = 0x000060e1;
att_server_get_mtu = 0x000060f9;
att_server_indicate = 0x00006171;
att_server_init = 0x000061f5;
att_server_notify = 0x00006231;
att_server_register_packet_handler = 0x00006349;
att_server_request_can_send_now_event = 0x00006355;
att_set_db = 0x00006371;
att_set_read_callback = 0x00006385;
att_set_write_callback = 0x00006391;
bd_addr_cmp = 0x00006501;
bd_addr_copy = 0x00006507;
bd_addr_to_str = 0x00006511;
big_endian_read_16 = 0x00006549;
big_endian_read_32 = 0x00006551;
big_endian_store_16 = 0x00006565;
big_endian_store_32 = 0x00006571;
btstack_config = 0x000066c5;
btstack_get_capabilities = 0x000066d1;
btstack_memory_pool_create = 0x00006819;
btstack_memory_pool_free = 0x00006841;
btstack_memory_pool_get = 0x000068a1;
btstack_push_user_msg = 0x00006909;
btstack_push_user_runnable = 0x00006915;
btstack_reset = 0x00006921;
char_for_nibble = 0x00006bfd;
eTaskConfirmSleepModeStatus = 0x00006ee5;
gap_add_dev_to_periodic_list = 0x0000753d;
gap_add_whitelist = 0x0000754d;
gap_aes_encrypt = 0x00007559;
gap_clear_white_lists = 0x00007591;
gap_clr_adv_set = 0x0000759d;
gap_clr_periodic_adv_list = 0x000075a9;
gap_create_connection_cancel = 0x000075b5;
gap_default_periodic_adv_sync_transfer_param = 0x000075c1;
gap_disconnect = 0x000075d9;
gap_disconnect2 = 0x000075e1;
gap_disconnect_all = 0x0000760d;
gap_ext_create_connection = 0x0000764d;
gap_get_connection_parameter_range = 0x00007725;
gap_le_read_channel_map = 0x0000775d;
gap_periodic_adv_create_sync = 0x000077bd;
gap_periodic_adv_create_sync_cancel = 0x000077e1;
gap_periodic_adv_set_info_transfer = 0x000077ed;
gap_periodic_adv_sync_transfer = 0x000077fd;
gap_periodic_adv_sync_transfer_param = 0x0000780d;
gap_periodic_adv_term_sync = 0x00007829;
gap_read_antenna_info = 0x000078b1;
gap_read_periodic_adv_list_size = 0x000078bd;
gap_read_phy = 0x000078c9;
gap_read_remote_used_features = 0x000078d5;
gap_read_remote_version = 0x000078e1;
gap_read_rssi = 0x000078ed;
gap_read_white_lists_size = 0x000078f9;
gap_remove_whitelist = 0x00007905;
gap_rmv_adv_set = 0x00007981;
gap_rmv_dev_from_periodic_list = 0x0000798d;
gap_rx_test_v2 = 0x0000799d;
gap_rx_test_v3 = 0x000079ad;
gap_set_adv_set_random_addr = 0x000079f9;
gap_set_callback_for_next_hci = 0x00007a1d;
gap_set_connection_cte_request_enable = 0x00007a3d;
gap_set_connection_cte_response_enable = 0x00007a59;
gap_set_connection_cte_rx_param = 0x00007a69;
gap_set_connection_cte_tx_param = 0x00007abd;
gap_set_connection_parameter_range = 0x00007b09;
gap_set_connectionless_cte_tx_enable = 0x00007b21;
gap_set_connectionless_cte_tx_param = 0x00007b31;
gap_set_connectionless_iq_sampling_enable = 0x00007b8d;
gap_set_data_length = 0x00007be9;
gap_set_def_phy = 0x00007c01;
gap_set_ext_adv_data = 0x00007c11;
gap_set_ext_adv_enable = 0x00007c29;
gap_set_ext_adv_para = 0x00007c99;
gap_set_ext_scan_enable = 0x00007d61;
gap_set_ext_scan_para = 0x00007d79;
gap_set_ext_scan_response_data = 0x00007e19;
gap_set_host_channel_classification = 0x00007e31;
gap_set_periodic_adv_data = 0x00007e41;
gap_set_periodic_adv_enable = 0x00007eb1;
gap_set_periodic_adv_para = 0x00007ec1;
gap_set_periodic_adv_rx_enable = 0x00007ed9;
gap_set_phy = 0x00007ee9;
gap_set_random_device_address = 0x00007f05;
gap_start_ccm = 0x00007f21;
gap_test_end = 0x00007f69;
gap_tx_test_v2 = 0x00007f75;
gap_tx_test_v4 = 0x00007f8d;
gap_update_connection_parameters = 0x00007fb1;
gap_vendor_tx_continuous_wave = 0x00007ff5;
gatt_client_cancel_write = 0x0000851d;
gatt_client_discover_characteristic_descriptors = 0x00008543;
gatt_client_discover_characteristics_for_handle_range_by_uuid128 = 0x00008583;
gatt_client_discover_characteristics_for_handle_range_by_uuid16 = 0x000085d3;
gatt_client_discover_characteristics_for_service = 0x00008623;
gatt_client_discover_primary_services = 0x00008659;
gatt_client_discover_primary_services_by_uuid128 = 0x0000868b;
gatt_client_discover_primary_services_by_uuid16 = 0x000086cf;
gatt_client_execute_write = 0x0000870b;
gatt_client_find_included_services_for_service = 0x00008731;
gatt_client_get_mtu = 0x0000875f;
gatt_client_is_ready = 0x00008809;
gatt_client_listen_for_characteristic_value_updates = 0x0000881f;
gatt_client_prepare_write = 0x00008841;
gatt_client_read_characteristic_descriptor_using_descriptor_handle = 0x0000887d;
gatt_client_read_long_characteristic_descriptor_using_descriptor_handle = 0x000088a7;
gatt_client_read_long_characteristic_descriptor_using_descriptor_handle_with_offset = 0x000088ad;
gatt_client_read_long_value_of_characteristic_using_value_handle = 0x000088db;
gatt_client_read_long_value_of_characteristic_using_value_handle_with_offset = 0x000088e1;
gatt_client_read_multiple_characteristic_values = 0x0000890f;
gatt_client_read_value_of_characteristic_using_value_handle = 0x0000893f;
gatt_client_read_value_of_characteristics_by_uuid128 = 0x0000896d;
gatt_client_read_value_of_characteristics_by_uuid16 = 0x000089b9;
gatt_client_register_handler = 0x00008a05;
gatt_client_reliable_write_long_value_of_characteristic = 0x00008a11;
gatt_client_signed_write_without_response = 0x00008e41;
gatt_client_write_characteristic_descriptor_using_descriptor_handle = 0x00008f05;
gatt_client_write_client_characteristic_configuration = 0x00008f3f;
gatt_client_write_long_characteristic_descriptor_using_descriptor_handle = 0x00008f91;
gatt_client_write_long_characteristic_descriptor_using_descriptor_handle_with_offset = 0x00008fa1;
gatt_client_write_long_value_of_characteristic = 0x00008fdd;
gatt_client_write_long_value_of_characteristic_with_offset = 0x00008fed;
gatt_client_write_value_of_characteristic = 0x00009029;
gatt_client_write_value_of_characteristic_without_response = 0x0000905f;
hci_add_event_handler = 0x0000a599;
hci_power_control = 0x0000ad35;
hci_register_acl_packet_handler = 0x0000aee9;
kv_commit = 0x0000b64d;
kv_get = 0x0000b6a9;
kv_init = 0x0000b6b5;
kv_init_backend = 0x0000b735;
kv_put = 0x0000b749;
kv_remove = 0x0000b755;
kv_remove_all = 0x0000b789;
kv_value_modified = 0x0000b7b9;
kv_value_modified_of_key = 0x0000b7d5;
kv_visit = 0x0000b7e1;
l2cap_add_event_handler = 0x0000b871;
l2cap_can_send_packet_now = 0x0000b881;
l2cap_create_le_credit_based_connection_request = 0x0000ba3d;
l2cap_credit_based_send = 0x0000bb81;
l2cap_credit_based_send_continue = 0x0000bbad;
l2cap_disconnect = 0x0000bc29;
l2cap_get_le_credit_based_connection_credits = 0x0000be79;
l2cap_get_peer_mtu_for_local_cid = 0x0000be95;
l2cap_init = 0x0000c269;
l2cap_le_send_flow_control_credit = 0x0000c35f;
l2cap_max_le_mtu = 0x0000c669;
l2cap_register_packet_handler = 0x0000c791;
l2cap_register_service = 0x0000c79d;
l2cap_request_can_send_now_event = 0x0000c8ad;
l2cap_request_connection_parameter_update = 0x0000c8c7;
l2cap_send_echo_request = 0x0000cda1;
l2cap_unregister_service = 0x0000ce61;
le_device_db_add = 0x0000ceb9;
le_device_db_find = 0x0000cf91;
le_device_db_from_key = 0x0000cfbd;
le_device_db_iter_cur = 0x0000cfc5;
le_device_db_iter_cur_key = 0x0000cfc9;
le_device_db_iter_init = 0x0000cfcd;
le_device_db_iter_next = 0x0000cfd5;
le_device_db_remove_key = 0x0000cffb;
ll_ackable_packet_alloc = 0x0000d027;
ll_ackable_packet_get_status = 0x0000d159;
ll_ackable_packet_run = 0x0000d1c9;
ll_ackable_packet_set_tx_data = 0x0000d265;
ll_aes_encrypt = 0x0000d281;
ll_attach_cte_to_adv_set = 0x0000d2fd;
ll_channel_monitor_alloc = 0x0000d495;
ll_channel_monitor_check_each_pdu = 0x0000d517;
ll_channel_monitor_run = 0x0000d585;
ll_config = 0x0000d639;
ll_free = 0x0000d66f;
ll_get_capabilities = 0x0000d679;
ll_get_heap_free_size = 0x0000d699;
ll_get_states = 0x0000d6a9;
ll_hint_on_ce_len = 0x0000d765;
ll_legacy_adv_set_interval = 0x0000d79d;
ll_lock_frequency = 0x0000d7ad;
ll_malloc = 0x0000d811;
ll_query_timing_info = 0x0000d949;
ll_raw_packet_alloc = 0x0000d995;
ll_raw_packet_free = 0x0000da69;
ll_raw_packet_get_bare_rx_data = 0x0000daa1;
ll_raw_packet_get_iq_samples = 0x0000db67;
ll_raw_packet_get_rx_data = 0x0000dc01;
ll_raw_packet_recv = 0x0000dca1;
ll_raw_packet_send = 0x0000dd5d;
ll_raw_packet_set_bare_data = 0x0000de45;
ll_raw_packet_set_bare_mode = 0x0000de83;
ll_raw_packet_set_fake_cte_info = 0x0000df89;
ll_raw_packet_set_param = 0x0000dfab;
ll_raw_packet_set_rx_cte = 0x0000e009;
ll_raw_packet_set_tx_cte = 0x0000e09f;
ll_raw_packet_set_tx_data = 0x0000e0dd;
ll_register_hci_acl_previewer = 0x0000e141;
ll_scan_set_fixed_channel = 0x0000e1a5;
ll_scanner_enable_iq_sampling = 0x0000e1b1;
ll_set_adv_access_address = 0x0000e465;
ll_set_adv_coded_scheme = 0x0000e471;
ll_set_conn_acl_report_latency = 0x0000e4a1;
ll_set_conn_coded_scheme = 0x0000e4d1;
ll_set_conn_interval_unit = 0x0000e4fd;
ll_set_conn_latency = 0x0000e509;
ll_set_conn_tx_power = 0x0000e539;
ll_set_def_antenna = 0x0000e581;
ll_set_initiating_coded_scheme = 0x0000e59d;
ll_set_max_conn_number = 0x0000e5a9;
ll_unlock_frequency = 0x0000e63d;
nibble_for_char = 0x0001f8fd;
platform_calibrate_rt_clk = 0x0001f9a9;
platform_call_on_stack = 0x00004183;
platform_cancel_us_timer = 0x0001f9ad;
platform_config = 0x0001f9c1;
platform_create_us_timer = 0x0001fae5;
platform_delete_timer = 0x0001faf9;
platform_enable_irq = 0x0001fb01;
platform_get_current_task = 0x0001fb39;
platform_get_gen_os_driver = 0x0001fb5d;
platform_get_heap_status = 0x0001fb65;
platform_get_link_layer_interf = 0x0001fb7d;
platform_get_task_handle = 0x0001fb85;
platform_get_timer_counter = 0x0001fba5;
platform_get_us_time = 0x0001fba9;
platform_get_version = 0x0001fbad;
platform_hrng = 0x0001fbb5;
platform_install_isr_stack = 0x0001fbbd;
platform_install_task_stack = 0x0001fbc9;
platform_patch_rf_init_data = 0x0001fc01;
platform_printf = 0x0001fc0d;
platform_raise_assertion = 0x0001fc21;
platform_rand = 0x0001fc35;
platform_read_info = 0x0001fc39;
platform_read_persistent_reg = 0x0001fc69;
platform_reset = 0x0001fc79;
platform_rt_rc_auto_tune = 0x0001fc9d;
platform_rt_rc_auto_tune2 = 0x0001fca5;
platform_rt_rc_tune = 0x0001fd21;
platform_set_abs_timer = 0x0001fd45;
platform_set_evt_callback = 0x0001fd49;
platform_set_evt_callback_table = 0x0001fd5d;
platform_set_irq_callback = 0x0001fd69;
platform_set_irq_callback_table = 0x0001fd85;
platform_set_rf_clk_source = 0x0001fd91;
platform_set_rf_init_data = 0x0001fd9d;
platform_set_rf_power_mapping = 0x0001fda9;
platform_set_timer = 0x0001fdb5;
platform_shutdown = 0x0001fdb9;
platform_switch_app = 0x0001fdbd;
platform_trace_raw = 0x0001fde9;
platform_write_persistent_reg = 0x0001fe01;
printf_hexdump = 0x0001ffb5;
pvPortMalloc = 0x00020aa9;
pvTaskIncrementMutexHeldCount = 0x00020b91;
pvTimerGetTimerID = 0x00020ba9;
pxPortInitialiseStack = 0x00020bd5;
reverse_128 = 0x00020db5;
reverse_24 = 0x00020dbb;
reverse_256 = 0x00020dc1;
reverse_48 = 0x00020dc7;
reverse_56 = 0x00020dcd;
reverse_64 = 0x00020dd3;
reverse_bd_addr = 0x00020dd9;
reverse_bytes = 0x00020ddf;
sm_add_event_handler = 0x000210fd;
sm_address_resolution_lookup = 0x00021255;
sm_authenticated = 0x000215fd;
sm_authorization_decline = 0x0002160b;
sm_authorization_grant = 0x0002162b;
sm_authorization_state = 0x0002164b;
sm_bonding_decline = 0x00021665;
sm_config = 0x00021ac1;
sm_config_conn = 0x00021af5;
sm_encryption_key_size = 0x00021caf;
sm_just_works_confirm = 0x00022235;
sm_le_device_key = 0x00022575;
sm_passkey_input = 0x0002260b;
sm_private_random_address_generation_get = 0x000229cd;
sm_private_random_address_generation_get_mode = 0x000229d5;
sm_private_random_address_generation_set_mode = 0x000229e1;
sm_private_random_address_generation_set_update_period = 0x00022a09;
sm_register_external_ltk_callback = 0x00022b45;
sm_register_oob_data_callback = 0x00022b51;
sm_request_pairing = 0x00022b5d;
sm_send_security_request = 0x0002363b;
sm_set_accepted_stk_generation_methods = 0x00023661;
sm_set_authentication_requirements = 0x0002366d;
sm_set_encryption_key_size_range = 0x0002367d;
sscanf_bd_addr = 0x00023a3d;
sysSetPublicDeviceAddr = 0x00023e39;
uuid128_to_str = 0x000245f9;
uuid_add_bluetooth_prefix = 0x00024651;
uuid_has_bluetooth_prefix = 0x00024671;
uxListRemove = 0x0002468d;
uxQueueMessagesWaiting = 0x000246b5;
uxQueueMessagesWaitingFromISR = 0x000246dd;
uxQueueSpacesAvailable = 0x000246f9;
uxTaskGetStackHighWaterMark = 0x00024725;
uxTaskPriorityGet = 0x00024745;
uxTaskPriorityGetFromISR = 0x00024761;
vListInitialise = 0x0002481b;
vListInitialiseItem = 0x00024831;
vListInsert = 0x00024837;
vListInsertEnd = 0x00024867;
vPortEndScheduler = 0x00024881;
vPortEnterCritical = 0x000248ad;
vPortExitCritical = 0x000248f1;
vPortFree = 0x00024925;
vPortSuppressTicksAndSleep = 0x000249b9;
vPortValidateInterruptPriority = 0x00024ae1;
vQueueDelete = 0x00024b3d;
vQueueWaitForMessageRestricted = 0x00024b69;
vTaskDelay = 0x00024bb1;
vTaskInternalSetTimeOutState = 0x00024bfd;
vTaskMissedYield = 0x00024c0d;
vTaskPlaceOnEventList = 0x00024c19;
vTaskPlaceOnEventListRestricted = 0x00024c51;
vTaskPriorityDisinheritAfterTimeout = 0x00024c91;
vTaskPrioritySet = 0x00024d3d;
vTaskResume = 0x00024e05;
vTaskStartScheduler = 0x00024e89;
vTaskStepTick = 0x00024f19;
vTaskSuspend = 0x00024f49;
vTaskSuspendAll = 0x00025005;
vTaskSwitchContext = 0x00025015;
xPortStartScheduler = 0x000250bd;
xQueueAddToSet = 0x00025185;
xQueueCreateCountingSemaphore = 0x000251a9;
xQueueCreateCountingSemaphoreStatic = 0x000251e5;
xQueueCreateMutex = 0x00025229;
xQueueCreateMutexStatic = 0x0002523f;
xQueueCreateSet = 0x00025259;
xQueueGenericCreate = 0x00025261;
xQueueGenericCreateStatic = 0x000252ad;
xQueueGenericReset = 0x00025315;
xQueueGenericSend = 0x000253a1;
xQueueGenericSendFromISR = 0x0002550d;
xQueueGiveFromISR = 0x000255cd;
xQueueGiveMutexRecursive = 0x00025671;
xQueueIsQueueEmptyFromISR = 0x000256b1;
xQueueIsQueueFullFromISR = 0x000256d5;
xQueuePeek = 0x000256fd;
xQueuePeekFromISR = 0x00025825;
xQueueReceive = 0x00025891;
xQueueReceiveFromISR = 0x000259bd;
xQueueRemoveFromSet = 0x00025a51;
xQueueSelectFromSet = 0x00025a73;
xQueueSelectFromSetFromISR = 0x00025a85;
xQueueSemaphoreTake = 0x00025a99;
xQueueTakeMutexRecursive = 0x00025c05;
xTaskCheckForTimeOut = 0x00025c49;
xTaskCreate = 0x00025cb9;
xTaskCreateStatic = 0x00025d15;
xTaskGetCurrentTaskHandle = 0x00025d85;
xTaskGetSchedulerState = 0x00025d91;
xTaskGetTickCount = 0x00025dad;
xTaskGetTickCountFromISR = 0x00025db9;
xTaskIncrementTick = 0x00025dc9;
xTaskPriorityDisinherit = 0x00025e95;
xTaskPriorityInherit = 0x00025f29;
xTaskRemoveFromEventList = 0x00025fbd;
xTaskResumeAll = 0x0002603d;
xTaskResumeFromISR = 0x00026105;
xTimerCreate = 0x00026191;
xTimerCreateStatic = 0x000261c5;
xTimerCreateTimerTask = 0x000261fd;
xTimerGenericCommand = 0x00026269;
xTimerGetExpiryTime = 0x000262d9;
xTimerGetTimerDaemonTaskHandle = 0x000262f9;
