--define_symbol att_dispatch_client_can_send_now=0x00005875
--define_symbol att_dispatch_client_request_can_send_now_event=0x0000587b
--define_symbol att_dispatch_register_client=0x00005881
--define_symbol att_dispatch_register_server=0x00005895
--define_symbol att_dispatch_server_can_send_now=0x000058a9
--define_symbol att_dispatch_server_request_can_send_now_event=0x000058af
--define_symbol att_emit_general_event=0x00005961
--define_symbol att_server_can_send_packet_now=0x00006091
--define_symbol att_server_deferred_read_response=0x00006095
--define_symbol att_server_get_mtu=0x000060ad
--define_symbol att_server_indicate=0x00006125
--define_symbol att_server_init=0x000061a9
--define_symbol att_server_notify=0x000061e5
--define_symbol att_server_register_packet_handler=0x000062fd
--define_symbol att_server_request_can_send_now_event=0x00006309
--define_symbol att_set_db=0x00006325
--define_symbol att_set_read_callback=0x00006339
--define_symbol att_set_write_callback=0x00006345
--define_symbol bd_addr_cmp=0x000064b5
--define_symbol bd_addr_copy=0x000064bb
--define_symbol bd_addr_to_str=0x000064c5
--define_symbol big_endian_read_16=0x000064fd
--define_symbol big_endian_read_32=0x00006505
--define_symbol big_endian_store_16=0x00006519
--define_symbol big_endian_store_32=0x00006525
--define_symbol btstack_config=0x00006679
--define_symbol btstack_memory_pool_create=0x000067b7
--define_symbol btstack_memory_pool_free=0x000067e1
--define_symbol btstack_memory_pool_get=0x00006841
--define_symbol btstack_push_user_msg=0x000068a9
--define_symbol btstack_push_user_runnable=0x000068b5
--define_symbol btstack_reset=0x000068c1
--define_symbol char_for_nibble=0x00006b9d
--define_symbol eTaskConfirmSleepModeStatus=0x00006e85
--define_symbol gap_add_dev_to_periodic_list=0x000074f1
--define_symbol gap_add_whitelist=0x00007501
--define_symbol gap_aes_encrypt=0x0000750d
--define_symbol gap_clear_white_lists=0x00007545
--define_symbol gap_clr_adv_set=0x00007551
--define_symbol gap_clr_periodic_adv_list=0x0000755d
--define_symbol gap_create_connection_cancel=0x00007569
--define_symbol gap_default_periodic_adv_sync_transfer_param=0x00007575
--define_symbol gap_disconnect=0x0000758d
--define_symbol gap_disconnect_all=0x000075b9
--define_symbol gap_ext_create_connection=0x000075f9
--define_symbol gap_get_connection_parameter_range=0x000076d1
--define_symbol gap_le_read_channel_map=0x0000770d
--define_symbol gap_periodic_adv_create_sync=0x00007779
--define_symbol gap_periodic_adv_create_sync_cancel=0x0000779d
--define_symbol gap_periodic_adv_set_info_transfer=0x000077a9
--define_symbol gap_periodic_adv_sync_transfer=0x000077b9
--define_symbol gap_periodic_adv_sync_transfer_param=0x000077c9
--define_symbol gap_periodic_adv_term_sync=0x000077e5
--define_symbol gap_read_antenna_info=0x0000786d
--define_symbol gap_read_periodic_adv_list_size=0x00007879
--define_symbol gap_read_phy=0x00007885
--define_symbol gap_read_remote_used_features=0x00007891
--define_symbol gap_read_remote_version=0x0000789d
--define_symbol gap_read_rssi=0x000078a9
--define_symbol gap_remove_whitelist=0x000078b5
--define_symbol gap_rmv_adv_set=0x00007931
--define_symbol gap_rmv_dev_from_periodic_list=0x0000793d
--define_symbol gap_rx_test_v2=0x0000794d
--define_symbol gap_rx_test_v3=0x0000795d
--define_symbol gap_set_adv_set_random_addr=0x000079a9
--define_symbol gap_set_callback_for_next_hci=0x000079e5
--define_symbol gap_set_connection_cte_request_enable=0x00007a05
--define_symbol gap_set_connection_cte_response_enable=0x00007a21
--define_symbol gap_set_connection_cte_rx_param=0x00007a31
--define_symbol gap_set_connection_cte_tx_param=0x00007a85
--define_symbol gap_set_connection_parameter_range=0x00007ad1
--define_symbol gap_set_connectionless_cte_tx_enable=0x00007ae9
--define_symbol gap_set_connectionless_cte_tx_param=0x00007af9
--define_symbol gap_set_connectionless_iq_sampling_enable=0x00007b55
--define_symbol gap_set_data_length=0x00007bb1
--define_symbol gap_set_def_phy=0x00007bc9
--define_symbol gap_set_ext_adv_data=0x00007bd9
--define_symbol gap_set_ext_adv_enable=0x00007bf1
--define_symbol gap_set_ext_adv_para=0x00007c61
--define_symbol gap_set_ext_scan_enable=0x00007d39
--define_symbol gap_set_ext_scan_para=0x00007d51
--define_symbol gap_set_ext_scan_response_data=0x00007df1
--define_symbol gap_set_host_channel_classification=0x00007e09
--define_symbol gap_set_periodic_adv_data=0x00007e19
--define_symbol gap_set_periodic_adv_enable=0x00007e89
--define_symbol gap_set_periodic_adv_para=0x00007e99
--define_symbol gap_set_periodic_adv_rx_enable=0x00007eb1
--define_symbol gap_set_phy=0x00007ec1
--define_symbol gap_set_random_device_address=0x00007edd
--define_symbol gap_start_ccm=0x00007f0d
--define_symbol gap_test_end=0x00007f55
--define_symbol gap_tx_test_v2=0x00007f61
--define_symbol gap_tx_test_v4=0x00007f79
--define_symbol gap_update_connection_parameters=0x00007f9d
--define_symbol gap_vendor_tx_continuous_wave=0x00007fe1
--define_symbol gatt_client_cancel_write=0x00008509
--define_symbol gatt_client_discover_characteristic_descriptors=0x0000852f
--define_symbol gatt_client_discover_characteristics_for_handle_range_by_uuid128=0x0000856f
--define_symbol gatt_client_discover_characteristics_for_handle_range_by_uuid16=0x000085bf
--define_symbol gatt_client_discover_characteristics_for_service=0x0000860f
--define_symbol gatt_client_discover_primary_services=0x00008645
--define_symbol gatt_client_discover_primary_services_by_uuid128=0x00008677
--define_symbol gatt_client_discover_primary_services_by_uuid16=0x000086bb
--define_symbol gatt_client_execute_write=0x000086f7
--define_symbol gatt_client_find_included_services_for_service=0x0000871d
--define_symbol gatt_client_get_mtu=0x0000874b
--define_symbol gatt_client_is_ready=0x000087ed
--define_symbol gatt_client_listen_for_characteristic_value_updates=0x00008803
--define_symbol gatt_client_prepare_write=0x00008825
--define_symbol gatt_client_read_characteristic_descriptor_using_descriptor_handle=0x00008861
--define_symbol gatt_client_read_long_characteristic_descriptor_using_descriptor_handle=0x0000888b
--define_symbol gatt_client_read_long_characteristic_descriptor_using_descriptor_handle_with_offset=0x00008891
--define_symbol gatt_client_read_long_value_of_characteristic_using_value_handle=0x000088bf
--define_symbol gatt_client_read_long_value_of_characteristic_using_value_handle_with_offset=0x000088c5
--define_symbol gatt_client_read_multiple_characteristic_values=0x000088f3
--define_symbol gatt_client_read_value_of_characteristic_using_value_handle=0x00008923
--define_symbol gatt_client_read_value_of_characteristics_by_uuid128=0x00008951
--define_symbol gatt_client_read_value_of_characteristics_by_uuid16=0x0000899d
--define_symbol gatt_client_register_handler=0x000089e9
--define_symbol gatt_client_reliable_write_long_value_of_characteristic=0x000089f5
--define_symbol gatt_client_signed_write_without_response=0x00008e25
--define_symbol gatt_client_write_characteristic_descriptor_using_descriptor_handle=0x00008ee9
--define_symbol gatt_client_write_client_characteristic_configuration=0x00008f23
--define_symbol gatt_client_write_long_characteristic_descriptor_using_descriptor_handle=0x00008f75
--define_symbol gatt_client_write_long_characteristic_descriptor_using_descriptor_handle_with_offset=0x00008f85
--define_symbol gatt_client_write_long_value_of_characteristic=0x00008fc1
--define_symbol gatt_client_write_long_value_of_characteristic_with_offset=0x00008fd1
--define_symbol gatt_client_write_value_of_characteristic=0x0000900d
--define_symbol gatt_client_write_value_of_characteristic_without_response=0x00009043
--define_symbol hci_add_event_handler=0x0000a585
--define_symbol hci_power_control=0x0000ad25
--define_symbol hci_register_acl_packet_handler=0x0000aed9
--define_symbol kv_commit=0x0000b64d
--define_symbol kv_get=0x0000b6a9
--define_symbol kv_init=0x0000b6b5
--define_symbol kv_init_backend=0x0000b735
--define_symbol kv_put=0x0000b749
--define_symbol kv_remove=0x0000b755
--define_symbol kv_remove_all=0x0000b789
--define_symbol kv_value_modified=0x0000b7b9
--define_symbol kv_value_modified_of_key=0x0000b7d5
--define_symbol kv_visit=0x0000b7e1
--define_symbol l2cap_add_event_handler=0x0000b871
--define_symbol l2cap_can_send_packet_now=0x0000b881
--define_symbol l2cap_create_le_credit_based_connection_request=0x0000ba3d
--define_symbol l2cap_credit_based_send=0x0000bb81
--define_symbol l2cap_credit_based_send_continue=0x0000bbad
--define_symbol l2cap_disconnect=0x0000bc29
--define_symbol l2cap_get_le_credit_based_connection_credits=0x0000be79
--define_symbol l2cap_get_peer_mtu_for_local_cid=0x0000be95
--define_symbol l2cap_init=0x0000c269
--define_symbol l2cap_le_send_flow_control_credit=0x0000c35f
--define_symbol l2cap_max_le_mtu=0x0000c669
--define_symbol l2cap_register_packet_handler=0x0000c791
--define_symbol l2cap_register_service=0x0000c79d
--define_symbol l2cap_request_can_send_now_event=0x0000c8ad
--define_symbol l2cap_request_connection_parameter_update=0x0000c8c7
--define_symbol l2cap_send_echo_request=0x0000cda1
--define_symbol l2cap_unregister_service=0x0000ce61
--define_symbol le_device_db_add=0x0000ceb9
--define_symbol le_device_db_find=0x0000cf91
--define_symbol le_device_db_from_key=0x0000cfbd
--define_symbol le_device_db_iter_cur=0x0000cfc5
--define_symbol le_device_db_iter_cur_key=0x0000cfc9
--define_symbol le_device_db_iter_init=0x0000cfcd
--define_symbol le_device_db_iter_next=0x0000cfd5
--define_symbol le_device_db_remove_key=0x0000cffb
--define_symbol ll_ackable_packet_alloc=0x0000d027
--define_symbol ll_ackable_packet_get_status=0x0000d159
--define_symbol ll_ackable_packet_run=0x0000d1c9
--define_symbol ll_ackable_packet_set_tx_data=0x0000d265
--define_symbol ll_aes_encrypt=0x0000d281
--define_symbol ll_attach_cte_to_adv_set=0x0000d2fd
--define_symbol ll_channel_monitor_alloc=0x0000d495
--define_symbol ll_channel_monitor_check_each_pdu=0x0000d517
--define_symbol ll_channel_monitor_run=0x0000d57d
--define_symbol ll_config=0x0000d631
--define_symbol ll_free=0x0000d667
--define_symbol ll_get_heap_free_size=0x0000d671
--define_symbol ll_hint_on_ce_len=0x0000d685
--define_symbol ll_legacy_adv_set_interval=0x0000d6bd
--define_symbol ll_lock_frequency=0x0000d6cd
--define_symbol ll_malloc=0x0000d731
--define_symbol ll_query_timing_info=0x0000d869
--define_symbol ll_raw_packet_alloc=0x0000d8b5
--define_symbol ll_raw_packet_free=0x0000d989
--define_symbol ll_raw_packet_get_bare_rx_data=0x0000d9c1
--define_symbol ll_raw_packet_get_iq_samples=0x0000da87
--define_symbol ll_raw_packet_get_rx_data=0x0000db21
--define_symbol ll_raw_packet_recv=0x0000dbc1
--define_symbol ll_raw_packet_send=0x0000dc7d
--define_symbol ll_raw_packet_set_bare_data=0x0000dd65
--define_symbol ll_raw_packet_set_bare_mode=0x0000dda3
--define_symbol ll_raw_packet_set_fake_cte_info=0x0000dea9
--define_symbol ll_raw_packet_set_param=0x0000decb
--define_symbol ll_raw_packet_set_rx_cte=0x0000df29
--define_symbol ll_raw_packet_set_tx_cte=0x0000dfbf
--define_symbol ll_raw_packet_set_tx_data=0x0000dffd
--define_symbol ll_register_hci_acl_previewer=0x0000e061
--define_symbol ll_scan_set_fixed_channel=0x0000e0c5
--define_symbol ll_scanner_enable_iq_sampling=0x0000e0d1
--define_symbol ll_set_adv_access_address=0x0000e385
--define_symbol ll_set_adv_coded_scheme=0x0000e391
--define_symbol ll_set_conn_acl_report_latency=0x0000e3c1
--define_symbol ll_set_conn_coded_scheme=0x0000e3f1
--define_symbol ll_set_conn_interval_unit=0x0000e41d
--define_symbol ll_set_conn_latency=0x0000e429
--define_symbol ll_set_conn_tx_power=0x0000e459
--define_symbol ll_set_def_antenna=0x0000e4a1
--define_symbol ll_set_initiating_coded_scheme=0x0000e4bd
--define_symbol ll_set_max_conn_number=0x0000e4c9
--define_symbol ll_unlock_frequency=0x0000e55d
--define_symbol nibble_for_char=0x0001f80d
--define_symbol platform_32k_rc_auto_tune=0x0001f8b9
--define_symbol platform_32k_rc_tune=0x0001f935
--define_symbol platform_calibrate_32k=0x0001f949
--define_symbol platform_config=0x0001f94d
--define_symbol platform_delete_timer=0x0001fa71
--define_symbol platform_enable_irq=0x0001fa79
--define_symbol platform_get_current_task=0x0001fab1
--define_symbol platform_get_gen_os_driver=0x0001fad5
--define_symbol platform_get_heap_status=0x0001fadd
--define_symbol platform_get_link_layer_interf=0x0001faf5
--define_symbol platform_get_task_handle=0x0001fafd
--define_symbol platform_get_timer_counter=0x0001fb1d
--define_symbol platform_get_us_time=0x0001fb21
--define_symbol platform_get_version=0x0001fb25
--define_symbol platform_hrng=0x0001fb2d
--define_symbol platform_install_isr_stack=0x0001fb35
--define_symbol platform_install_task_stack=0x0001fb41
--define_symbol platform_patch_rf_init_data=0x0001fb79
--define_symbol platform_printf=0x0001fb85
--define_symbol platform_raise_assertion=0x0001fb99
--define_symbol platform_rand=0x0001fbad
--define_symbol platform_read_info=0x0001fbb1
--define_symbol platform_read_persistent_reg=0x0001fbe1
--define_symbol platform_reset=0x0001fbf1
--define_symbol platform_set_abs_timer=0x0001fc15
--define_symbol platform_set_evt_callback=0x0001fc19
--define_symbol platform_set_evt_callback_table=0x0001fc2d
--define_symbol platform_set_irq_callback=0x0001fc39
--define_symbol platform_set_irq_callback_table=0x0001fc55
--define_symbol platform_set_rf_clk_source=0x0001fc61
--define_symbol platform_set_rf_init_data=0x0001fc6d
--define_symbol platform_set_rf_power_mapping=0x0001fc79
--define_symbol platform_set_timer=0x0001fc85
--define_symbol platform_shutdown=0x0001fc89
--define_symbol platform_switch_app=0x0001fc8d
--define_symbol platform_trace_raw=0x0001fcb9
--define_symbol platform_write_persistent_reg=0x0001fcd1
--define_symbol printf_hexdump=0x0001fe85
--define_symbol pvPortMalloc=0x00020979
--define_symbol pvTaskIncrementMutexHeldCount=0x00020a61
--define_symbol pvTimerGetTimerID=0x00020a79
--define_symbol pxPortInitialiseStack=0x00020aa5
--define_symbol reverse_128=0x00020c85
--define_symbol reverse_24=0x00020c8b
--define_symbol reverse_256=0x00020c91
--define_symbol reverse_48=0x00020c97
--define_symbol reverse_56=0x00020c9d
--define_symbol reverse_64=0x00020ca3
--define_symbol reverse_bd_addr=0x00020ca9
--define_symbol reverse_bytes=0x00020caf
--define_symbol sm_add_event_handler=0x00020fcd
--define_symbol sm_address_resolution_lookup=0x00021125
--define_symbol sm_authenticated=0x000214a1
--define_symbol sm_authorization_decline=0x000214af
--define_symbol sm_authorization_grant=0x000214cf
--define_symbol sm_authorization_state=0x000214ef
--define_symbol sm_bonding_decline=0x00021509
--define_symbol sm_config=0x00021965
--define_symbol sm_config_conn=0x0002197d
--define_symbol sm_encryption_key_size=0x00021b33
--define_symbol sm_just_works_confirm=0x000220b9
--define_symbol sm_le_device_key=0x00022405
--define_symbol sm_passkey_input=0x0002249b
--define_symbol sm_private_random_address_generation_get=0x00022855
--define_symbol sm_private_random_address_generation_get_mode=0x0002285d
--define_symbol sm_private_random_address_generation_set_mode=0x00022869
--define_symbol sm_private_random_address_generation_set_update_period=0x00022891
--define_symbol sm_register_external_ltk_callback=0x000229cd
--define_symbol sm_register_oob_data_callback=0x000229d9
--define_symbol sm_request_pairing=0x000229e5
--define_symbol sm_send_security_request=0x000234bb
--define_symbol sm_set_accepted_stk_generation_methods=0x000234e1
--define_symbol sm_set_authentication_requirements=0x000234ed
--define_symbol sm_set_encryption_key_size_range=0x000234f9
--define_symbol sscanf_bd_addr=0x000238c9
--define_symbol sysSetPublicDeviceAddr=0x00023c7d
--define_symbol uuid128_to_str=0x00024405
--define_symbol uuid_add_bluetooth_prefix=0x0002445d
--define_symbol uuid_has_bluetooth_prefix=0x0002447d
--define_symbol uxListRemove=0x00024499
--define_symbol uxQueueMessagesWaiting=0x000244c1
--define_symbol uxQueueMessagesWaitingFromISR=0x000244e9
--define_symbol uxQueueSpacesAvailable=0x00024505
--define_symbol uxTaskGetStackHighWaterMark=0x00024531
--define_symbol uxTaskPriorityGet=0x00024551
--define_symbol uxTaskPriorityGetFromISR=0x0002456d
--define_symbol vListInitialise=0x00024627
--define_symbol vListInitialiseItem=0x0002463d
--define_symbol vListInsert=0x00024643
--define_symbol vListInsertEnd=0x00024673
--define_symbol vPortEndScheduler=0x0002468d
--define_symbol vPortEnterCritical=0x000246b9
--define_symbol vPortExitCritical=0x000246fd
--define_symbol vPortFree=0x00024731
--define_symbol vPortSuppressTicksAndSleep=0x000247c5
--define_symbol vPortValidateInterruptPriority=0x000248ed
--define_symbol vQueueDelete=0x00024949
--define_symbol vQueueWaitForMessageRestricted=0x00024975
--define_symbol vTaskDelay=0x000249bd
--define_symbol vTaskInternalSetTimeOutState=0x00024a09
--define_symbol vTaskMissedYield=0x00024a19
--define_symbol vTaskPlaceOnEventList=0x00024a25
--define_symbol vTaskPlaceOnEventListRestricted=0x00024a5d
--define_symbol vTaskPriorityDisinheritAfterTimeout=0x00024a9d
--define_symbol vTaskPrioritySet=0x00024b49
--define_symbol vTaskResume=0x00024c11
--define_symbol vTaskStartScheduler=0x00024c95
--define_symbol vTaskStepTick=0x00024d25
--define_symbol vTaskSuspend=0x00024d55
--define_symbol vTaskSuspendAll=0x00024e11
--define_symbol vTaskSwitchContext=0x00024e21
--define_symbol xPortStartScheduler=0x00024ec9
--define_symbol xQueueAddToSet=0x00024f91
--define_symbol xQueueCreateCountingSemaphore=0x00024fb5
--define_symbol xQueueCreateCountingSemaphoreStatic=0x00024ff1
--define_symbol xQueueCreateMutex=0x00025035
--define_symbol xQueueCreateMutexStatic=0x0002504b
--define_symbol xQueueCreateSet=0x00025065
--define_symbol xQueueGenericCreate=0x0002506d
--define_symbol xQueueGenericCreateStatic=0x000250b9
--define_symbol xQueueGenericReset=0x00025121
--define_symbol xQueueGenericSend=0x000251ad
--define_symbol xQueueGenericSendFromISR=0x00025319
--define_symbol xQueueGiveFromISR=0x000253d9
--define_symbol xQueueGiveMutexRecursive=0x0002547d
--define_symbol xQueueIsQueueEmptyFromISR=0x000254bd
--define_symbol xQueueIsQueueFullFromISR=0x000254e1
--define_symbol xQueuePeek=0x00025509
--define_symbol xQueuePeekFromISR=0x00025631
--define_symbol xQueueReceive=0x0002569d
--define_symbol xQueueReceiveFromISR=0x000257c9
--define_symbol xQueueRemoveFromSet=0x0002585d
--define_symbol xQueueSelectFromSet=0x0002587f
--define_symbol xQueueSelectFromSetFromISR=0x00025891
--define_symbol xQueueSemaphoreTake=0x000258a5
--define_symbol xQueueTakeMutexRecursive=0x00025a11
--define_symbol xTaskCheckForTimeOut=0x00025a55
--define_symbol xTaskCreate=0x00025ac5
--define_symbol xTaskCreateStatic=0x00025b21
--define_symbol xTaskGetCurrentTaskHandle=0x00025b91
--define_symbol xTaskGetSchedulerState=0x00025b9d
--define_symbol xTaskGetTickCount=0x00025bb9
--define_symbol xTaskGetTickCountFromISR=0x00025bc5
--define_symbol xTaskIncrementTick=0x00025bd5
--define_symbol xTaskPriorityDisinherit=0x00025ca1
--define_symbol xTaskPriorityInherit=0x00025d35
--define_symbol xTaskRemoveFromEventList=0x00025dc9
--define_symbol xTaskResumeAll=0x00025e49
--define_symbol xTaskResumeFromISR=0x00025f11
--define_symbol xTimerCreate=0x00025f9d
--define_symbol xTimerCreateStatic=0x00025fd1
--define_symbol xTimerCreateTimerTask=0x00026009
--define_symbol xTimerGenericCommand=0x00026075
--define_symbol xTimerGetExpiryTime=0x000260e5
--define_symbol xTimerGetTimerDaemonTaskHandle=0x00026105
