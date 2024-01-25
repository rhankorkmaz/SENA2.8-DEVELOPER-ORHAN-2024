#ifndef S_NETGLOBAL_H_
#define S_NETGLOBAL_H_

#include <iostream>
#include <string>
#include <time.h>
#include <tchar.h>
#include <WinSock2.h>
#pragma comment(lib,"WS2_32")

#include "..\include\TimeLog.h"
#include "..\Include\MAIN_DataTypeAndProtocol.h"
#include "..\include\cts_mysql.h"


#include "Myserver.h"
#include "H03_MyUser.h"
#include "H04_MyWork.h"
#include "H05_MyTransfer.h"
#include "H06_MyUpperCom.h"
#include "H07_MyGame.h"
#include "MyDB.h"
#include "BugTrap/BugTrap.h"
#pragma comment(lib, "BugTrap/BugTrap.lib")

// #define MAX_SEND_BUFFER_SIZE										8196
// #define MAX_RECV_BUFFER_SIZE										8196
#define ID_TIMER                                                    0

using namespace std;

typedef struct __g_env
{
	string svr_name_str_obj;
	int tno_worker_process;
	int tno_startup_worker_thread;
	int tno_min_spare_worker_thread;
	int tno_max_spare_worker_thread;
	int tno_max_allowed_worker_thread;
	int tno_tmp_spare_worker_thread_to;
	int to_read;
	int listen_port;
	bool tcp_nodelay;
	int sock_sndbuf;
	int sock_rcvbuf;
#ifdef __USE_DB_POOL__
	string db_acct_str_obj;
	string db_acct_passwd_str_obj;
	string db_name_str_obj;
	string db_host_addr_str_obj;
	int db_host_port;
	int tno_db_start_up_conn;
	int tno_db_min_spare_conn;
	int tno_db_max_spare_conn;
	int tno_db_max_allowed_conn;
	int tno_db_maintenance_time;
#endif
	int tno_proc_maintenance_rc;
	int tno_proc_maintenance_time;
	int tno_db_maintenance_time;

	// game server configuration
	string db_acct_str_obj;
	string db_acct_passwd_str_obj;
	string db_name_str_obj;
	string db_host_addr_str_obj;
	int db_host_port;

	string db2_acct_str_obj;
	string db2_acct_passwd_str_obj;
	string db2_name_str_obj;
	string db2_host_addr_str_obj;
	string db2_host_addr2_str_obj;
	int db2_host_port;

	int premium_server; // 프리미엄 서버(월드) 여부(0이면 일반 서버, 1이면 프리미엄 서버). // @_Premium_Server_@
} _g_env;

typedef struct _SERVER_INFO
{
	char mServerName[100];
	int mServerPort;
	int mIslandNum;
	int mPartitionNum;
	int mWorldNumber;
	int mServerVersion;
	char mUpperServer_1_IP[16];
	int mUpperServer_1_Port;
	char mUpperServer_2_IP[16];
	int mUpperServer_2_Port;
	char mUpperServer_3_IP[16];
	int mUpperServer_3_Port;
	char mUpperServer_4_IP[16];
	int mUpperServer_4_Port;
	int mIyoyoAPNum;

	char mDB_1_IP[2][16];
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
	char mDB_2_IP[2][16];
	int mDB_2_PORT;
	char mDB_2_ID[100];
	char mDB_2_PASSWORD[100];
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
	char mDB_3_IP[2][16];
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
} SERVER_INFO;
extern void BugTrapInit(void);
extern _g_env g_env;
extern SERVER_INFO mSERVER_INFO;
extern HWND hMainWindow;
#endif