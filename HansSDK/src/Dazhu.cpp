#include "Dazhu.h"

Dazhu::Dazhu()
{
    std::cout << "Dazhu constructor" << std::endl;
    unsigned short nPort = 10003;
    // 连接机器人服务器
    int nret = HRIF_Connect(0,"192.168.0.10",10003);//连接机器人服务器,这里需要填写机器人的IP地址
    if (nret != 0)
    {
        err("HRIF_Connect");
        cout << "HRIF_Connect调用flase!" << endl;

    }
    else
    {
       cout << "HRIF_Connect调用成功!" << endl;
    }
}

Dazhu::~Dazhu()
{
    std::cout << "Dazhu destructor" << std::endl;
}

void Dazhu::HR_connect(const char* IP,unsigned short nPort)
{
    // 连接机器人服务器
    int nret = HRIF_Connect(0,IP,nPort);//连接机器人服务器,这里需要填写机器人的IP地址
    if (nret != 0)
    {
        err("HRIF_Connect");
        cout << "HRIF_Connect调用flase!" << endl;

    }
    else
    {
       cout << "HRIF_Connect调用成功!" << endl;
    }
}

