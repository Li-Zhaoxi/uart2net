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
     if(tcpSocketConnetList.size() > 1) //新客户端连接后，断开之前所有旧的
     {
         for(int i = 0; i < tcpSocketConnetList.size() - 1; i++)
         {
             QTcpSocket *item = tcpSocketConnetList.at(i);
             item->close();
             // 关闭之后自动触发disconnected信号
             //tcpSocketConnetList.removeAt(i);//如果有客户端断开连接， 就将列表中的套接字删除
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
        if(item->socketDescriptor() == descriptor)        //通过descriptor在QList中查找对应的QTcpSocket对象
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
        if(-1 == temp||temp == descriptor)            //测试中发现，当disconnected()信号发出，item->socketDescriptor()返回值已经为-1了，不能通过item->socketDescriptor() == descriptor来进行判断了。。。所以删除返回值为-1的QTcpSocket对象
        {
            tcpSocketConnetList.removeAt(i);//如果有客户端断开连接， 就将列表中的套接字删除
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
