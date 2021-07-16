
之前有个项目，要求无人机与地面站直接的通信由之前的数传改为wifi，搜了一圈，很多都属于手工调试，而且包含复杂的界面。然而实际需求要求稳定，自动化。因此为了满足这个需求只能是自己开发一个小工具。

在当前项目背景下，要实现的需求如下图所示

```mermaid
graph LR
A[无人机飞控串口A] --串口发送--> B[无人机上位机串口B]
B -- 串口发送 --> A
linkStyle 0 stroke:#ff0000,stroke-width:2px;
linkStyle 1 stroke:#0000FF,stroke-width:2px;
B -- 数据传递 -->C[无人机客户端]
C -- 数据传递  --> B
linkStyle 2 stroke:#ff0000,stroke-width:2px;
linkStyle 3 stroke:#0000FF,stroke-width:2px;
C -- TCP发送 -->D[地面站服务端]
D -- TCP发送 -->C
linkStyle 4 stroke:#ff0000,stroke-width:2px;
linkStyle 5 stroke:#0000FF,stroke-width:2px;
D -- 串口发送 --> E[无人机地面站]
E -- 串口发送 --> D
linkStyle 6 stroke:#ff0000,stroke-width:2px;
linkStyle 7 stroke:#0000FF,stroke-width:2px;
```

实际上，正常的无人机与地面之间的通信用的是数传模块，无人机和地面站之间都是通过串口连接到这个模块上。模块和模块之间的通信利用远程无线电进行通信。

<center>
<img src="https://img-blog.csdnimg.cn/20210715100630792.png" width="60%">


但是，在一些**特殊场景中**，比如不能用无线电台的地方，敏感区域等，就只能想办法用其他的手段实现无人机与地面站的通信，而利用网络通信就是一个非常有效的手段。

项目开源在Github，下载地址：[https://github.com/Li-Zhaoxi/uart2net](https://github.com/Li-Zhaoxi/uart2net)

# 1 应用前景

简单来说，串口转wifi干了什么事呢，就是将下图这个串口线，线的部分变成了无线网，或者局域网之间。
<center>
<img src="https://img-blog.csdnimg.cn/20210715101353885.png" width="60%">

别看问题简单，应用的场景可多了：
- **局域网范围优势**。拿校园网来说，校园网实际上是个超大规模的局域网，传输速度高达100MB/s，所以串口两端的设备都连上校园网，我可以在**任何地方快速地**控制设备。
- **局域网频段优势**。数传模块的频段会有冲突，但网络不会，适用于大规模控制。
- **便宜**。搞研究一般都在室内，有个路由器就够了（省下好几百数传模块的钱投资在头发上不香吗）。
- **应用范围广**。可以远程调试串口，可以模拟任何两个串口之间的通信，省下一大堆串口线。
- **公网扩展**。两个设备之间既然是利用网络通信就不仅仅局限于局域网，在无人机设备上插入SIM卡并不是什么难事，而且利用现在的5G技术，是可以快速传输无人机大量的图像数据的（我个人觉得这也是为什么要封杀5G的原因吧，尽管在民用用途不大，但在工业圈非常重要，突破了网速限制，真的可以为所欲为）。

当然，缺点很明显，**延迟会很高，受限于网络覆盖范围**，如果需要野外大范围的飞行，还是得安装数传图传模块。

TB上是有卖串口转wifi的**硬件**，我这个是**软件**，跨平台，可以安装在x86平台，也可以安装在aarch64架构的嵌入式平台（比如jetson系列的嵌入式系统）。


# 2 使用说明

## 2.1 程序编译
改程序基于QT，所以无论在哪个平台，都要安装QT所支持的库。Windows下去下载exe安装包就行，Linux下用`apt-get install` 命令是可以直接安装QT的。

```bash
sudo apt-get install qt5-default
sudo apt-get install libqt5serialport5-dev
```


**WINDOWS 下的使用方法**
1. 使用QTCreator加载当前*uart2net.pro*文件
2. 在release模式下编译。
3. 找到release版本的exe，与*uart2net.ini*单独放进一个文件夹。
4. 如果需要发布到别的电脑，按照[《QT 发布release版本》](https://www.cnblogs.com/nanmi/p/12808699.html)的方法，补充对应的dll文件。
5. 编译通过后，此工程可以删掉。
6. **配置ini文件**，双击exe即可执行。


**Linux下的使用方法（包含嵌入式Linux）**

1. 下载代码`git clone https://github.com/Li-Zhaoxi/uart2net`
2. 进入文件路径`cd uart2net`
3. 输入`qmake uart2net.pro`
4. 编译`make all -j6`
5. 编译无错通过后，根据设备**修改对应的ini文件**。
6. 输入`sudo ./uart2net` (串口读写必须是管理员权限，也可以用chmod改掉这个串口权限)

## 2.2 配置文件用法
配置文件可以用记事本打开，==切记修改时候里面不能有中文==：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210716152724651.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1poYW94aV9MaQ==,size_16,color_FFFFFF,t_70)
- **uart2net**
  - **type**：表示是服务端还是客户端，1表示服务端，2表示客户端
  - **heartbeattime**：检测心跳，客户端必须设置（默认2000即可），否则无法检测断线并自动重连，服务器如果通信频繁可以设置0。（网络断开时候，程序是没法自动检测的，只能通过心跳）。
  - **RecordLog**：默认0不要动，本意是想记录通信之间传递的数据（因为我实现一半时候觉得没必要）。
  - **showmessage**：在控制台显示传递的数据，设置0就行。（因为设置1时候，满屏的二进制数，你也看不过来，前期自己调试用的）。
- **serial-port**
  - **number **：串口号。windows下一般为 **COM3** （3根据实际情况调整），Linux下一般为 **/dev/ttyS3**，后面的数字同样根据实际设备号调整。
  - **btl**：串口波特率。
- **TCP**：
  - **hostip**：服务端IP地址（仅用于客户端，但在服务端你不能删掉这行）。
  - **port**：服务端端口号。

## 2.3 一些效果图
服务端，设备连接上之后会有显示，设备重连也会有显示。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210716161713591.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1poYW94aV9MaQ==,size_16,color_FFFFFF,t_70)

客户端，最开始时候服务端还没开，一直在重连。
![在这里插入图片描述](https://img-blog.csdnimg.cn/2021071616194231.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L1poYW94aV9MaQ==,size_16,color_FFFFFF,t_70)

客户端，根据设置的心跳，2秒内没消息就重连。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20210716162039426.png)


# 3 总结
写这个小工具大概花了我2周左右的时间，主要就利用QT的串口和网络通信，并没有使用多高深的软件技术。后面移植到无人机系统中前前后后联调修了一堆bug，对于我来说，这个东西的最大价值也许就是其稳定性，在不断的调试中得到了最优版本。

在未来有需求的话也会对其进行进一步升级（毕竟这东西思想上容易，实际上调试巨麻烦），比如：
- 心跳包不再占用数据通信的socket，两端都可以检测对方是否还活着
- 现在是一对设备就创建一个服务端和客户端，后续也会升级为创建一个服务器，每个设备都是一个客户端（类似局域网聊天器那种）。
- 有效的记录Log。设备发生意外，后续检查时候可以通过日志查看最后发送消息。（如果追求数据完整性，就得进来个数据存一次，导致IO变多，如果满足缓存再存，设备出故障容易异常关机，导致数据丢失）。

这次公布的是**稳定版本**，当然后续要是自己碰到需要更高级的需求，自己也会升级下这个。








