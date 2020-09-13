#include "uart2net_definitions.h"

QString ByteArrayToHexString(QByteArray data)
{
    QString ret(data.toHex().toUpper());
    int len = ret.length()/2;
    for(int i=1;i<len;i++)
    {
        ret.insert(2*i+i-1," ");
    }
    return ret;
}


void ShowMessageState(unsigned char id)
{
    switch (id) {
    case INI_NOT_EXIST:
        std::cout << "INI_NOT_EXIST." << std::endl;
        break;
    case LOST_ELEMENTS:
        std::cout << "LOST_ELEMENTS." << std::endl;
        break;
    case UART_OPEN_FAILED:
        std::cout << "UART_OPEN_FAILED." << std::endl;
        break;
    case SERVER_CREATE_FAILED:
        std::cout << "SERVER_CREATE_FAILED." << std::endl;
        break;
    case CLIENT_CREATE_FAILED:
        std::cout << "CLIENT_CREATE_FAILED." << std::endl;
        break;
    case LOG_CREATE_FAILED:
        std::cout << "LOG_CREATE_FAILED." << std::endl;
        break;
    default:
        break;

    }
}
