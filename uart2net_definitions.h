#ifndef UART2NET_DEFINITIONS_H
#define UART2NET_DEFINITIONS_H



#define UART2NET_SERVER 1
#define UART2NET_CLIENT 2


#define UART2NET_SUCCESS 1
#define UART2NET_UNABLE_OPEN_CONFIG -1
#define UART2NET_ERROR_CONFIG_FILE -2
#define UART2NET_NONE_ELEMENT  -3

//#define DEBUG_SERIAL_PORT_RECEIVE // 输出，从串口接收信息
//#define DEBUG_SERIAL_PORT_SEND    // 输出, 向串口发送消息

#define DEBUG_TCPNET_NEW_CONNECTION // 输出，有新链接则输出IP地址和总连接个数

//#define DEBUG_TCP_CLIENT_RECEIVE // 输出客户端接收信息






#include <QtCore>
#include <QtXml>
#include <QDateTime>

QString ByteArrayToHexString(QByteArray data);


#endif // UART2NET_DEFINITIONS_H
