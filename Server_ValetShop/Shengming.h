#ifndef S_NETGLOBAL_H_
#define S_NETGLOBAL_H_
#include <iostream>
#include <string>
#include <stdio.h>
#include <Winsock2.h>
#include <fstream>
#include <tchar.h>
#include <time.h>
#include <map>

#if _MSC_VER 
#ifndef snprintf
#define snprintf _snprintf
#endif
#endif

#include "..\include\TimeLog.h"
#include "..\include\MAIN_DataTypeAndProtocol.h"

#include "H02_MyServer.h"
#include "H08_MyDB.h"
#include "H05_MyTransfer.h"
#include "H03_MyUser.h"
#include "H07_MyGame.h"
#include "H04_MyWork.h"


#define MAX_OTHER_KILL_POINT										300000
#define MAX_WRONG_ANSWER_COUNT										3
#define LIMIT_SEND_TIME_MINUTE										1

////server
#define WM_USER_NEW                                                 10
#define WM_NETWORK_MESSAGE_1										WM_USER_NEW + 1
/////

typedef struct
{
	char mServerName[100];
	int mServerPort;
	int mWorldNumber;
	char mUpperServer_1_IP[16];
	int mUpperServer_1_Port;
	char mDB_1_IP[16];
	int mDB_1_PORT;
	char mDB_1_ID[100];
	char mDB_1_PASSWORD[100];
	char mDB_1_Table01[100];
	char mDB_1_Table02[100];
	char mDB_1_Table03[100];
	char mDB_1_Table04[100];
	char mDB_1_Table05[100];
	char mDB_1_Table06[100];
	char mDB_1_Table07[100];
	char mDB_1_Table08[100];
	char mDB_1_Table09[100];
	char mDB_1_Table10[100];
	//Account DB
	char mDB_2_IP[16];
	int mDB_2_PORT;
	char mDB_2_ID[100];
	char mDB_2_PASSWORD[100];
	//---------
	char mDB_2_Table01[100];
	char mDB_2_Table02[100];
	char mDB_2_Table03[100];
	char mDB_2_Table04[100];
	char mDB_2_Table05[100];
	char mDB_2_Table06[100];
	char mDB_2_Table07[100];
	char mDB_2_Table08[100];
	char mDB_2_Table09[100];
	char mDB_2_Table10[100];
	char mDB_3_IP[16];
	int mDB_3_PORT;
	char mDB_3_ID[100];
	char mDB_3_PASSWORD[100];
	char mDB_3_Table01[100];
	char mDB_3_Table02[100];
	char mDB_3_Table03[100];
	char mDB_3_Table04[100];
	char mDB_3_Table05[100];
	char mDB_3_Table06[100];
	char mDB_3_Table07[100];
	char mDB_3_Table08[100];
	char mDB_3_Table09[100];
	char mDB_3_Table10[100];
}
SERVER_INFO;

typedef struct __g_env
{
	int world_num;
} _g_env;

extern _g_env g_env;
extern SERVER_INFO mSERVER_INFO;
extern HWND hMainWindow;
#endif