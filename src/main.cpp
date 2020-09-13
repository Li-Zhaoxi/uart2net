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
/*
    unsigned char err_message;
    UART2NET uart2net;
    err_message = uart2net.load_config("uart2net.ini");

    if(err_message != MESSAGE_SUCCESS)
        ShowMessageState(err_message);
    else
    {
        uart2net.show_config();
        err_message = uart2net.run_uart2net();
        ShowMessageState(err_message);
    }*/



    ParmsUART2NET parms;
    parms.write_config();
    parms.read_config("uart2net.ini");
    parms.show_config();



    return a.exec();
}
