#include "uart2net.h"


ParmsUART2NET::ParmsUART2NET()
{
    isServer = 0;
    monitor_interval = 5;
    needLog = 0;
    logpath = "log.txt";
    comnum = "COM3";
    btl = 9600;
    hostip = "172.0.0.0";
    tcpport = 8888;
    heartbeattime = 1000;
}

unsigned char ParmsUART2NET::write_config(QString save_path)
{
    QSettings *configiniWrite = new QSettings(save_path, QSettings::IniFormat);
    if (configiniWrite == nullptr)
        return INI_NOT_EXIST;

    configiniWrite->setValue(QString(VAR_NAME(isServer)), isServer);
    configiniWrite->setValue(QString(VAR_NAME(monitor_interval)), monitor_interval);
    configiniWrite->setValue(QString(VAR_NAME(needLog)), needLog);
    configiniWrite->setValue(QString(VAR_NAME(logpath)), logpath);


    configiniWrite->setValue(QString("uart/") + QString(VAR_NAME(comnum)), comnum);
    configiniWrite->setValue(QString("uart/") + QString(VAR_NAME(btl)), btl);

    configiniWrite->setValue(QString("net/") + QString(VAR_NAME(hostip)), hostip);
    configiniWrite->setValue(QString("net/") + QString(VAR_NAME(tcpport)), tcpport);
    configiniWrite->setValue(QString("net/") + QString(VAR_NAME(heartbeattime)), heartbeattime);

    configiniWrite->sync();


    delete configiniWrite;

    return MESSAGE_SUCCESS;

}


unsigned char ParmsUART2NET::read_config(QString load_path)
{
    QFileInfo fi(load_path);
    if(!fi.exists())
    {
        return INI_NOT_EXIST;
    }

    QSettings *configiniRead = new QSettings(load_path, QSettings::IniFormat);
    QByteArray str;

    if(configiniRead->contains(QString(VAR_NAME(isServer))))
        isServer = configiniRead->value(QString(VAR_NAME(isServer))).toInt();
    else
        return LOST_ELEMENTS;

    if(configiniRead->contains(QString(VAR_NAME(monitor_interval))))
        monitor_interval = configiniRead->value(QString(VAR_NAME(monitor_interval))).toInt();
    else
        return LOST_ELEMENTS;

    if(configiniRead->contains(QString(VAR_NAME(needLog))))
        needLog = configiniRead->value(QString(VAR_NAME(needLog))).toInt();
    else
        return LOST_ELEMENTS;

    if(configiniRead->contains(QString(VAR_NAME(logpath))))
        logpath = configiniRead->value(QString(VAR_NAME(logpath))).toString();
    else
        return LOST_ELEMENTS;

    if(configiniRead->contains(QString("uart/") + QString(VAR_NAME(comnum))))
        comnum = configiniRead->value(QString("uart/") + QString(VAR_NAME(comnum))).toString();
    else
        return LOST_ELEMENTS;

    if(configiniRead->contains(QString("uart/") + QString(VAR_NAME(btl))))
        btl = configiniRead->value(QString("uart/") + QString(VAR_NAME(btl))).toInt();
    else
        return LOST_ELEMENTS;

    if(configiniRead->contains(QString("net/") + QString(VAR_NAME(hostip))))
        hostip = configiniRead->value(QString("net/") + QString(VAR_NAME(hostip))).toString();
    else
        return LOST_ELEMENTS;

    if(configiniRead->contains(QString("net/") + QString(VAR_NAME(tcpport))))
        tcpport = configiniRead->value(QString("net/") + QString(VAR_NAME(tcpport))).toInt();
    else
        return LOST_ELEMENTS;

    if(configiniRead->contains(QString("net/") + QString(VAR_NAME(heartbeattime))))
        heartbeattime = configiniRead->value(QString("net/") + QString(VAR_NAME(heartbeattime))).toInt();
    else
        return LOST_ELEMENTS;

    if(needLog)
    {
        msglog = new message_log();
        if(msglog->create(logpath) != MESSAGE_SUCCESS)
            return LOG_CREATE_FAILED;
    }

    return MESSAGE_SUCCESS;
}


void ParmsUART2NET::show_config()
{
    std::cout << "GENERAL:" << std::endl;
    std::cout << "    " << VAR_NAME(isServer) << ": " << isServer << std::endl;
    std::cout << "    " << VAR_NAME(monitor_interval) << ": " << monitor_interval << std::endl;
    std::cout << "    " << VAR_NAME(needLog) << ": " << needLog << std::endl;
    std::cout << "    " << VAR_NAME(logpath) << ": " << logpath.toStdString() << std::endl;
    std::cout << "UART:" << std::endl;
    std::cout << "    " << VAR_NAME(comnum) << ": " << comnum.toStdString() << std::endl;
    std::cout << "    " << VAR_NAME(btl) << ": " << btl << std::endl;
    std::cout << "NET:" << std::endl;
    std::cout << "    " << VAR_NAME(hostip) << ": " << hostip.toStdString() << std::endl;
    std::cout << "    " << VAR_NAME(tcpport) << ": " << tcpport << std::endl;
    std::cout << "    " << VAR_NAME(heartbeattime) << ": " << heartbeattime << std::endl;
}
