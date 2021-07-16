#include "tcpsocket.h"


TcpSocket::TcpSocket()
{

}

void TcpSocket::run()
{
    Descriptor = this->socketDescriptor();
    connect(this,SIGNAL(readyRead()),this,SLOT(ReceiveData_slot()));
    connect(this,SIGNAL(disconnected()),this,SLOT(ClientDisconnected_slot()));
}

//TcpSocket数据接收触发
void TcpSocket::ReceiveData_slot()
{
    QByteArray buffer;
    buffer = readAll();
    if(!buffer.isEmpty())
    {
        emit GetDataFromClient(buffer, Descriptor);
    }
}

//TcpSocket断开链接触发
void TcpSocket::ClientDisconnected_slot()
{
    emit ClientDisConnected(Descriptor);
}
