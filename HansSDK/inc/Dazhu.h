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

/**
 * @brief The Dazhu class represents a class for controlling a robot named Dazhu.
 */
class Dazhu {  
public:
    /**
     * @brief Constructs a Dazhu object.
     */
    Dazhu();//构造函数

    /**
     * @brief Destroys the Dazhu object.
     */
    ~Dazhu();//析构函数
    
    /**
     * @brief Moves the robot in a demo mode.
     */
    void Move_demo();

    /**
     * @brief Moves the robot to the specified position.
     * @param arr The position to move to.
     * @return flag The flag to indicate whether to move to the specified position.
     */
    bool Move(vector<float> arr);//移动到指定位置，只能传入6个元素的数组

    /**
     * @brief Enables the robot.
     */
    void Enable();//机器人使能

    /**
     * @brief Disable the robot.
     */
    void Disable();//机器人失能

    /**
     * @brief Read current state machine.
     * @param nCurFSM The current state machine.
     * @param strCurFSM The current state machine field.
     * @return flag The flag to indicate whether to read the current state machine.
     */
    int ReadCurFSM();//读取当前状态机

private:
    string Msg;//消息
    int nRet;//返回值
    const char* IP;//机器人的IP地址
    unsigned short nPort ;//机器人的端口号
    int nCurFSM = 0;//当前状态机
    string strCurFSM = "";//当前状态机字段
    vector<float> arr = {         //路径点_demo
        200.0, 50.0, 700.0, 0.0, 0.0, 5.0,
        200.0, 100.0, 700.0, 0.0, 0.0, 5.0,
        200.0, 150.0, 700.0, 0.0, 0.0, 5.0,
        200.0, 200.0, 700.0, 0.0, 0.0, 5.0,
        200.0, 150.0, 700.0, 0.0, 0.0, 5.0,
        200.0, 100.0, 700.0, 0.0, 0.0, 5.0
    };
    
    /**
     * @brief Initializes the Dazhu object.
     */
    void init();//初始化
    
    /**
     * @brief Connects to the robot server using the specified IP address and port number.
     * @param IP The IP address of the robot.
     * @param nPort The port number of the robot.
     */
    void HR_connect(const char* IP,unsigned short nPort);//连接机器人服务器

    /**
     * @brief Gets the position of the robot.
     * @param boxID The ID of the box.
     * @param rbtID The ID of the robot.
     * @return pos The position of the robot.
     */
    int getInPos(unsigned int boxID, unsigned int rbtID);//获取机器人是否到位
};