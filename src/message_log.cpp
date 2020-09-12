#include "message_log.h"


message_log::message_log()
{
    file = nullptr;
}

message_log::~message_log()
{
    if(file)
    {
        file->close();
        delete file;
        file = nullptr;
    }

}

void message_log::write(QByteArray data, QString dtype)
{
    QString hexstr = ByteArrayToHexString(data);
    auto time2 = QDateTime::currentDateTime();
    QString current_date =time2.toString("[yyyy-MM-dd-hh-mm-ss-zzz]: ");
    QString out_str = current_date+QString("C") + dtype + QString(")") + hexstr + "\n";
    file->write(out_str.toStdString().c_str());
}



unsigned char message_log::create(QString save_path)
{
    file = new QFile(save_path);
    if(file == nullptr)
        return LOG_CREATE_FAILED;
    file->open(QIODevice::WriteOnly | QIODevice::Text);

    return MESSAGE_SUCCESS;
}
