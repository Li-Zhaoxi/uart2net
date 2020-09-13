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
#include "message_log.h"




class ParmsUART2NET
{
public:
    ParmsUART2NET();
    int isServer;
    int monitor_interval; // ����ʱ����
    int needLog;
    QString logpath;
    // �������ò���
    QString comnum; // ���ں�
    unsigned int btl;     // ������

    // �����������ò���
    QString hostip; // ������IP��ַ
    unsigned short tcpport; // �������˿ں�
    unsigned short heartbeattime; // ���������������������ms



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
    unsigned char load_config(QString load_path);
    void show_config();
    // �ܳ���
    unsigned char run_uart2net();
    // ��������wifi��������
    unsigned char run_server(QString comnum, qint32 btl, quint16 tcpport);
    // ��������wifi�ͻ���
    unsigned char run_client(QString comnum, qint32 btl, QString hostip, quint16 tcpport);
    // �رմ���wifi����˻�ͻ���
    void close();

private:
    ParmsUART2NET parms;

private:
    TcpServer *tcp_server;
    TcpClient *tcp_client;
    SerialPort *serialport;

public: // ���ݴ洢����
    int create_log();
    void write_log(QByteArray binaryData, QString sourcetype);
    void close_log();
private:
    QFile log_data;
    QTextStream *log_out;

    QTimer heartbeattimer;
    QDateTime lasttime; // ���ڿͻ��˼����ܵ�tcp��Ϣʱ��
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
