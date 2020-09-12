#ifndef UART2NET_DEFINITIONS_H
#define UART2NET_DEFINITIONS_H


enum UART2NET_TYPE
{
    UART2NET_SERVER = 1,
    UART2NET_CLIENT = 2
};


#define UART2NET_SUCCESS 1
#define UART2NET_UNABLE_OPEN_CONFIG -1
#define UART2NET_ERROR_CONFIG_FILE -2
#define UART2NET_NONE_ELEMENT  -3

//#define DEBUG_SERIAL_PORT_RECEIVE // ������Ӵ��ڽ�����Ϣ
//#define DEBUG_SERIAL_PORT_SEND    // ���, �򴮿ڷ�����Ϣ

#define DEBUG_TCPNET_NEW_CONNECTION // ������������������IP��ַ�������Ӹ���

//#define DEBUG_TCP_CLIENT_RECEIVE // ����ͻ��˽�����Ϣ






#include <QtCore>
#include <QtXml>
#include <QDateTime>

QString ByteArrayToHexString(QByteArray data);


#endif // UART2NET_DEFINITIONS_H