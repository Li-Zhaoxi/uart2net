#include "tcpclinet.h"

TcpClient::TcpClient()
{
    hostip = new QHostAddress();
    clientsocket = new QTcpSocket();
    isConnected = false;
}

TcpClient::~TcpClient()
{
    close();

    delete[] hostip;
    delete[] clientsocket;
}

int TcpClient::run(QString ipserver, quint16 port)
{
    //close();

    if(!hostip->setAddress(ipserver))
        return -1;
    _port = port;

    clientsocket->connectToHost(*hostip, port);

    connect(clientsocket, SIGNAL(connected()), this, SLOT(slotconnectedsuccess()));
    int loop = 0;
    while(!clientsocket->waitForConnected(5000))
    {
        loop++;

        QMutex mutex;
        QWaitCondition sleep;
        mutex.lock();
        sleep.wait(&mutex, 1000);
        mutex.unlock();

        qDebug() << loop << "th reconnect to the server";
        clientsocket->connectToHost(*hostip, port);
    }

    if(!clientsocket->waitForConnected(5000))
        return -2;

    //接收到服务器的信息就会触发readyRead信号
    connect(clientsocket, SIGNAL(readyRead()), this, SLOT(receivedata()));
    // 断开服务器信号
    connect(clientsocket, SIGNAL(disconnected()), this, SLOT(slotdisconnected()));

    return 1;
}

int TcpClient::reconnect()
{
    clientsocket->disconnectFromHost();
    clientsocket->connectToHost(*hostip, _port);
    QDateTime time1 = QDateTime::currentDateTime(), time2;
    if(!clientsocket->waitForConnected(5000))
    {
        QMutex mutex;
        QWaitCondition sleep;
        time2 = QDateTime::currentDateTime();
        int dis = time1.msecsTo(QDateTime::currentDateTime());

        mutex.lock();
        sleep.wait(&mutex, dis + 1);
        mutex.unlock();

        return -2;
    }


    return 1;
}

void TcpClient::slotconnectedsuccess()
{
    isConnected = 1;
    QString str = "Client: " +
            clientsocket->localAddress().toString() +
            "." + QString::number(clientsocket->localPort()) +
            " connects to server ^_^.\n";
    clientsocket->write(str.toUtf8());
}
void TcpClient::slotdisconnected()
{
    isConnected = 0;
}
void TcpClient::receivedata()
{
    QByteArray array = clientsocket->readAll();
    emit signals_socket_receive(array);
#ifdef DEBUG_TCP_CLIENT_RECEIVE
    QString hexstr = ByteArrayToHexString(array);
    printf("Client receive: %s\n", hexstr.toStdString().c_str());
#endif
}



void TcpClient::close()
{
    if(hostip != nullptr)
    {
        hostip->clear();
    }
    if(clientsocket != nullptr)
    {
        clientsocket->disconnectFromHost();
        clientsocket->waitForDisconnected();
        clientsocket->close();
    }
    isConnected = false;
}

void TcpClient::send(QByteArray tcpdata)
{
    clientsocket->write(tcpdata);
}
