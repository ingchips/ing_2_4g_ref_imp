--define_symbol att_dispatch_client_can_send_now=0x020051dd
--define_symbol att_dispatch_client_request_can_send_now_event=0x020051e3
--define_symbol att_dispatch_register_client=0x020051e9
--define_symbol att_dispatch_register_server=0x020051fd
--define_symbol att_dispatch_server_can_send_now=0x02005211
--define_symbol att_dispatch_server_request_can_send_now_event=0x02005217
--define_symbol att_emit_general_event=0x020052c9
--define_symbol att_server_can_send_packet_now=0x020059fd
--define_symbol att_server_deferred_read_response=0x02005a01
--define_symbol att_server_get_mtu=0x02005a19
--define_symbol att_server_indicate=0x02005a85
--define_symbol att_server_init=0x02005b09
--define_symbol att_server_notify=0x02005b45
--define_symbol att_server_register_packet_handler=0x02005c5d
--define_symbol att_server_request_can_send_now_event=0x02005c8f
--define_symbol att_set_db=0x02005cab
--define_symbol att_set_read_callback=0x02005cbd
--define_symbol att_set_write_callback=0x02005cc9
--define_symbol bd_addr_cmp=0x02005e99
--define_symbol bd_addr_copy=0x02005e9f
--define_symbol bd_addr_to_str=0x02005ea9
--define_symbol big_endian_read_16=0x02005ee1
--define_symbol big_endian_read_32=0x02005ee9
--define_symbol big_endian_store_16=0x02005efd
--define_symbol big_endian_store_32=0x02005f09
--define_symbol btstack_config=0x02005f35
--define_symbol btstack_get_capabilities=0x02005f41
--define_symbol btstack_memory_pool_create=0x0200608b
--define_symbol btstack_memory_pool_free=0x020060b5
--define_symbol btstack_memory_pool_get=0x02006115
--define_symbol btstack_push_user_msg=0x0200617d
--define_symbol btstack_push_user_runnable=0x02006189
--define_symbol btstack_reset=0x02006195
--define_symbol char_for_nibble=0x020063c3
--define_symbol eTaskConfirmSleepModeStatus=0x020066fd
--define_symbol gap_add_dev_to_periodic_list=0x02006d41
--define_symbol gap_add_whitelist=0x02006d51
--define_symbol gap_aes_encrypt=0x02006d5d
--define_symbol gap_clear_white_lists=0x02006d95
--define_symbol gap_clr_adv_set=0x02006da1
--define_symbol gap_clr_periodic_adv_list=0x02006dad
--define_symbol gap_create_connection_cancel=0x02006db9
--define_symbol gap_default_periodic_adv_sync_transfer_param=0x02006dc5
--define_symbol gap_disconnect=0x02006ddd
--define_symbol gap_disconnect2=0x02006de5
--define_symbol gap_disconnect_all=0x02006e11
--define_symbol gap_ext_create_connection=0x02006e51
--define_symbol gap_get_connection_parameter_range=0x02006f29
--define_symbol gap_le_read_channel_map=0x02006f61
--define_symbol gap_periodic_adv_create_sync=0x02006fc1
--define_symbol gap_periodic_adv_create_sync_cancel=0x02006fe5
--define_symbol gap_periodic_adv_set_info_transfer=0x02006ff1
--define_symbol gap_periodic_adv_sync_transfer=0x02007001
--define_symbol gap_periodic_adv_sync_transfer_param=0x02007011
--define_symbol gap_periodic_adv_term_sync=0x0200702d
--define_symbol gap_read_antenna_info=0x020070b5
--define_symbol gap_read_periodic_adv_list_size=0x020070c1
--define_symbol gap_read_phy=0x020070cd
--define_symbol gap_read_remote_used_features=0x020070d9
--define_symbol gap_read_remote_version=0x020070e5
--define_symbol gap_read_rssi=0x020070f1
--define_symbol gap_read_white_lists_size=0x020070fd
--define_symbol gap_remove_whitelist=0x02007109
--define_symbol gap_rmv_adv_set=0x02007185
--define_symbol gap_rmv_dev_from_periodic_list=0x02007191
--define_symbol gap_rx_test_v2=0x020071a1
--define_symbol gap_rx_test_v3=0x020071b1
--define_symbol gap_set_adv_set_random_addr=0x020071fd
--define_symbol gap_set_callback_for_next_hci=0x02007221
--define_symbol gap_set_connection_cte_request_enable=0x02007241
--define_symbol gap_set_connection_cte_response_enable=0x0200725d
--define_symbol gap_set_connection_cte_rx_param=0x0200726d
--define_symbol gap_set_connection_cte_tx_param=0x020072c1
--define_symbol gap_set_connection_parameter_range=0x0200730d
--define_symbol gap_set_connectionless_cte_tx_enable=0x02007325
--define_symbol gap_set_connectionless_cte_tx_param=0x02007335
--define_symbol gap_set_connectionless_iq_sampling_enable=0x02007391
--define_symbol gap_set_data_length=0x020073ed
--define_symbol gap_set_def_phy=0x02007405
--define_symbol gap_set_ext_adv_data=0x02007415
--define_symbol gap_set_ext_adv_enable=0x0200742d
--define_symbol gap_set_ext_adv_para=0x0200749d
--define_symbol gap_set_ext_scan_enable=0x0200755d
--define_symbol gap_set_ext_scan_para=0x02007575
--define_symbol gap_set_ext_scan_response_data=0x02007615
--define_symbol gap_set_host_channel_classification=0x0200762d
--define_symbol gap_set_periodic_adv_data=0x0200763d
--define_symbol gap_set_periodic_adv_enable=0x020076ad
--define_symbol gap_set_periodic_adv_para=0x020076bd
--define_symbol gap_set_periodic_adv_rx_enable=0x020076d5
--define_symbol gap_set_phy=0x020076e5
--define_symbol gap_set_random_device_address=0x02007701
--define_symbol gap_start_ccm=0x0200771d
--define_symbol gap_test_end=0x02007765
--define_symbol gap_tx_test_v2=0x02007771
--define_symbol gap_tx_test_v4=0x02007789
--define_symbol gap_update_connection_parameters=0x020077ad
--define_symbol gap_vendor_tx_continuous_wave=0x020077ed
--define_symbol gatt_client_cancel_write=0x02007d15
--define_symbol gatt_client_discover_characteristic_descriptors=0x02007d3b
--define_symbol gatt_client_discover_characteristics_for_handle_range_by_uuid128=0x02007d7b
--define_symbol gatt_client_discover_characteristics_for_handle_range_by_uuid16=0x02007dcb
--define_symbol gatt_client_discover_characteristics_for_service=0x02007e1b
--define_symbol gatt_client_discover_primary_services=0x02007e51
--define_symbol gatt_client_discover_primary_services_by_uuid128=0x02007e83
--define_symbol gatt_client_discover_primary_services_by_uuid16=0x02007ec7
--define_symbol gatt_client_execute_write=0x02007f05
--define_symbol gatt_client_find_included_services_for_service=0x02007f2b
--define_symbol gatt_client_get_mtu=0x02007f59
--define_symbol gatt_client_is_ready=0x02008025
--define_symbol gatt_client_listen_for_characteristic_value_updates=0x0200803b
--define_symbol gatt_client_prepare_write=0x0200805b
--define_symbol gatt_client_read_characteristic_descriptor_using_descriptor_handle=0x02008097
--define_symbol gatt_client_read_long_characteristic_descriptor_using_descriptor_handle=0x020080c1
--define_symbol gatt_client_read_long_characteristic_descriptor_using_descriptor_handle_with_offset=0x020080c7
--define_symbol gatt_client_read_long_value_of_characteristic_using_value_handle=0x020080f5
--define_symbol gatt_client_read_long_value_of_characteristic_using_value_handle_with_offset=0x020080fb
--define_symbol gatt_client_read_multiple_characteristic_values=0x02008129
--define_symbol gatt_client_read_value_of_characteristic_using_value_handle=0x02008159
--define_symbol gatt_client_read_value_of_characteristics_by_uuid128=0x02008187
--define_symbol gatt_client_read_value_of_characteristics_by_uuid16=0x020081d3
--define_symbol gatt_client_register_handler=0x0200821d
--define_symbol gatt_client_reliable_write_long_value_of_characteristic=0x02008229
--define_symbol gatt_client_signed_write_without_response=0x02008631
--define_symbol gatt_client_write_characteristic_descriptor_using_descriptor_handle=0x020086f5
--define_symbol gatt_client_write_client_characteristic_configuration=0x0200872f
--define_symbol gatt_client_write_long_characteristic_descriptor_using_descriptor_handle=0x02008781
--define_symbol gatt_client_write_long_characteristic_descriptor_using_descriptor_handle_with_offset=0x02008791
--define_symbol gatt_client_write_long_value_of_characteristic=0x020087cd
--define_symbol gatt_client_write_long_value_of_characteristic_with_offset=0x020087dd
--define_symbol gatt_client_write_value_of_characteristic=0x02008819
--define_symbol gatt_client_write_value_of_characteristic_without_response=0x0200884f
--define_symbol hci_add_event_handler=0x02009e21
--define_symbol hci_power_control=0x0200a5ad
--define_symbol hci_register_acl_packet_handler=0x0200a761
--define_symbol kv_commit=0x0200ada5
--define_symbol kv_get=0x0200ae01
--define_symbol kv_init=0x0200ae0d
--define_symbol kv_init_backend=0x0200ae89
--define_symbol kv_put=0x0200ae9d
--define_symbol kv_remove=0x0200aea9
--define_symbol kv_remove_all=0x0200aedd
--define_symbol kv_value_modified=0x0200af0d
--define_symbol kv_value_modified_of_key=0x0200af29
--define_symbol kv_visit=0x0200af35
--define_symbol l2cap_add_event_handler=0x0200afc5
--define_symbol l2cap_can_send_packet_now=0x0200afd5
--define_symbol l2cap_create_le_credit_based_connection_request=0x0200b199
--define_symbol l2cap_credit_based_send=0x0200b2e1
--define_symbol l2cap_credit_based_send_continue=0x0200b30d
--define_symbol l2cap_disconnect=0x0200b389
--define_symbol l2cap_get_le_credit_based_connection_credits=0x0200b56d
--define_symbol l2cap_get_peer_mtu_for_local_cid=0x0200b589
--define_symbol l2cap_init=0x0200b9b5
--define_symbol l2cap_le_send_flow_control_credit=0x0200baa9
--define_symbol l2cap_max_le_mtu=0x0200bda5
--define_symbol l2cap_register_packet_handler=0x0200becd
--define_symbol l2cap_register_service=0x0200bed9
--define_symbol l2cap_request_can_send_now_event=0x0200bfe9
--define_symbol l2cap_request_connection_parameter_update=0x0200c003
--define_symbol l2cap_send_echo_request=0x0200c4d1
--define_symbol l2cap_unregister_service=0x0200c5b1
--define_symbol le_device_db_add=0x0200c609
--define_symbol le_device_db_find=0x0200c6e1
--define_symbol le_device_db_from_key=0x0200c70d
--define_symbol le_device_db_iter_cur=0x0200c715
--define_symbol le_device_db_iter_cur_key=0x0200c719
--define_symbol le_device_db_iter_init=0x0200c71d
--define_symbol le_device_db_iter_next=0x0200c725
--define_symbol le_device_db_remove_key=0x0200c74b
--define_symbol ll_adjust_conn_peer_tx_power=0x0200c779
--define_symbol ll_aes_encrypt=0x0200c7a1
--define_symbol ll_config=0x0200c815
--define_symbol ll_free=0x0200c84b
--define_symbol ll_get_capabilities=0x0200c855
--define_symbol ll_get_heap_free_size=0x0200c875
--define_symbol ll_get_states=0x0200c885
--define_symbol ll_hint_on_ce_len=0x0200c921
--define_symbol ll_legacy_adv_set_interval=0x0200c959
--define_symbol ll_malloc=0x0200c969
--define_symbol ll_register_hci_acl_previewer=0x0200ca81
--define_symbol ll_scan_set_fixed_channel=0x0200cae5
--define_symbol ll_set_adv_access_address=0x0200ccfd
--define_symbol ll_set_adv_coded_scheme=0x0200cd09
--define_symbol ll_set_conn_acl_report_latency=0x0200cd39
--define_symbol ll_set_conn_coded_scheme=0x0200cd65
--define_symbol ll_set_conn_latency=0x0200cd8d
--define_symbol ll_set_conn_tx_power=0x0200cdb9
--define_symbol ll_set_def_antenna=0x0200cdf1
--define_symbol ll_set_initiating_coded_scheme=0x0200ce11
--define_symbol ll_set_max_conn_number=0x0200ce1d
--define_symbol ll_set_tx_power_range=0x0200ceb1
--define_symbol nibble_for_char=0x0201d1d9
--define_symbol platform_calibrate_rt_clk=0x0201d261
--define_symbol platform_call_on_stack=0x020030fb
--define_symbol platform_cancel_us_timer=0x0201d265
--define_symbol platform_config=0x0201d279
--define_symbol platform_create_us_timer=0x0201d3ad
--define_symbol platform_delete_timer=0x0201d3c1
--define_symbol platform_enable_irq=0x0201d3c9
--define_symbol platform_get_current_task=0x0201d41d
--define_symbol platform_get_gen_os_driver=0x0201d441
--define_symbol platform_get_heap_status=0x0201d449
--define_symbol platform_get_link_layer_interf=0x0201d461
--define_symbol platform_get_task_handle=0x0201d469
--define_symbol platform_get_timer_counter=0x0201d489
--define_symbol platform_get_us_time=0x0201d48d
--define_symbol platform_get_version=0x0201d491
--define_symbol platform_hrng=0x0201d4ad
--define_symbol platform_install_isr_stack=0x0201d4b5
--define_symbol platform_install_task_stack=0x0201d4c1
--define_symbol platform_patch_rf_init_data=0x0201d4f9
--define_symbol platform_printf=0x0201d505
--define_symbol platform_raise_assertion=0x0201d519
--define_symbol platform_rand=0x0201d52d
--define_symbol platform_read_info=0x0201d531
--define_symbol platform_read_persistent_reg=0x0201d561
--define_symbol platform_reset=0x0201d581
--define_symbol platform_rt_rc_auto_tune=0x0201d595
--define_symbol platform_rt_rc_auto_tune2=0x0201d59d
--define_symbol platform_rt_rc_tune=0x0201d5fd
--define_symbol platform_set_abs_timer=0x0201d629
--define_symbol platform_set_evt_callback=0x0201d62d
--define_symbol platform_set_evt_callback_table=0x0201d641
--define_symbol platform_set_irq_callback=0x0201d64d
--define_symbol platform_set_irq_callback_table=0x0201d669
--define_symbol platform_set_rf_clk_source=0x0201d675
--define_symbol platform_set_rf_init_data=0x0201d681
--define_symbol platform_set_rf_power_mapping=0x0201d68d
--define_symbol platform_set_timer=0x0201d699
--define_symbol platform_shutdown=0x0201d69d
--define_symbol platform_switch_app=0x0201d6a1
--define_symbol platform_trace_raw=0x0201d6b9
--define_symbol platform_write_persistent_reg=0x0201d6d1
--define_symbol printf_hexdump=0x0201d8a9
--define_symbol pvPortMalloc=0x0201e2dd
--define_symbol pvTaskIncrementMutexHeldCount=0x0201e3c5
--define_symbol pvTimerGetTimerID=0x0201e3dd
--define_symbol pxPortInitialiseStack=0x0201e409
--define_symbol reverse_128=0x0201e5f1
--define_symbol reverse_24=0x0201e5f7
--define_symbol reverse_256=0x0201e5fd
--define_symbol reverse_48=0x0201e603
--define_symbol reverse_56=0x0201e609
--define_symbol reverse_64=0x0201e60f
--define_symbol reverse_bd_addr=0x0201e615
--define_symbol reverse_bytes=0x0201e61b
--define_symbol sm_add_event_handler=0x0201e921
--define_symbol sm_address_resolution_lookup=0x0201ea79
--define_symbol sm_authenticated=0x0201ee21
--define_symbol sm_authorization_decline=0x0201ee2f
--define_symbol sm_authorization_grant=0x0201ee4f
--define_symbol sm_authorization_state=0x0201ee6f
--define_symbol sm_bonding_decline=0x0201ee89
--define_symbol sm_config=0x0201f2dd
--define_symbol sm_config_conn=0x0201f311
--define_symbol sm_encryption_key_size=0x0201f4cb
--define_symbol sm_just_works_confirm=0x0201fa61
--define_symbol sm_le_device_key=0x0201fd99
--define_symbol sm_passkey_input=0x0201fe2f
--define_symbol sm_private_random_address_generation_get=0x02020205
--define_symbol sm_private_random_address_generation_get_mode=0x0202020d
--define_symbol sm_private_random_address_generation_set_mode=0x02020219
--define_symbol sm_private_random_address_generation_set_update_period=0x02020241
--define_symbol sm_register_external_ltk_callback=0x0202037d
--define_symbol sm_register_oob_data_callback=0x02020389
--define_symbol sm_request_pairing=0x02020395
--define_symbol sm_send_security_request=0x02020e83
--define_symbol sm_set_accepted_stk_generation_methods=0x02020ea9
--define_symbol sm_set_authentication_requirements=0x02020eb5
--define_symbol sm_set_encryption_key_size_range=0x02020ec5
--define_symbol sscanf_bd_addr=0x02021215
--define_symbol sysSetPublicDeviceAddr=0x020212e9
--define_symbol uuid128_to_str=0x02021aad
--define_symbol uuid_add_bluetooth_prefix=0x02021b05
--define_symbol uuid_has_bluetooth_prefix=0x02021b25
--define_symbol uxListRemove=0x02021b41
--define_symbol uxQueueMessagesWaiting=0x02021b69
--define_symbol uxQueueMessagesWaitingFromISR=0x02021b91
--define_symbol uxQueueSpacesAvailable=0x02021bad
--define_symbol uxTaskGetStackHighWaterMark=0x02021bd9
--define_symbol uxTaskPriorityGet=0x02021bf9
--define_symbol uxTaskPriorityGetFromISR=0x02021c15
--define_symbol vListInitialise=0x02021c7b
--define_symbol vListInitialiseItem=0x02021c91
--define_symbol vListInsert=0x02021c97
--define_symbol vListInsertEnd=0x02021cc7
--define_symbol vPortEndScheduler=0x02021ce1
--define_symbol vPortEnterCritical=0x2000033b
--define_symbol vPortExitCritical=0x20000375
--define_symbol vPortFree=0x02021d0d
--define_symbol vPortSuppressTicksAndSleep=0x200003a1
--define_symbol vPortValidateInterruptPriority=0x02021db1
--define_symbol vQueueDelete=0x02021e0d
--define_symbol vQueueWaitForMessageRestricted=0x02021e39
--define_symbol vTaskDelay=0x02021e7d
--define_symbol vTaskInternalSetTimeOutState=0x02021ec9
--define_symbol vTaskMissedYield=0x02021ed9
--define_symbol vTaskPlaceOnEventList=0x02021ee5
--define_symbol vTaskPlaceOnEventListRestricted=0x02021f1d
--define_symbol vTaskPriorityDisinheritAfterTimeout=0x02021f5d
--define_symbol vTaskPrioritySet=0x02022009
--define_symbol vTaskResume=0x020220d1
--define_symbol vTaskStartScheduler=0x02022155
--define_symbol vTaskStepTick=0x2000071f
--define_symbol vTaskSuspend=0x020221e5
--define_symbol vTaskSuspendAll=0x20000693
--define_symbol vTaskSwitchContext=0x020222a1
--define_symbol xPortStartScheduler=0x02022349
--define_symbol xQueueAddToSet=0x0202244d
--define_symbol xQueueCreateCountingSemaphore=0x02022471
--define_symbol xQueueCreateCountingSemaphoreStatic=0x020224ad
--define_symbol xQueueCreateMutex=0x020224f1
--define_symbol xQueueCreateMutexStatic=0x02022507
--define_symbol xQueueCreateSet=0x02022521
--define_symbol xQueueGenericCreate=0x02022529
--define_symbol xQueueGenericCreateStatic=0x02022575
--define_symbol xQueueGenericReset=0x020225dd
--define_symbol xQueueGenericSend=0x02022669
--define_symbol xQueueGenericSendFromISR=0x020227d5
--define_symbol xQueueGiveFromISR=0x02022895
--define_symbol xQueueGiveMutexRecursive=0x02022939
--define_symbol xQueueIsQueueEmptyFromISR=0x02022979
--define_symbol xQueueIsQueueFullFromISR=0x0202299d
--define_symbol xQueuePeek=0x020229c5
--define_symbol xQueuePeekFromISR=0x02022aed
--define_symbol xQueueReceive=0x02022b59
--define_symbol xQueueReceiveFromISR=0x02022c85
--define_symbol xQueueRemoveFromSet=0x02022d19
--define_symbol xQueueSelectFromSet=0x02022d3b
--define_symbol xQueueSelectFromSetFromISR=0x02022d4d
--define_symbol xQueueSemaphoreTake=0x02022d61
--define_symbol xQueueTakeMutexRecursive=0x02022ecd
--define_symbol xTaskCheckForTimeOut=0x02022f11
--define_symbol xTaskCreate=0x02022f81
--define_symbol xTaskCreateStatic=0x02022fdd
--define_symbol xTaskGetCurrentTaskHandle=0x0202304d
--define_symbol xTaskGetSchedulerState=0x02023059
--define_symbol xTaskGetTickCount=0x02023075
--define_symbol xTaskGetTickCountFromISR=0x02023081
--define_symbol xTaskIncrementTick=0x20000525
--define_symbol xTaskPriorityDisinherit=0x02023091
--define_symbol xTaskPriorityInherit=0x02023125
--define_symbol xTaskRemoveFromEventList=0x020231b9
--define_symbol xTaskResumeAll=0x200005df
--define_symbol xTaskResumeFromISR=0x02023239
--define_symbol xTimerCreate=0x020232c5
--define_symbol xTimerCreateStatic=0x020232f9
--define_symbol xTimerCreateTimerTask=0x02023331
--define_symbol xTimerGenericCommand=0x0202339d
--define_symbol xTimerGetExpiryTime=0x0202340d
--define_symbol xTimerGetTimerDaemonTaskHandle=0x0202342d
