#include <iostream>
#include "../inc/HR_Pro.h"
#include <vector>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#define err(Msg)   printf("%s调用失败！错误码为：%d,报错行数：%d\n",Msg,nRet,__LINE__)
using namespace std;
class Dazhu
{
public:
    Dazhu();
    ~Dazhu();
    void sayHello();
private:
    string Msg;//消息
    int nRet;//返回值
    const char* IP="192.168.0.10";//机器人的IP地址
    unsigned short nPort = 10003;//机器人的端口号
    void HR_connect(const char* IP,unsigned short nPort);//连接机器人服务器
    void init();
    void move(float arr[],int size);
};