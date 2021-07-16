#ifndef TCPSERVER_H
#define TCPSERVER_H


#include <QtNetwork>
#include <QTcpServer>

#include <iostream>
#include "tcpsocket.h"

#include "uart2net_definitions.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer();

    int run(quint16 port);

    void send(QByteArray senddata, int idx);
protected:
    void incomingConnection(qintptr socketDescriptor); // 有链接的处理

private:
    QList<QTcpSocket*> tcpSocketConnetList;



protected slots:
    void Scoket_Data_Processing(QByteArray SendData,qintptr descriptor); //处理数据
    void Socket_Disconnected(qintptr descriptor); //断开连接处理


signals:
    void signals_socket_receive(QByteArray, int);
};

#endif // TCPSERVER_H
