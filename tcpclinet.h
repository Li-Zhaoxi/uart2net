#ifndef TCPCLINET_H
#define TCPCLINET_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QSerialPort>

#include <iostream>

#include "uart2net_definitions.h"

class TcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    TcpClient();
    ~TcpClient();
    int run(QString ipserver, quint16 port);
    int reconnect();
    void close();
    void send(QByteArray tcpdata);
private:
    QHostAddress *hostip;
    quint16 _port;
    QTcpSocket *clientsocket;


    int isConnected;

protected slots:
    void receivedata();//处理readyRead信号读取数据
    //客户端断开连接触发disconnected信号，这个槽函数用来处理这个信号
    void slotdisconnected(); //用来处理离开聊天室的信号
    void slotconnectedsuccess();//用来处理连接成功的信号

signals:
    void signals_socket_receive(QByteArray);
};

#endif // TCPCLINET_H
