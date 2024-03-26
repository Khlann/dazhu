#include "Dazhu.h"

Dazhu::Dazhu()
{
    IP="192.168.0.10";//机器人的IP地址
    nPort = 10003;//机器人的端口号
    cout << "Dazhu constructor" << endl;
    HR_connect(IP,nPort);
    init();
}

Dazhu::~Dazhu()
{
    cout << "Dazhu destructor" << endl;
}

void Dazhu::init()
{
    // 定义状态机变量
    int nCurFSM = 0;
    // 定义状态机字段变量
    string strCurFSM = "";
    // 读取当前状态机
    while (true)
    {
        
        int nRet= HRIF_ReadCurFSM(0,0, nCurFSM, strCurFSM);
        cout << "now_state:" << nCurFSM << endl;
        if (int(nCurFSM)== 24)
        {
            //机器人使能
            int nRet= HRIF_GrpEnable(0,0);
        }
        else if (int(nCurFSM)== 22 or int(nCurFSM)==5)
        {
            // 机器人复位
            int nRet= HRIF_GrpReset(0,0);
        }
        else if (int(nCurFSM)== 14)
        {
            // 连接机器人
            int nRet= HRIF_Connect2Controller(0);
        }
        else if (int(nCurFSM)== 7)
        {
            // 机器人上电
            int nRet= HRIF_Electrify(0);
        }
        else if (int(nCurFSM)== 33)
        {
            break;
        }
    }
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

void Dazhu::Move_demo()
{
    int test=1;
    int size = arr.size();
    for (int i=0;i<size;i=i+6)
    {
        float dX = arr[i];float dY = arr[i+1];float dZ = arr[i+2];
        float dRx = arr[i+3];float dRy = arr[i+4];float dRz = arr[i+5];
        int nMoveType = 1;string sTcpName = "TCP";string sUcsName = "Base";
        int dVelocity = 1000;int dAcc = 2500;int dRadius = 10;int nIsUseJoint = 0;
        int nIsSeek = 0; int nIOBit = 0;int nIOState = 0;
        string character;
        character = i+'0';
        string strCmdID = character;
        
        // 定义关节命令位置
        double dJ1 = 0; double dJ2 = 0; double dJ3 = 0;
        double dJ4 = 0; double dJ5 = 0; double dJ6 = 0;
        // 读取关节命令位置
        int nRet = HRIF_ReadActJointPos(0,0, dJ1 , dJ2 , dJ3 , dJ4 , dJ5 , dJ6);
        // 执行路点运动
        int nRetaa = HRIF_WayPoint(0, 0,nMoveType , dX , dY , dZ , dRx , dRy , dRz , dJ1 , dJ2 , dJ3 , dJ4 , dJ5 , dJ6 
                                ,sTcpName , sUcsName, dVelocity, dAcc, dRadius,nIsUseJoint, nIsSeek, nIOBit, nIOState, strCmdID);
        sleep(2.5); 
        cout << "运动到第"<< test++ <<"个点" << endl;
    }
    cout << "11111"<<endl;
    sleep(2.5);
    cout << "22222"<<endl;

    // 定义状态机变量
    int nCurFSM1 = 0;
    // 定义状态机字段变量
    string strCurFSM1 = "";
    while (true)
    {
        int nRet= HRIF_ReadCurFSM(0,0, nCurFSM1, strCurFSM1);
       // cout << "now_FSM:" << nCurFSM1 <<endl;

        if (int(nCurFSM1) == 33)
        {
            break;
        }
    }
    int nRet= HRIF_GrpDisable(0,0);//机器人失能
    cout << "cobot_running_done"<<endl;
}

bool Dazhu::Move(vector<float> arr)
{
    int size = arr.size();
    //只能一次性传入6个数据
    if (size%6 != 0)
    {
        cout << "数据传入错误" << endl;
        return false;
    }
    for (int i=0;i<size;i=i+6)
    {
        float dX = arr[i];float dY = arr[i+1];float dZ = arr[i+2];
        float dRx = arr[i+3];float dRy = arr[i+4];float dRz = arr[i+5];
        int nMoveType = 1;string sTcpName = "TCP";string sUcsName = "Base";
        int dVelocity = 1000;int dAcc = 2500;int dRadius = 10;int nIsUseJoint = 0;
        int nIsSeek = 0; int nIOBit = 0;int nIOState = 0;
        string character;
        character = i+'0';
        string strCmdID = character;
        
        // 定义关节命令位置
        double dJ1 = 0; double dJ2 = 0; double dJ3 = 0;
        double dJ4 = 0; double dJ5 = 0; double dJ6 = 0;
        // 读取关节命令位置
        int nRet = HRIF_ReadActJointPos(0,0, dJ1 , dJ2 , dJ3 , dJ4 , dJ5 , dJ6);
        // 执行路点运动
        int nRetaa = HRIF_WayPoint(0, 0,nMoveType , dX , dY , dZ , dRx , dRy , dRz , dJ1 , dJ2 , dJ3 , dJ4 , dJ5 , dJ6 ,sTcpName , sUcsName, dVelocity, dAcc, dRadius,nIsUseJoint, nIsSeek, nIOBit, nIOState, strCmdID);
    }
    while (getInPos(0,0) != 1)
    {
        cout << "正在到达目标点" << endl;
        sleep(1);
    }
    int nRet= HRIF_GrpDisable(0,0);//机器人失能
    cout << "到达目标点" << endl;


}

int Dazhu::getInPos(unsigned int boxID, unsigned int rbtID) {
    int nMovingState, nEnableState, nErrorState, nErrorCode, nErrorAxis;
    int nBreaking, nPause, nEmergencyStop, nSaftyGuard, nElectrify, nIsConnectToBox;
    int nBlendingDone, nInpos;

    HRIF_ReadRobotState(boxID, rbtID,
                        nMovingState, nEnableState, nErrorState, nErrorCode, nErrorAxis,
                        nBreaking, nPause, nEmergencyStop, nSaftyGuard, nElectrify,
                        nIsConnectToBox, nBlendingDone, nInpos);
    return nInpos;
    // 现在你可以使用nInpos
    //cout << "nInpos: " << nInpos << endl;
}