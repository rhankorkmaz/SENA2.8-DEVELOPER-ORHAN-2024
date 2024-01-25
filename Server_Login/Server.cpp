#include "Shengming.h"

_g_env g_env;
SERVER_INFO mSERVER_INFO;
HWND hMainWindow;

BOOL load_config(void);
BOOL GetOneValueFromFile( HANDLE hFile, char *tBuffer, int tBufferSize );
VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT_PTR iTimerID, DWORD dwTimer);
LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
void BugTrapInit(void);

int _tmain(int argc, _TCHAR* argv[])
{
	if (BUGTRAP_ACTIVE == 1)
	{
		BugTrapInit();
	}

	if (!load_config())
	{
		__LogMgr()->Log("加载配置项目失败");
	}

	char szClassName[] = "MainWClass";
	WNDCLASSEX wndclass;
	//用描述主窗口的参数填充WNDCLASSEX结构
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW|CS_VREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.cbWndExtra = 0;
	wndclass.cbClsExtra = 0;
	wndclass.hInstance = NULL;
	wndclass.hIcon = ::LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = ::LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;
	wndclass.hIconSm = NULL;
	::RegisterClassEx(&wndclass);
	//创建主窗口
	HWND hWnd = ::CreateWindowEx(
		0,
		szClassName,
		"",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		NULL,
		NULL);

	if(hWnd == NULL)
	{
		::MessageBox(NULL,"创建窗口出错！","error",MB_OK);
		return -1;
	}

	hMainWindow = hWnd;
	MSG msg;
	int ret = NULL;

	if(!mSERVER.Init(&ret))
	{
		__LogMgr()->Log("[Error::mSERVER.Init()]-(%d)", ret );
	}
	if(ret == NULL) 
		__LogMgr()->Log("服务器开启成功[%d]",g_env.listen_port);

	SetTimer(NULL, ID_TIMER, 10000, TimerProc);

	while(::GetMessage(&msg,NULL,0,0))
	{
		::DispatchMessage(&msg);//将消息发送到相应窗口函数
	}

	return (int)msg.wParam;//当GETMESSAGE返回0时结束
}



LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam) //消息处理
{
	switch( uMsg )
	{
	case WM_NETWORK_MESSAGE_1 :
		mSERVER.PROCESS_FOR_NETWORK( hWnd, wParam, lParam );
		return 0;
	case WM_TIMER :
		//mSERVER.PROCESS_FOR_TIMER();
		return 0;
	case WM_DESTROY :
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hWnd,	uMsg, wParam,lParam);

}

