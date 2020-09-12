#ifndef TCPSOCKET_H
#define TCPSOCKET_H


#include <QtNetwork>
#include <QTcpSocket>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpSocket();
    void run();

private:
    qintptr Descriptor;

protected slots:
    void ReceiveData_slot();            //处理readyRead信号读取数据
    void ClientDisconnected_slot();     //客户端断开连接触发disconnected信号，这个槽函数用来处理这个信号

signals:
    void GetDataFromClient(QByteArray ,qintptr);   //告诉server有数据处理
    void ClientDisConnected(qintptr);           //告诉server有客户端断开连接

};

#endif // TCPSOCKET_H
