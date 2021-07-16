#include "uart2net.h"


UART2NET::UART2NET()
{
    tcp_server = new TcpServer;
    tcp_client = new TcpClient;
    serialport = new SerialPort;

}

UART2NET::~UART2NET()
{
    close();
    delete[] serialport;
    delete[] tcp_server;
    delete[] tcp_client;
}

 void UART2NET::run_server(QString comnum, qint32 btl, quint16 tcpport)
 {
     uart2netconfig.isServer = UART2NET_SERVER;

     int err;

     err = serialport->run(comnum, btl);
     if(err <=0 )
     {
         fprintf(stderr, "UART2NET serialport open failed");
         return;
         // 这里补充失败的解决办法
     }

     err = tcp_server->run(tcpport);
     if(err <= 0)
     {
         fprintf(stderr, "UART2NET tcp create failed");
         return;
         // 这里补充失败的解决办法

     }

     // 设置心跳包，每隔指定时间发送一个包
     if(uart2netconfig.heartbeattime > 0)
     {
         connect(&heartbeattimer, &QTimer::timeout,
                 this, &UART2NET::send_heartbeats);
         heartbeattimer.start(uart2netconfig.heartbeattime);
     }

     // 连接信号槽：串口接收+TCP发送
     connect(serialport, SIGNAL(signals_serial_receive(QByteArray)),
             this, SLOT(transport_serial_to_tcp(QByteArray)));
     // 连接信号槽：tcp接收+串口发送
     connect(tcp_server, SIGNAL(signals_socket_receive(QByteArray, int)),
             this, SLOT(transport_tcp_to_serial(QByteArray)));

 }

void UART2NET::run_client(QString comnum, qint32 btl, QString hostip, quint16 tcpport)
{
    uart2netconfig.isServer = UART2NET_CLIENT;
    _config = uart2netconfig;
    int err;

    err = serialport->run(comnum, btl);
    if(err <=0 )
    {
        fprintf(stderr, "UART2NET serialport open failed");
        return;
        // 这里补充失败的解决办法
    }

    err = tcp_client->run(hostip, tcpport);
    if(err <= 0)
    {
        fprintf(stderr, "UART2NET tcp create failed");
        return;
        // 这里补充失败的解决办法
    }
    // 连接信号槽：串口接收+TCP发送
    connect(serialport, SIGNAL(signals_serial_receive(QByteArray)),
            this, SLOT(transport_serial_to_tcp(QByteArray)));
    // 连接信号槽：tcp接收+串口发送
    connect(tcp_client, SIGNAL(signals_socket_receive(QByteArray)),
            this, SLOT(transport_tcp_to_serial(QByteArray)));

    connect(this, &UART2NET::signals_reconnect_host,
            this, &UART2NET::reconnect);
    // 更新客户端心跳检测,心跳时间大于0意味着需要心跳检测
    T_disconnect = uart2netconfig.heartbeattime;
    if(uart2netconfig.heartbeattime > 0)
    {
        //qDebug() << "The time for heartbeating is " << uart2netconfig.heartbeattime;
        T_disconnect += 100;
        connect(&heartbeattimer, &QTimer::timeout,
                this, &UART2NET::judge_alive);
        heartbeattimer.start(uart2netconfig.heartbeattime);
        lasttime = QDateTime::currentDateTime();
    }

}

void UART2NET::transport_serial_to_tcp(QByteArray serialdata)
{
    //printf("get serial port *****, %d\n", isServer);
    if(uart2netconfig.isServer == UART2NET_SERVER) // 服务器端
    {
        tcp_server->send(serialdata, 0);
        // 进行数据存储问题


    }
    else if(uart2netconfig.isServer == UART2NET_CLIENT) // 客户端
    {
        //printf("get serial port *****\n");
        //qDebug() << serialdata;
        //printf("%d\n", serialdata.length());
        tcp_client->send(serialdata);
    }
    //write_log(serialdata, "serial");
}


void UART2NET::transport_tcp_to_serial(QByteArray tcpdata)
{
    // 更新最后一次收到tcp时间
    lasttime = QDateTime::currentDateTime();
    if(serialport != nullptr)
    {
        serialport->send(tcpdata);
    }

    //write_log(tcpdata, "net");
}


void UART2NET::close()
{
    serialport->close();
    tcp_server->close();
    tcp_client->close();
    close_log();
}

void UART2NET::uart2net_safe_quit()
{
    printf("quit\n");
    QMutex mutex;
    QWaitCondition sleep;
    mutex.lock();
    sleep.wait(&mutex, 5000);
    mutex.unlock();
    close();
}


void UART2NET::run_uart2net()
{

    if(uart2netconfig.isServer == UART2NET_SERVER) // 创建服务器端
    {
        run_server(uart2netconfig.comnum, uart2netconfig.btl,
                   uart2netconfig.tcpport);
    }
    else if(uart2netconfig.isServer == UART2NET_CLIENT) // 创建客户端
    {
        run_client(uart2netconfig.comnum, uart2netconfig.btl,
                   uart2netconfig.hostip, uart2netconfig.tcpport);
    }

}


void UART2NET::send_heartbeats()
{
    if(uart2netconfig.isServer == UART2NET_SERVER)
    {
        QByteArray beatarray;
        beatarray.resize(2);
        beatarray[0] = 0;
        beatarray[1] = 1;
        if(tcp_server != nullptr )
        {
            tcp_server->send(beatarray, 0);
        }
    }
}


void UART2NET::judge_alive()
{
    if(lasttime.msecsTo(QDateTime::currentDateTime()) > T_disconnect)
    {
        qDebug() << "The client detects that the server is disconnected and reconnects";
        emit signals_reconnect_host();
    }
    //else
    //    qDebug() << "safe";
}

void UART2NET::reconnect()
{
    if(tcp_client->reconnect() > 0)
    {
        qDebug() << "Client reconnected successfully";
    }
    else {
        qDebug() << "Failed to reconnect client, try it again";
        emit signals_reconnect_host();
    }
}


void UART2NET::slots_about_toquit()
{
    printf("The process of quit.\n");

    QTime t;
    t.start();
    while(t.elapsed()<5000);

}
