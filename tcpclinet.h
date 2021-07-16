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
    void receivedata();//����readyRead�źŶ�ȡ����
    //�ͻ��˶Ͽ����Ӵ���disconnected�źţ�����ۺ���������������ź�
    void slotdisconnected(); //���������뿪�����ҵ��ź�
    void slotconnectedsuccess();//�����������ӳɹ����ź�

signals:
    void signals_socket_receive(QByteArray);
};

#endif // TCPCLINET_H
