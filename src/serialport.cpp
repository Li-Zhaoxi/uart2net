#include "serialport.h"

#if defined(LINUX) || defined(UNIX)
#include <unisted>
#elif defined(WINDOWS)
#include <Windows.h>
#endif

SerialPort::SerialPort()
{
    serialport = new QSerialPort;
    hasbeenclosed = 1;
}

SerialPort::~SerialPort()
{
    if(hasbeenclosed == 0)
        close();
    delete[] serialport;
}

int SerialPort::run(QString comnum, qint32 btl)
{
    serialport->setPortName(comnum);
    serialport->setBaudRate(btl);
    serialport->setDataBits(QSerialPort::Data8); //数据位
    serialport->setParity(QSerialPort::NoParity);//无奇偶校验
    serialport->setStopBits(QSerialPort::OneStop);//停止位1
    serialport->setFlowControl(QSerialPort::NoFlowControl);//无控制
    hasbeenclosed = 0;
    if(!serialport->open(QIODevice::ReadWrite))
        return -1;
    else
    {
        connect(serialport, &QSerialPort::readyRead,
                this, &SerialPort::begin_to_receive);
        //connect(serialport, SIGNAL(readyRead()), this, SLOT(begin_to_receive()));
        return 1;
    }
}

void SerialPort::begin_to_receive()
{
    rcvdata = serialport->readAll();

    emit signals_serial_receive(rcvdata);

#if defined(LINUX) || defined(UNIX)
    usleep(5000);
#elif defined(WINDOWS)
    Sleep(5);
#endif

#ifdef DEBUG_SERIAL_PORT_RECEIVE
    QString hexstr = ByteArrayToHexString(rcvdata);
    printf("SerialPort receive: %s\n", hexstr.toStdString().c_str());
#endif


}


void SerialPort::send(QByteArray portdata)
{
    if(serialport != nullptr)
    {
        qint64 res = serialport->write(portdata);
        //serialport->flush();
        //printf("Send length: %d\n", res);
#ifdef DEBUG_SERIAL_PORT_SEND
        //printf("Serial send: %s\n", ByteArrayToHexString(portdata).toStdString().c_str());
#endif
    }
}


void SerialPort::close()
{
    if(serialport != nullptr)
    {
        hasbeenclosed = 1;
        serialport->clear();
        serialport->close();
    }
}
