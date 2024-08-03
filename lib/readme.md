# 版本记录：

### BLE_2P4G_Switch.lib

截至20240803的最新版本，以后lib文件不再此处更新，只更新例程中的lib文件。

...\ING_2P4G\ING_BLE_2P4G_example\2P4G

### BLE_2P4G_Switch_V1.3.0.lib

- 打包了sdk源码，基于V8.4.1
- 增加了tx_pkt_event中断源
- 修改了tx配置后while死等的方式
- 修复了初始化为2Mphy通讯失败的问题

### BLE_2P4G_Switch_V1.2.1.lib

修改了浮点数不能运算的问题

### BLE_2P4G_Switch_V1.2.0.lib

增加了RSSI扫描接口，可以扫描特定频点的拥挤程度

原本2.4G占用了Timer0，现在释放了。

### BLE_2P4G_Switch_V1.1.2.lib

自本版本开始主要更新lib文件，sample除非说明不更新。

减小了Lib里申请的链路层ram，从而让用户可以申请更多的链路层空间。实验申请到17K没问题，更多的还没试验。 