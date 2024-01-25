#include "Shengming.h"
#pragma comment(lib,"WS2_32")
LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
BOOL GetOneValueFromFile( HANDLE hFile, char *tBuffer, int tBufferSize );
BOOL ReadServerInfo( void );
HWND hMainWindow;
SERVER_INFO mSERVER_INFO;
void BugTrapInit(void);


int _tmain(int argc, _TCHAR* argv[])
{
	if (BUGTRAP_ACTIVE == 1)
	{
		BugTrapInit();
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

	if( !ReadServerInfo() )
	{
		__LogMgr()->Log( "[Error::ReadServerInfo(%s)]", "SERVER");
	}
	if(!mSERVER.Init(&ret))
	{
		__LogMgr()->Log("[Error::mSERVER.Init()]-(%d)", ret );
	}
	if(ret == NULL) __LogMgr()->Log("mSERVER_INFO.mServerPort%d]",mSERVER_INFO.mServerPort);

	while(::GetMessage(&msg,NULL,0,0))
	{
		::TranslateMessage(&msg);//转化键盘消息
		::DispatchMessage(&msg);//将消息发送到相应窗口函数
	}

	return msg.wParam;//当GETMESSAGE返回0时结束
}

LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch( uMsg )
	{
	case WM_NETWORK_MESSAGE_1 :
		mSERVER.PROCESS_FOR_NETWORK( hWnd, wParam, lParam );
		return 0;
	case WM_TIMER :
		mSERVER.PROCESS_FOR_TIMER();
		return 0;
	case WM_DESTROY :
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hWnd,	uMsg, wParam,lParam);

}

BOOL ReadServerInfo( void )
{
	HANDLE hFile;
	char tempString01[100];

	hFile = CreateFile( "CONFIG\\RELAY_SERVER_INFO.TXT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		return FALSE;
	}
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mServerName, tempString01 );
	if( strcmp( mSERVER_INFO.mServerName, "" ) == 0 )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mServerPort = atoi( tempString01 );
	if( ( mSERVER_INFO.mServerPort < 10000 ) || ( mSERVER_INFO.mServerPort > 99999 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	mSERVER_INFO.mWorldNumber = atoi( tempString01 );
	if( ( mSERVER_INFO.mWorldNumber < 1 ) || ( mSERVER_INFO.mWorldNumber > 999 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	if( !CloseHandle( hFile ) )
	{
		return FALSE;
	}
	return TRUE;
}
//GET_ONE_VALUE_FROM_FILE
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

//BUG_TRAP_INIT
void BugTrapInit(void)
{
	BT_InstallSehFilter();
	BT_SetAppName("SailorSky2 Relay BugTrap");
	BT_SetReportFilePath("C:\\BugTrap");
	BT_SetFlags(BTF_DETAILEDMODE);
}