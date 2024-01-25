#ifndef S_NETGLOBAL_H_
#define S_NETGLOBAL_H_

#include <iostream>
#include <string>

#include <Winsock2.h>
#include <fstream>
#include <tchar.h>
#include <time.h>
#include "..\include\MAIN_DataTypeAndProtocol.h"
#include "..\include\TimeLog.h"
#include "BugTrap/BugTrap.h"
#pragma comment(lib, "BugTrap/BugTrap.lib")
#include "H02_MyServer.h"
#include "H03_MyUser.h"
#include "H04_MyWork.h"
#include "H05_MyTransfer.h"

#include "H07_MyGame.h"
#include "H08_MyDB.h"


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
	char mUpperServer_2_IP[16];
	int mUpperServer_2_Port;
	char mDB_1_IP[26];
	int mDB_1_PORT;
	char mDB_1_ID[100];
	char mDB_1_PASSWORD[100];
	char mDB_1_Table01[100];
	char mDB_2_Table01[100];
	char mDB_2_Table02[100];
	char mDB_3_Table01[100];
	char mDB2_1_IP[26];
	int mDB2_1_PORT;
	char mDB2_1_ID[100];
	char mDB2_1_PASSWORD[100];
	char mDB2_1_Table01[100];
	int mCheckTestServer;
}
SERVER_INFO;

typedef struct __g_env
{
	int world_num;
	string db_name_str_obj;
} _g_env;
extern void BugTrapInit(void);
extern SERVER_INFO mSERVER_INFO;
extern HWND hMainWindow;
extern _g_env g_env;
#endif