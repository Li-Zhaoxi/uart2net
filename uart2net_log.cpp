#include "uart2net.h"


int UART2NET::create_log()
{
    QDateTime current_time = QDateTime::currentDateTime();
    QString filename = current_time.toString("yyyy-MM-dd-hh-mm-ss") + ".txt";

    QDir dir;
    if(!dir.exists("log"))
    {
        bool res = dir.mkpath("log");
        if(res == false)
           return -1;
    }


    //log_data.open("log\\" + filename, QFile::WriteOnly | QIODevice::Truncate);
    log_data.setFileName("log\\" + filename);
    if(!log_data.open(QFile::WriteOnly | QIODevice::Truncate))
        return -2;

    log_out = new QTextStream(&log_data);

//    *log_out << current_time.toString("[yyyy-MM-dd hh:mm:ss.zzz]: 12345");

//    log_data.close();


    return 1;
}

void UART2NET::close_log()
{
    delete[] log_out;
    log_data.close();
}

void UART2NET::write_log(QByteArray binaryData, QString sourcetype)
{
    QDateTime current_time = QDateTime::currentDateTime();
    QString outstr = current_time.toString("[yyyy-MM-dd hh:mm:ss.zzz]: ") +
            sourcetype + " " +
            ByteArrayToHexString(binaryData);
    *log_out<<binaryData;
}
