
//using namespace std;



using namespace std;
string Msg;
int nRet;



void HR_connect()
{

}

void init()
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

void move(float arr[],int size)
{
    int test=0;
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
        //cout<<dX<<endl;
        
        // 定义关节命令位置
        double dJ1 = 0; double dJ2 = 0; double dJ3 = 0;
        double dJ4 = 0; double dJ5 = 0; double dJ6 = 0;
        // 读取关节命令位置
        int nRet = HRIF_ReadActJointPos(0,0, dJ1 , dJ2 , dJ3 , dJ4 , dJ5 , dJ6);
        // 执行路点运动
        int nRetaa = HRIF_WayPoint(0, 0,nMoveType , dX , dY , dZ , dRx , dRy , dRz , dJ1 , dJ2 , dJ3 , dJ4 , dJ5 , dJ6 ,sTcpName , sUcsName, dVelocity, dAcc, dRadius,nIsUseJoint, nIsSeek, nIOBit, nIOState, strCmdID);
        sleep(2.5); 
        std :: cout << "test:" << test++ << std :: endl;
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
    int nRet= HRIF_GrpDisable(0,0);
    cout << "cobot_running_done"<<endl;

    
}


int main()
{
    HR_connect();
    init();
    //int nRet= HRIF_MoveRelJ(0,0,1 ,1,10);//关节运动
/*     float point[] = {520.0,0.0,572.0,
                     180.0,0.0,180.0,
                     530.1,50.0,550.0,
                     180.0,0.0,180.0,
                     520.0,0.0,572.0,
                     180.0,0.0,180.0};//位置坐标（6个一组）  */
    float point[] = {200.0,50.0,700.0,
                    0.0,0.0,5.0,

                    200.0,100.0,700.0,
                    0.0,0.0,5.0,

                    200.0,150.0,700.0,
                    0.0,0.0,5.0,

                    200.0,200.0,700.0,
                    0.0,0.0,5.0,

                    200.0,150.0,700.0,
                    0.0,0.0,5.0,

                    200.0,100.0,700.0,
                    0.0,0.0,5.0,

                    };//位置坐标（6个一组） 
    int size = sizeof(point) / sizeof(point[0]);
    move(point,size);    
    return 0;
}