#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include "uart2net_definitions.h"
#include "message_log.h"

class SerialPort : public QSerialPort
{
    Q_OBJECT
public:
    SerialPort();
    ~SerialPort();
    int run(QString comnum, qint32 btl);
    int run(QString comnum, qint32 btl, int loop_interval);
    void send(QByteArray portdata);
    void close();
private:
    QSerialPort *serialport;
    QByteArray rcvdata;
    int hasbeenclosed;
    int loop_interval;
public slots:
    void begin_to_receive(); //槽函数：接收串口消息

signals:
    void signals_serial_receive(QByteArray);
};

#endif // SERIALPORT_H