BOOL load_config(void) 
{
	HANDLE hFile = NULL;
	char tempString01[100];
	hFile = CreateFile( "CONFIG\\LOGIN_SERVER_INFO.TXT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.svr_name_str_obj = tempString01;
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.tno_worker_process = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.tno_startup_worker_thread = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.tno_min_spare_worker_thread = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.tno_max_spare_worker_thread = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.tno_max_allowed_worker_thread = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.tno_tmp_spare_worker_thread_to = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.to_read = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.listen_port = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.sock_sndbuf = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.sock_rcvbuf = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.tno_db_maintenance_time = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.tno_proc_maintenance_time = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.tno_proc_maintenance_rc = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.db_name_str_obj = tempString01;
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.db_acct_str_obj = tempString01;
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.db_acct_passwd_str_obj = tempString01;
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.db_host_addr_str_obj = tempString01;
	strcpy( mSERVER_INFO.mDB_1_IP[0], tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_IP[1], tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.db_host_port = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.db2_name_str_obj = tempString01;
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.db2_acct_str_obj = tempString01;
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.db2_acct_passwd_str_obj = tempString01;
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.db2_host_addr_str_obj = tempString01;
	strcpy( mSERVER_INFO.mDB_2_IP[0], tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_2_IP[1], tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	g_env.db2_host_port = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mIslandNum = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mPartitionNum = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mWorldNumber = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mServerVersion = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mIyoyoAPNum = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table01, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table02, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table03, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table04, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table05, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table06, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table07, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_Table08, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_2_Table01, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_2_Table02, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_2_Table03, tempString01 );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_2_Table04, tempString01 );

	strcpy( mSERVER_INFO.mDB_1_ID, g_env.db_acct_str_obj.c_str() );

	strcpy( mSERVER_INFO.mDB_1_PASSWORD, g_env.db_acct_passwd_str_obj.c_str() );


	strcpy( mSERVER_INFO.mDB_2_ID, g_env.db2_acct_str_obj.c_str() );
	strcpy( mSERVER_INFO.mDB_2_PASSWORD, g_env.db2_acct_passwd_str_obj.c_str() );
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mUpperServer_1_IP,tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mUpperServer_1_Port = ::atoi(tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mUpperServer_2_IP,tempString01);
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mUpperServer_2_Port = ::atoi(tempString01);
	CloseHandle( hFile );
	return TRUE;

}

BOOL GetOneValueFromFile( HANDLE hFile, char *tBuffer, int tBufferSize )
{
	int index01;
	DWORD nReadByte;
	BOOL tCheckSaveState;
	char tData;

	index01 = 0;
	tCheckSaveState = FALSE;
	while( TRUE )
	{
		if( !ReadFile( hFile, &tData, 1, &nReadByte, NULL ) )
		{
			return FALSE;
		}
		if( nReadByte != 1 )
		{
			return FALSE;
		}
		if( !tCheckSaveState )
		{
			if( tData == '[' )
			{
				tCheckSaveState = TRUE;
			}
		}
		else
		{
			if( tData == ']' )
			{
				tBuffer[index01] = '\0';
				break;
			}
			else
			{
				if( index01 < ( tBufferSize - 1 ) )
				{
					tBuffer[index01] = tData;
					index01++;
				}
				else
				{
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}


VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT_PTR iTimerID, DWORD dwTimer)
{
	//MessageBox(NULL, "Hello World!", "Test", MB_OK);
	int index01;
	DWORD tPresentTime;

	tPresentTime = GetTickCount();
	for( index01 = 0 ; index01 < MAX_USER_NUM ; index01++ )
	{
		if( !mUSER[index01].mCheckConnectState )
		{
			continue;
		}
		if( ( tPresentTime - mUSER[index01].mUsedTime ) > 60000 )
		{
			mUSER[index01].Quit();
			continue;
		}
		if( !mUSER[index01].mCheckValidState )
		{
			continue;
		}
		if( ( tPresentTime - mUSER[index01].mRegisterTime ) > 180000 )
		{
			if( mUSER[index01].mMoveZoneResult == 0 )
			{
				mPLAYUSER_COM.U_REGISTER_USER_FOR_LOGIN_2_SEND( mUSER[index01].mPlayUserIndex, &mUSER[index01].uID[0] );
				if( mPLAYUSER_COM.mRecv_Result != 0 )
				{
					mUSER[index01].Quit();
					continue;
				}
				mUSER[index01].mRegisterTime = tPresentTime;
			}
		}
	}

	mPLAYUSER_COM.U_LOGIN_OK_FOR_PLAYUSER_SEND();
	mDB.DB_PROCESS_01();
	if( mGAME.mMaxPlayerNum > 0 )
	{
		mPLAYUSER_COM.U_GET_PRESENT_USER_NUM_FOR_LOGIN_SEND();
		mGAME.mPresentPlayerNum = mPLAYUSER_COM.mRecv_PresentUserNum;
	}
}
//BUG_TRAP_INIT
void BugTrapInit(void)
{
	BT_InstallSehFilter();
	BT_SetAppName("SailorSky2 Login BugTrap");
	BT_SetReportFilePath("C:\\BugTrap");
	BT_SetFlags(BTF_DETAILEDMODE);
}