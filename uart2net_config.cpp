#include "uart2net.h"

#include <fstream>

using namespace std;
#include <QSettings>

void UART2NET::write_uart2net_iniconfig()
{

    QSettings *configiniwrite = new QSettings("uart2net.ini", QSettings::IniFormat);

    uart2netconfig.btl = 9600;
    uart2netconfig.isServer = 2;
    uart2netconfig.comnum = "COM5";
    uart2netconfig.hostip = "127.0.0.1";
    uart2netconfig.tcpport = 8888;
    uart2netconfig.heartbeattime = 2000;
    uart2netconfig.needLog = 0;
    uart2netconfig.needShowConsole = 0;

    configiniwrite->setValue("uart2net/type", uart2netconfig.isServer);
    configiniwrite->setValue("uart2net/heartbeattime", uart2netconfig.heartbeattime);
    configiniwrite->setValue("uart2net/RecordLog", uart2netconfig.needLog);
    configiniwrite->setValue("uart2net/showmessage", uart2netconfig.needShowConsole);
    configiniwrite->setValue("serial-port/number", uart2netconfig.comnum);
    configiniwrite->setValue("serial-port/btl", uart2netconfig.btl);
    configiniwrite->setValue("TCP/hostip", uart2netconfig.hostip);
    configiniwrite->setValue("TCP/port", uart2netconfig.tcpport);
    configiniwrite->sync();

    delete configiniwrite;



}

int UART2NET::read_uart2net_iniconfig()
{
    QFileInfo fi("uart2net.ini");
    if(!fi.exists())
        return UART2NET_UNABLE_OPEN_CONFIG;

    QSettings *configiniRead = new QSettings("uart2net.ini", QSettings::IniFormat);


    if(configiniRead->contains("uart2net/type"))
        uart2netconfig.isServer = configiniRead->value("uart2net/type").toInt();
    else
        return UART2NET_NONE_ELEMENT;

    if(configiniRead->contains("uart2net/heartbeattime"))
        uart2netconfig.heartbeattime = configiniRead->value("uart2net/heartbeattime").toUInt();
    else
        return UART2NET_NONE_ELEMENT;

    if(configiniRead->contains("uart2net/RecordLog"))
        uart2netconfig.needLog = configiniRead->value("uart2net/RecordLog").toUInt();
    else
        return UART2NET_NONE_ELEMENT;

    if(configiniRead->contains("uart2net/showmessage"))
        uart2netconfig.needShowConsole = configiniRead->value("uart2net/showmessage").toUInt();
    else
        return UART2NET_NONE_ELEMENT;

    if(configiniRead->contains("serial-port/number"))
        uart2netconfig.comnum = configiniRead->value("serial-port/number").toString();
    else
        return UART2NET_NONE_ELEMENT;

    if(configiniRead->contains("serial-port/btl"))
        uart2netconfig.btl = configiniRead->value("serial-port/btl").toUInt();
    else
        return UART2NET_NONE_ELEMENT;

    if(configiniRead->contains("TCP/hostip"))
        uart2netconfig.hostip = configiniRead->value("TCP/hostip").toString();
    else
        return UART2NET_NONE_ELEMENT;

    if(configiniRead->contains("TCP/port"))
        uart2netconfig.tcpport = configiniRead->value("TCP/port").toUInt();
    else
        return UART2NET_NONE_ELEMENT;


    show_uart2net_iniconfig();

    delete configiniRead;
    return UART2NET_SUCCESS;

}



void UART2NET::show_uart2net_iniconfig()
{
    printf("--> General Config\n");
    printf("   TYPE: %d. ( 1=Server 2=Client)\n", uart2netconfig.isServer);
    printf("   HeartBeat: %d ms.\n", uart2netconfig.heartbeattime);
    printf("   RecordLog: %d. (1=Yes 0=No)\n", uart2netconfig.needLog);
    printf("   ShowHexData: %d. (1=Yes 0=No)\n", uart2netconfig.needShowConsole);
    printf("--> Serial Port Config\n");
    printf("   Port Number: %s.\n", uart2netconfig.comnum.toStdString().c_str());
    printf("   Baud Rate: %d.\n", uart2netconfig.btl);
    printf("--> TCP Config\n");
    if(uart2netconfig.isServer == UART2NET_CLIENT)
        printf("   Host IP: %s\n", uart2netconfig.hostip.toStdString().c_str());
    printf("   Port: %d.\n", uart2netconfig.tcpport);

}
