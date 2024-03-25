#include <iostream>
#include "../inc/HR_Pro.h"
//#include "/home/wayne/Desktop/HansSDK/inc/HR_Pro.h"
#include <vector>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

bool m_bSendPoint = false;

vector<vector<double>> vecvecPoints;

int ReadPoint()
{
    vecvecPoints.clear();
    ifstream inRead; 
    inRead.open("/mnt/hgfs/HansRobotV5/HansSDK/inc/servoJ.txt");

    string strLine;
    vector<string> vecString;
    while(getline(inRead,strLine))
    {
        vecString.push_back(strLine);
    }
    inRead.close();  
    vector<double> vecPoint;
    for (size_t i = 0; i < vecString.size(); i++)
    {
        string sMark = ",";
        string sValTmp(vecString[i]);
        if (sValTmp.empty() || sMark.empty())
        {
            return 0;
        }
        if (sValTmp[sValTmp.size() - 1] != sMark[0])
        {
            sValTmp.append(sMark);
        }
        if (sValTmp.empty() || sMark.empty())
        {
            return 0;
        }
        if (sValTmp.size() > 0)
        {
            string::size_type stPos = string::npos, tmpPos = string::npos;
            stPos = sValTmp.find(sMark);
            string sTmp;
            unsigned long iLen = sMark.size();
            vecPoint.clear();
            while (stPos != string::npos)
            {
                sTmp = sValTmp.substr(0, stPos);
                tmpPos = sTmp.length() + iLen;
                sValTmp = sValTmp.substr(tmpPos, sValTmp.length());
                stPos = sValTmp.find(sMark);
                vecPoint.push_back(atof(sTmp.c_str()));
                
            }
            vecvecPoints.push_back(vecPoint);
        }
    }    
    return 0; 
}

void *thread_ReadServEsJState(void *args)
{
    int nState = 0;
    int nIndex = 0;
    int nCount = 0;
    int nRet = 0;
    bool bSendPoints = false;
    int nCnt = 0;

    while (false)
    {
        if(m_bSendPoint)
        {
			// 读取当前状态，1：可以继续下发点位
            nRet = HRIF_ReadServoEsJState(0,0,nState,nIndex,nCount);
            if(nRet != 0)
            {
                printf("ReadServoEsJState_error:%d,%d\n",nRet,nState);
                return NULL;
            }
			// 1：可以继续下发点位
            if(nState == 1)
            {
                string sPoints = "";
                double dJoint[6] = { 0 };
				// 发送10次往返点位数据后再下发355个点位后停止下发
                if(nCnt > 10)
                {
					// 往返运动标志
                    if(!bSendPoints)
                    {
						//关节1-6:，从0°运动到35.5°
                        printf("SendPoints:cnt=%d\n",nCnt);
                        for (size_t i = 0; i < 355; i++)
                        {
                            for (size_t j = 0; j < 6; j++)
                            {
                                sPoints = sPoints + to_string(dJoint[0] + (i*10) / 100.0 + 50);
                                sPoints = sPoints + ",";
                            }
                        }
						// 删除末尾逗号
                        sPoints = sPoints.substr(0,sPoints.length()-1);
						// 下发点位
                        nRet = HRIF_PushServoEsJ(0,0, 355, sPoints);
                        if(nRet != 0)
                        {
                            printf("PushServoEsJ_error:%d,%d\n",nRet,nState);
                            return NULL;
                        }
                        bSendPoints = true;
                    }
                    else
                    {
						//关节1-6:，从50°运动到14.5°
                        printf("SendPoints:cnt=%d\n",nCnt);
                        for (size_t i = 0; i < 355; i++)
                        {
                            for (size_t j = 0; j < 6; j++)
                            {
                                sPoints = sPoints + to_string(dJoint[0] + 50 - (i*10) / 100.0 + 50);
                                sPoints = sPoints + ",";
                            }
                        }
						// 删除末尾逗号
                        sPoints = sPoints.substr(0,sPoints.length()-1);
						// 下发点位
                        nRet = HRIF_PushServoEsJ(0,0, 355, sPoints);
                        if(nRet != 0)
                        {
                            printf("PushServoEsJ_error:%d,%d\n",nRet,nState);
                            return NULL;
                        }
                        bSendPoints = false;
                    }
                    return NULL;
                }
				
				// 发送10次往返点位数据
                if(!bSendPoints)
                {
                    printf("SendPoints:cnt=%d\n",nCnt);
                    for (size_t i = 0; i < 500; i++)
                    {
                        for (size_t j = 0; j < 6; j++)
                        {
                            sPoints = sPoints + to_string(dJoint[0] + (i*10) / 100.0 + 50);
                            sPoints = sPoints + ",";
                        }
                    }
					// 删除末尾逗号
                    sPoints = sPoints.substr(0,sPoints.length()-1);
					// 下发点位
                    nRet = HRIF_PushServoEsJ(0,0, 500, sPoints);
                    if(nRet != 0)
                    {
                        printf("PushServoEsJ_error:%d,%d\n",nRet,nState);
                        return NULL;
                    }
                    bSendPoints = true;
                }
                else
                {
                    printf("SendPoints:cnt=%d\n",nCnt);
                    for (size_t i = 0; i < 500; i++)
                    {
                        for (size_t j = 0; j < 6; j++)
                        {
                            sPoints = sPoints + to_string(dJoint[0] + 50 - (i*10) / 100.0 + 50);
                            sPoints = sPoints + ",";
                        }
                    }
					// 删除末尾逗号
                    sPoints = sPoints.substr(0,sPoints.length()-1);
					// 下发点位
                    nRet = HRIF_PushServoEsJ(0,0, 500, sPoints);
                    if(nRet != 0)
                    {
                        printf("PushServoEsJ_error:%d,%d\n",nRet,nState);
                        return NULL;
                    }
                    bSendPoints = false;
                }
                nCnt += 1;
            }
        }
		// 读取状态延时，建议>20ms
        usleep(50*1000);
    }
    return NULL;
}

