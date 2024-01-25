#ifndef S_NETGLOBAL_H_
#define S_NETGLOBAL_H_

#include <iostream>
#include <string>
#include <map>

#include <Winsock2.h>
#include <fstream>
#include <tchar.h>
#include <time.h>
#include "..\include\MAIN_DataTypeAndProtocol.h"
#include "..\include\TimeLog.h"
#include "H02_MyServer.h"
#include "H03_MyUser.h"
#include "H04_MyWork.h"
#include "H05_MyTransfer.h"
#include "H06_MyUpperCom.h"
#include "BugTrap/BugTrap.h"
#pragma comment(lib, "BugTrap/BugTrap.lib")

////server
#define WM_USER_NEW                                                 10
#define WM_NETWORK_MESSAGE_1										WM_USER_NEW + 1
/////


typedef struct
{
	char mServerName[100];
	int mServerPort;
	int mWorldNumber;
}
SERVER_INFO;

extern void BugTrapInit(void);
extern SERVER_INFO mSERVER_INFO;
extern HWND hMainWindow;
#endif