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
    void ReceiveData_slot();            //����readyRead�źŶ�ȡ����
    void ClientDisconnected_slot();     //�ͻ��˶Ͽ����Ӵ���disconnected�źţ�����ۺ���������������ź�

signals:
    void GetDataFromClient(QByteArray ,qintptr);   //����server�����ݴ���
    void ClientDisConnected(qintptr);           //����server�пͻ��˶Ͽ�����

};

#endif // TCPSOCKET_H
