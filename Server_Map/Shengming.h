#ifndef S_NETGLOBAL_H_
#define S_NETGLOBAL_H_
//#include <afxres.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <Winsock2.h>
#include <fstream>
#include <tchar.h>
#include <time.h>
#include <map>
BOOL ReadServerInfo(void);
BOOL ReadServerInfoUpdate(void);

#include "..\include\TimeLog.h"
#include "..\include\MAIN_DataTypeAndProtocol.h"
#include "S02_MyServer.h"
#include "S03_MyUser.h"
#include "S04_MyWork01.h"
#include "H05_MyTransfer.h"
#include "H07_MyGmae.h"
#include "H06_MyUpperCom.h"
#include "H10_MySummonSystem.h"
#include "H08_MyGameSystem.h"
#include "H09_MyWorld.h"
#include "H11_Sphinx.h"
#include "H12_SphinxAlgorithm.h"
#include "H13_Math_For_Server.h"
#include "BugTrap/BugTrap.h"
#include "Helpers.h"
#pragma comment(lib, "BugTrap/BugTrap.lib")


#define MAX_OTHER_KILL_POINT										300000
#define MAX_WRONG_ANSWER_COUNT										3	// MAX YANLIÞ CEVAP
#define LIMIT_SEND_TIME_MINUTE										1	// SORU BEKLEME SÜRESÝ

////server
#define WM_USER_NEW                                                 10
#define WM_NETWORK_MESSAGE_1										WM_USER_NEW + 1
#define WM_NETWORK_MESSAGE_2										WM_USER_NEW + 2
#define WM_NETWORK_MESSAGE_3										WM_USER_NEW + 3
#define WM_TIMER_NEW                                                WM_USER_NEW + 10
#define ID_TIMER                                                    1
/////
//-------------------------------------------------------------------------------------------------
//ZONE_NUMBER
//-------------------------------------------------------------------------------------------------
#define ZONE_PRISON						88	// HAPÝSHANE
#define ZONE_BASE_JUNG					1	// EJDER
#define ZONE_BASE_SA					6	// YILAN
#define ZONE_BASE_MA					11	// PARS
#define ZONE_BASE_NANG					140	//GÖK KAVMÝ
//-------------------------------------------------------------------------------------------------

extern DWORD mBaseTickCountForLogic;
extern DWORD mPostTickCountForLogic;
extern BOOL mCheckLogicFlag;

typedef struct
{
	char mServerName[100];
	int mServerPort;
	int mServerMaxUserNum;
	int mServerNumber;
	int mWorldNumber;
	char mUpperServer_1_IP[16];
	int mUpperServer_1_Port;
	char mUpperServer_2_IP[16];
	int mUpperServer_2_Port;
	char mUpperServer_3_IP[16];
	int mUpperServer_3_Port;
	char mUpperServer_4_IP[16];
	int mUpperServer_4_Port;
	char mUpperServer_5_IP[16];
	int mUpperServer_5_Port;
	int m_iDeploymentStage;
	int mCheckPremiumServer; // ÇÁ¸®¹Ì¾ö ¼­¹ö(¿ùµå) ¿©ºÎ(0ÀÌ¸é ÀÏ¹Ý ¼­¹ö, 1ÀÌ¸é ÇÁ¸®¹Ì¾ö ¼­¹ö). // @_Premium_Server_@
	char mGameLogIp[16];
	int mGameLogPort;
	float WORLD_EXP;
	float WORLD_ITEM_DROP;
	float WORLD_ITEM_DROP_FM;
	int  WORLD_KTAV;
	int  WORLD_BINEKEXP;
	float WORLD_PATEXP;
	int WORLD_TEACHER_POINT;
	int  WORLD_EXPLOSS;
	int  WORLD_PVPXP;
	int WORLD_MONSTER_DROP_MONEY;
	int WORLD_GODITEM_DROP;
	int WORLD_EARTH_CHEST_DROP;
	int WORLD_DIAMOND_DROP;
	int WORLD_FEATHER_DROP;
	int WORLD_SKILL_BOX_DROP;
	int WORLD_IMPROVE_STONE_DROP;
	int WORLD_8TH_DROP;
	int OUTPOST_FEATHER_DROP;
	int OUTPOST_DIAMOND_DROP;
	int OUTPOST_5_MOUNT_DROP;
	int OUTPOST_HEAVENLY_CHEST_DROP;
	int OUTPOST_ASIRLIK_ALTIN_DROP;
	int OUTPOST_BLACK_FEATHER_DROP;
	int OUTPOST_IKSIR_DROP;
	int OUTPOST_SKILL_BOX_DROP;
	int OUTPOST_TREASURE_MONSTER_BOX;
	int OUTPOST_10_MOUNT_BOX_DROP;
	int OUTPOST_15_MOUNT_BOX_DROP;
	int OUTPOST_8_BK_CRAFT_DROP;
	int PK_IOS_KEY_DROP;
	int WORLD_2_SOCKET_RATE;
	int WORLD_3_SOCKET_RATE;
	int WORLD_4_SOCKET_RATE;
	int WORLD_5_SOCKET_RATE;
	char mValet_Ip[16];
	int mValet_Port;
	std::string IP;
}
SERVER_INFO;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern void BugTrapInit(void);

extern HWND hMainWindow;
extern SERVER_INFO mSERVER_INFO;
#endif
