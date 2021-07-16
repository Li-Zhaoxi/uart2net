#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include "uart2net_definitions.h"

class SerialPort : public QSerialPort
{
    Q_OBJECT
public:
    SerialPort();
    ~SerialPort();
    int run(QString comnum, qint32 btl);
    void send(QByteArray portdata);
    void close();
private:
    QSerialPort *serialport;
    QByteArray rcvdata;
    int hasbeenclosed;
public slots:
    void begin_to_receive(); //槽函数：接收串口消息

signals:
    void signals_serial_receive(QByteArray);
};

#endif // SERIALPORT_H
