# ING_BLE_2P4G_V1.0.0

## 该例程的作用？
  * 该例程演示了如何在**ING916xx**上使用桃芯自研**2.4G**的API进行通讯；
  * 桃芯自研的**2.4G**不同于标准的**2.4G**协议(例如ESB)，但运行方式和使用方式与其类似；
  * 桃芯自研的**2.4G**也与蓝牙协议不同，相对于蓝牙协议，它的使用更加灵活，也能获得更高的通讯速率；
  * 用户可以基于此例程弄明白桃芯**2.4G**的使用方式，并将它应用到键盘、鼠标等应用中。

## 如何测试该例程？
  * 找两套**ING916**的开发板，一块儿板子充当**master**，另外一块儿充当**slave**；
  * 使用**ingWizard**工具**import**该例程（假设已经安装好**keil**和**ingWizard**等必要环境）；
  * 右单击**open project ...**打开例程；
  * 将**keil**工程宏定义设置为 **DEF_MASTER=1** ，即将工程设置为**master**，并编译程序；
  * 右单击**ingWizard**上工程启动**downloader**下载工具，用串口方式将**master**例程烧录到**master**的开发板上；
  * 将keil工程宏定义设置为 **DEF_MASTER=0** ，即将工程设置为**slave**，并重新编译程序；
  * 用**downloader**将**slave**例程烧录到**slave**的开发板上；
  * 打开两个串口助手，分别观测两个开发板的串口日志，波特率**115200**；
  * 按下复位键，复位两个开发板，分别会打印开机日志；
  * 两个开发板开机默认处于**BLE**模式，按下一次**KEY2**按键，会切换到**2.4G**模式，再次按下一次**KEY2**键则进入到2.4G发送（**master**）和**2.4G**接收（**slave**）状态；
  * **master**开发板打印：**【Start to TX ... 】**则代表进入了发送状态；
  * **slave**开发板打印：【**Start to RX ...**】则代表进入了接收状态；
  * **master**开发板会统计发送与接收**ACK**的情况，会显示测试包数，丢失包数，和包速率等；

## 选用什么开发板
  * 选用**ING916XX**的开发板，一个功能板(版号：**DB72C8K1A**)+一个核心板(版号：**DB682CC2A**)组成一套开发板；
  * 每个开发板至少需要一个**micro-USB**数据线；
  * 注意核心板需要安装天线，以防信号较差，影响通讯速率。

## 一些重要信息
  * 目前**master**与**slave**通讯使用带应答的方式；
  * **master**发送和接收应答的流程如下：
    * **master**发送数据
    * **slave**接收数据
    * **slave**返回应答数据
    * **master**接收应答数据
  * 事件与中断：
    * **slave**接收到数据后会产生接收数据中断（可屏蔽）；
    * **slave**发送完应答后会产生接收过程结束事件中断（不可屏蔽），标记接收一个完整的包；
    * **master**发送完毕无中断事件；
    * **master**接收到应答会产生接收数据中断（可屏蔽）和接收事件中断（不可屏蔽）。
  * 从**2.4G**模式切换到**BLE**模式前，必须确保**2.4G**处于空闲状态；
  * 从**BLE**模式切换到**2.4G**模式前，必须确保**BLE**处于空闲状态，例如，没有广播、连接、扫描等事件。