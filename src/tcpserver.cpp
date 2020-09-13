#include "tcpserver.h"

TcpServer::TcpServer()
{
    tcpSocketConnetList.clear();
}


int TcpServer::run(quint16 port)
{
    if(this->listen(QHostAddress::Any, port))
        return 1;
    else
        return 0;
}




void TcpServer::incomingConnection(qintptr socketDescriptor)
{
     TcpSocket *tcpsocket = new TcpSocket();
     tcpsocket->setSocketDescriptor(socketDescriptor);
     tcpsocket->run();
     connect(tcpsocket,SIGNAL(GetDataFromClient(QByteArray ,qintptr)),this,SLOT(Scoket_Data_Processing(QByteArray,qintptr)));
     connect(tcpsocket,SIGNAL(ClientDisConnected(qintptr)),this,SLOT(Socket_Disconnected(qintptr)));
     tcpSocketConnetList.append(tcpsocket);
     if(tcpSocketConnetList.size() > 1) //�¿ͻ������Ӻ󣬶Ͽ�֮ǰ���оɵ�
     {
         for(int i = 0; i < tcpSocketConnetList.size() - 1; i++)
         {
             QTcpSocket *item = tcpSocketConnetList.at(i);
             item->close();
             // �ر�֮���Զ�����disconnected�ź�
             //tcpSocketConnetList.removeAt(i);//����пͻ��˶Ͽ����ӣ� �ͽ��б��е��׽���ɾ��
             //item->deleteLater();
         }
     }
#ifdef DEBUG_TCPNET_NEW_CONNECTION
     printf("New connection. IP: %s, total %d.\n",
            tcpsocket->peerAddress().toString().toStdString().c_str(),
            tcpSocketConnetList.count());
#endif
     if(msglog)
     {
         char tmp[1024];
         sprintf(tmp, "New connection. IP: %s, total %d.\n",
                 tcpsocket->peerAddress().toString().toStdString().c_str(),
                 tcpSocketConnetList.count());
         msglog->write(QString(tmp), "SERVERNEW");
     }

}


void TcpServer::Scoket_Data_Processing(QByteArray SendData,qintptr descriptor)
{
    for(int i = 0; i < tcpSocketConnetList.count(); i++)
    {
        QTcpSocket *item = tcpSocketConnetList.at(i);
        if(item->socketDescriptor() == descriptor)        //ͨ��descriptor��QList�в��Ҷ�Ӧ��QTcpSocket����
        {
            qDebug() << item->peerAddress().toString() <<":"<<item->peerPort() <<
                        "  " << QString::fromLocal8Bit(SendData);
            emit signals_socket_receive(SendData, i);
        }
    }
}

void TcpServer::Socket_Disconnected(qintptr descriptor)
{
    for(int i = 0; i < tcpSocketConnetList.count(); i++)
    {
        QTcpSocket *item = tcpSocketConnetList.at(i);
        qintptr temp = item->socketDescriptor();
        if(-1 == temp||temp == descriptor)            //�����з��֣���disconnected()�źŷ�����item->socketDescriptor()����ֵ�Ѿ�Ϊ-1�ˣ�����ͨ��item->socketDescriptor() == descriptor�������ж��ˡ���������ɾ������ֵΪ-1��QTcpSocket����
        {
            tcpSocketConnetList.removeAt(i);//����пͻ��˶Ͽ����ӣ� �ͽ��б��е��׽���ɾ��
            item->deleteLater();
            qDebug()<< "[TcpSocket]---------------------------------Disconnect:" << descriptor << endl;
            return;
        }
    }
    return;
}


void TcpServer::send(QByteArray senddata, int idx)
{
    if(idx < tcpSocketConnetList.size())
    {
        tcpSocketConnetList[idx]->write(senddata);
    }

}
