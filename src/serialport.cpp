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
    loop_interval = 5;
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
    serialport->setDataBits(QSerialPort::Data8); //����λ
    serialport->setParity(QSerialPort::NoParity);//����żУ��
    serialport->setStopBits(QSerialPort::OneStop);//ֹͣλ1
    serialport->setFlowControl(QSerialPort::NoFlowControl);//�޿���
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

int SerialPort::run(QString comnum, qint32 btl, int loop_interval)
{
    this->loop_interval = loop_interval;
    return this->run(comnum, btl);
}

void SerialPort::begin_to_receive()
{
    rcvdata = serialport->readAll();

    emit signals_serial_receive(rcvdata);

    if(msglog)
        msglog->write(rcvdata, "RCVUART");
#if defined(LINUX) || defined(UNIX)
    usleep(loop_interval * 1000);
#elif defined(WINDOWS)
    Sleep(loop_interval);
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

        if(msglog)
            msglog->write(portdata, "SDUART");
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