int HR_MoveServoEs()
{
    ReadPoint();
    int nRet = 0;
    int nState = 0;
    int nIndex = 0;
    int nCount = 0;
    int nCnt = 0;
    string sPoints = "";
    double dJoint[6] = { 0 };

	// Servo时间-点位下发间隔时间
    double dServoTime = 0.004;
	// 前瞻时间
    double dLookaheadTime = 0.008;
    int nPointCnt = 0;
    	
    // 初始化参数
    nRet = HRIF_InitServoEsJ(0,0);
    if(nRet != 0)
    {
        printf("[error]HRIF_InitServoEsJ:nRet=%d\n",nRet);
        return nRet;
    }
    
    //关节1-6:，从0°运动到50°
    for (size_t i = 0; i < 500; i++)
    {
        sPoints = sPoints + to_string(nPointCnt);
        sPoints = sPoints + ",";
        for (size_t j = 0; j < 6; j++)
        {
            sPoints = sPoints + to_string(vecvecPoints[i][j]);
            sPoints = sPoints + ",";
        }
        nPointCnt ++;
    }
	// 删除末尾逗号
    sPoints = sPoints.substr(0,sPoints.length()-1);
	// 下发点位
    nRet = HRIF_PushServoEsJ(0,0, 500, sPoints);
    if(nRet != 0)
    {
        printf("[error]HRIF_PushServoEsJ1:nRet=%d,nState=%d\n",nRet,nState);
        return nRet;
    }
    while (true)
    {
		// 读取当前状态，1：可以继续下发点位
        nRet = HRIF_ReadServoEsJState(0,0,nState,nIndex,nCount);
        if(nRet != 0)
        {
            printf("[error]HRIF_PushServoEsJ2:nRet=%d,nState=%d\n",nRet,nState);
            return 0;
        }
        if(nState == 0)
        {
            break;
        }
        usleep(10 * 1000);
    }
    sPoints.clear();
    //关节1-6:，从50°运动到0°
    for (size_t i = 0; i < 500; i++)
    {
        sPoints = sPoints + to_string(nPointCnt);
        sPoints = sPoints + ",";
        for (size_t j = 0; j < 6; j++)
        {
            sPoints = sPoints + to_string(vecvecPoints[500 + i][j]);
            sPoints = sPoints + ",";
        }
        nPointCnt ++;
    }
	// 删除末尾逗号
    sPoints = sPoints.substr(0,sPoints.length()-1);
	// 下发点位
    nRet = HRIF_PushServoEsJ(0,0, 500, sPoints);
    if(nRet != 0)
    {
        printf("[error]HRIF_PushServoEsJ3:nRet=%d,nState=%d\n",nRet,nState);
        return nRet;
    }

	// 延时等待缓存点位下发完成
    usleep(1000 * 1000);


	// 开始运动
    nRet = HRIF_StartServoEsJ(0,0, dServoTime, dLookaheadTime);
    if(nRet != 0)
    {
        printf("[error]HRIF_StartServoEsJ4:nRet=%d\n",nRet);
        return nRet;
    }

    int nSendCnt = 0;
    int nSize = vecvecPoints.size();
    while (true)
    {
		// 读取当前状态，1：可以继续下发点位
        nRet = HRIF_ReadServoEsJState(0,0,nState,nIndex,nCount);
        if(nRet != 0)
        {
            printf("[error]HRIF_PushServoEsJ5:nRet=%d,nState=%d\n",nRet,nState);
            return 0;
        }
        if(nState == 0 && (nCount - nIndex) < 600)
        {
            if((vecvecPoints.size() - (nSendCnt * 400 + 1000)) >= 400)
            {
                printf("[error]Cnt:nIndex=%d,nCount=%d\n",nIndex,nCount);
                sPoints.clear();
                //关节1-6:，从50°运动到0°
                for (size_t i = 0; i < 400; i++)
                {
                    sPoints = sPoints + to_string(nPointCnt);
                    sPoints = sPoints + ",";
                    for (size_t j = 0; j < 6; j++)
                    {
                        sPoints = sPoints + to_string(vecvecPoints[1000 + nSendCnt * 400 + i][j]);
                        sPoints = sPoints + ",";
                    }
                    nPointCnt ++;
                }
                // 删除末尾逗号
                sPoints = sPoints.substr(0,sPoints.length()-1);
                // 下发点位
                nRet = HRIF_PushServoEsJ(0,0, 400, sPoints);
                if(nRet != 0)
                {
                    printf("[error]HRIF_PushServoEsJ6:nRet=%d,nState=%d\n",nRet,nState);
                    return nRet;
                }
            }
            else
            {
                printf("[error]Cnt:nIndex=%d,nCount=%d\n",nIndex,nCount);
                sPoints.clear();
                //关节1-6:，从50°运动到0°
                for (size_t i = 0; i < vecvecPoints.size() - (nSendCnt * 400 + 1000); i++)
                {
                    sPoints = sPoints + to_string(nPointCnt);
                    sPoints = sPoints + ",";
                    for (size_t j = 0; j < 6; j++)
                    {
                        sPoints = sPoints + to_string(vecvecPoints[1000 + nSendCnt * 400 + i][j]);
                        sPoints = sPoints + ",";
                    }
                    nPointCnt ++;
                }
                // 删除末尾逗号
                sPoints = sPoints.substr(0,sPoints.length()-1);
                // 下发点位
                nRet = HRIF_PushServoEsJ(0,0, vecvecPoints.size() - (nSendCnt * 400 + 1000), sPoints);
                if(nRet != 0)
                {
                    printf("[error]HRIF_PushServoEsJ7:nRet=%d,nState=%d\n",nRet,nState);
                    return nRet;
                }
                break;
            }
            ++nSendCnt;
        }
        usleep(50 * 1000);
    }
    printf("[Info]nPointCnt=%d\n",nPointCnt);

	// 等待运动完成
    while(true)
    {
        bool bMoveDone = false;
        nRet = HRIF_IsMotionDone(0,0,bMoveDone);
        if(bMoveDone)
            return 0;
        usleep(10*1000);
    }
    usleep(1000 * 1000);
    return nRet;
}



int main()
{
    
	// 控制器IP地址
    string strIP = "192.168.0.10";
	// 控制器端口号
    int nPort = 10003;

	// 连接控制器
    int nRet = HRIF_Connect(0, strIP.c_str(), nPort);
    std::cout << "HRIF_Connect:" << nRet << std::endl;
    if(nRet != 0)
    {
       // std::cout << "HRIF_Connect:" << std::endl;
        return nRet;
    }
    nRet = HR_MoveServoEs();
    if(nRet != 0)
    {
        return nRet;
    }
  //  std::cout << "HRIF_Connect:" << std::endl;
/*     if(nRet != 0)
    {
        return nRet;
    }
    
    nRet = HR_MoveServoEs();
    if(nRet != 0)
    {
        return nRet;
    } */

    return 0;
}
