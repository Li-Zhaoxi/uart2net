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
         // ���ﲹ��ʧ�ܵĽ���취
     }

     err = tcp_server->run(tcpport);
     if(err <= 0)
     {
         fprintf(stderr, "UART2NET tcp create failed");
         return;
         // ���ﲹ��ʧ�ܵĽ���취

     }

     // ������������ÿ��ָ��ʱ�䷢��һ����
     if(uart2netconfig.heartbeattime > 0)
     {
         connect(&heartbeattimer, &QTimer::timeout,
                 this, &UART2NET::send_heartbeats);
         heartbeattimer.start(uart2netconfig.heartbeattime);
     }

     // �����źŲۣ����ڽ���+TCP����
     connect(serialport, SIGNAL(signals_serial_receive(QByteArray)),
             this, SLOT(transport_serial_to_tcp(QByteArray)));
     // �����źŲۣ�tcp����+���ڷ���
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
        // ���ﲹ��ʧ�ܵĽ���취
    }

    err = tcp_client->run(hostip, tcpport);
    if(err <= 0)
    {
        fprintf(stderr, "UART2NET tcp create failed");
        return;
        // ���ﲹ��ʧ�ܵĽ���취
    }
    // �����źŲۣ����ڽ���+TCP����
    connect(serialport, SIGNAL(signals_serial_receive(QByteArray)),
            this, SLOT(transport_serial_to_tcp(QByteArray)));
    // �����źŲۣ�tcp����+���ڷ���
    connect(tcp_client, SIGNAL(signals_socket_receive(QByteArray)),
            this, SLOT(transport_tcp_to_serial(QByteArray)));

    connect(this, &UART2NET::signals_reconnect_host,
            this, &UART2NET::reconnect);
    // ���¿ͻ����������,����ʱ�����0��ζ����Ҫ�������
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
    if(uart2netconfig.isServer == UART2NET_SERVER) // ��������
    {
        tcp_server->send(serialdata, 0);
        // �������ݴ洢����


    }
    else if(uart2netconfig.isServer == UART2NET_CLIENT) // �ͻ���
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
    // �������һ���յ�tcpʱ��
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

    if(uart2netconfig.isServer == UART2NET_SERVER) // ������������
    {
        run_server(uart2netconfig.comnum, uart2netconfig.btl,
                   uart2netconfig.tcpport);
    }
    else if(uart2netconfig.isServer == UART2NET_CLIENT) // �����ͻ���
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
