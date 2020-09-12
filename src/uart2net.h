#ifndef UART2NET_H
#define UART2NET_H


#include <QSerialPort>
#include <QtNetwork>
#include <QTcpServer>
#include <QDateTime>
#include <iostream>
#include <QSettings>
#include <QFileInfo>


#include "tcpclinet.h"
#include "tcpserver.h"
#include "serialport.h"

#include "uart2net_definitions.h"

#define VAR_NAME(name) #name

enum UART2NET_MESSAGE
{
    MESSAGE_SUCCESS,
    INI_NOT_EXIST,
    LOST_ELEMENTS,
    UART_OPEN_FAILED,
    SERVER_CREATE_FAILED,
    CLIENT_CREATE_FAILED
};

class ParmsUART2NET
{
public:
    ParmsUART2NET();
    int isServer;
    int monitor_interval; // 监听时间间隔
    // 串口配置参数
    QString comnum; // 串口号
    unsigned int btl;     // 波特率

    // 服务器端配置参数
    QString hostip; // 服务器IP地址
    unsigned short tcpport; // 服务器端口号
    unsigned short heartbeattime; // 服务器发送心跳包间隔，ms
    unsigned char needLog; // 是否需要记录日志文件
    unsigned char needShowConsole;



    unsigned char write_config(QString save_path = "uart2net.ini");
    unsigned char read_config(QString load_path);
    void show_config();
};


class UART2NET: public QObject
{
    Q_OBJECT

public:
    UART2NET();
    ~UART2NET();

    // 总程序
    void run_uart2net();
    // 建立串口wifi服务器端
    unsigned char run_server(QString comnum, qint32 btl, quint16 tcpport);
    // 建立串口wifi客户端
    unsigned char run_client(QString comnum, qint32 btl, QString hostip, quint16 tcpport);
    // 关闭串口wifi服务端或客户端
    void close();

private:
    ParmsUART2NET parms;

private:
    TcpServer *tcp_server;
    TcpClient *tcp_client;
    SerialPort *serialport;

public: // 数据存储部分
    int create_log();
    void write_log(QByteArray binaryData, QString sourcetype);
    void close_log();
private:
    QFile log_data;
    QTextStream *log_out;

    QTimer heartbeattimer;
    QDateTime lasttime; // 用于客户端检测接受到tcp消息时间
    int T_disconnect;
    //UART2NETCONFIG _config;
public slots:
    void transport_serial_to_tcp(QByteArray serialdata);
    void transport_tcp_to_serial(QByteArray tcpdata);
    void uart2net_safe_quit();

    void send_heartbeats();
    void judge_alive();
    void reconnect();

    void slots_about_toquit();

signals:
    void signals_reconnect_host();

};

#endif // UART2NET_H
