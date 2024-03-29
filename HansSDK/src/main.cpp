#include "../inc/Dazhu.h"

int main()
{
    Dazhu dazhu;
    //dazhu.Move_demo();//机器人demo演示
    vector<float> arr = {200.0, 50.0, 700.0, 0.0, 0.0, 5.0};//指定位置
    vector<float> arr2 = {200.0, 150.0, 700.0, 0.0, 0.0, 5.0};//指定位置
    //dazhu.ReadCurFSM();//读取当前状态机
    dazhu.Move(arr2);//机器人移动到指定位置
    dazhu.Disable();//机器人使能    
    return 0;
} 