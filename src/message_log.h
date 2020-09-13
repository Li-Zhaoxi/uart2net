#ifndef MESSAGE_LOG_H
#define MESSAGE_LOG_H

#include <QByteArray>
#include <QString>
#include <QFile>
#include "uart2net_definitions.h"

class message_log
{
public:
    message_log();
    ~message_log();
    unsigned char create(QString save_path);
    void write(QByteArray data, QString dtype);
    void write(QString str, QString dtype);

private:
    QFile *file;
};

extern message_log *msglog;

#endif // MESSAGE_LOG_H
