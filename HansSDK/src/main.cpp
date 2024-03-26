#include "../inc/Dazhu.h"

int main()
{
    Dazhu dazhu;
    //dazhu.Move_demo();//机器人demo演示
    vector<float> arr = {200.0, 50.0, 700.0, 0.0, 0.0, 5.0};//指定位置
    dazhu.Move(arr);//机器人移动到指定位置
    return 0;
} 