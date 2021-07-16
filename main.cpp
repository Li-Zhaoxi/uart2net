#include <QCoreApplication>

#include <QSerialPort>
#include <iostream>
//#include <Windows.h>
#include <QDateTime>

#include "tcpclinet.h"
#include "tcpserver.h"
#include "uart2net.h"


using namespace std;



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // FUN1: 写一个配置示例
    //UART2NET::write_an_example();

    // FUN2: 读配置示例
    //UART2NET::UART2NETCONFIG config;
    //UART2NET::read_uart2net_config(config);

    // FUN3: 创建服务器端示例

    UART2NET uart2net;

    //uart2net.write_uart2net_iniconfig();
    int res = uart2net.read_uart2net_iniconfig();
    if(res != UART2NET_SUCCESS)
    {
        fprintf(stderr, "Config File Error %d\n", res);
    }
    else
        uart2net.run_uart2net();

    //EXFunctions *exfuns = new EXFunctions;
   // exfuns->connect_main(1);
    //exfuns->start();

    //exfuns.connect_main(1);

    //cout << "继续" << endl;

    //QEventLoop loop;
    /*
    SerialPort sp;
    int res = sp.run("COM5", 9600);

    if(res == 1)
        std::cout << "success" << std::endl;
    else {
        std::cout << "failed" << std::endl;
    }

    QByteArray ba;
    ba.resize(1);
    ba[0] = 0x01;
    for(int i = 0;i < 10; i++)
    {
        ba[0] = i;
        sp.send(ba);
        //loop.processEvents();
        Sleep(100);
    }
    system("pause");
    sp.close();
    //system("pause");
    //sp.close();

    //UART2NET uart2net;
*/


    /*
    TcpServer tcpserver;
    int err = tcpserver.run(8888);
    if(err == 0)
        std::cout << "open failed" << std::endl;
    else
        std::cout << "open success" << std::endl;
    */

    //TcpClinet tcpclient;
    //int err = tcpclient.run("10.17.37.19", 8888);
    //std::cout << err << std::endl;
    //if(err > 0)
    //    std::cout << "open success" << std::endl;

    //Sleep(5000);
    //tcpclient.close();

    //writeUART2NETConfig("D:\\", "test.xml",
    //                    true,
    //                    "COM1", 9600, "10.17.37.19", 8888);

    //int isServer, btl, port;
    //QString portNum, hostip;
    //readUART2NETConfig("D:\\", "test.xml", isServer, portNum, btl, hostip, port);


    //UART2NET uart2net;
    //uart2net.run_server("COM4", 9600, 8888);
    //uart2net.run_client("COM4", 9600, "10.17.37.19", 8888);
    //Sleep(5000);
    //uart2net.close();
    //QObject::connect(&a, SIGNAL(aboutToQuit()), &uart2net, SLOT(uart2net_safe_quit()));

    //QDateTime current_time = QDateTime::currentDateTime();
    //QString strCUrrentTime = current_time.toString("[yyyy-MM-dd-hh-mm-ss]:");
    //printf("%s\n", current_time.toString("[yyyy-MM-dd-hh-mm-ss]:").toStdString().c_str());
    //printf("%s\n", current_time.toString("[yyyy-MM-dd hh:mm:ss.zzz]:").toStdString().c_str());

    //UART2NET uart2net;
    //uart2net.create_log();

    return a.exec();
}
