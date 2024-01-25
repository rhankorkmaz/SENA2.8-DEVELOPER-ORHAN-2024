#include "Shengming.h"
#pragma comment(lib,"WS2_32")
HWND hMainWindow;
SERVER_INFO mSERVER_INFO;
_g_env g_env;

BOOL ReadServerInfo( void );
BOOL GetOneValueFromFile( HANDLE hFile, char *tBuffer, int tBufferSize );
LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

int _tmain(int argc, _TCHAR* argv[])
{
	char szClassName[] = "MainWClass";
	WNDCLASSEX wndclass;
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
		::MessageBox(NULL, "Create Window Error", "ERROR", MB_OK);
		return -1;
	}
	hMainWindow = hWnd;

	system("color A");

	if (!ReadServerInfo())
	{
		//::MessageBox(NULL, "@ReadServerInfo", "ERROR", MB_OK);
		return -1;
	}
	g_env.world_num = 1;

	//Logger("!mServerName: %s", mSERVER_INFO.mServerName);
	//Logger("!mServerPort: %d", mSERVER_INFO.mServerPort);
	//Logger("!mWorldNumber: %d", mSERVER_INFO.mWorldNumber);

	int tResult;
	if( !mSERVER.Init( &tResult ) )
	{
		Logger("!mServer Init Error[%d]",tResult);
	}

	Logger("\nVALET SHOP SERVER STARTED, LISTEN PORT:[%d]\n", mSERVER_INFO.mServerPort);
	
	MSG msg;
	while( ::GetMessage(&msg, NULL, 0, 0))
	{
		::DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
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


BOOL ReadServerInfo( void )
{
	HANDLE hFile;
	char tempString01[100];

	hFile = CreateFile( "CONFIG\\VALET_SERVER_INFO.TXT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE )
	{
		::MessageBox(NULL, "@ReadServerInfo 1", "ERROR", MB_OK);
		return FALSE;
	}

	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 2", "ERROR", MB_OK);
		return FALSE;
	}
	strcpy( mSERVER_INFO.mServerName, tempString01 );
	if( strcmp( mSERVER_INFO.mServerName, "" ) == 0 )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 3", "ERROR", MB_OK);
		return FALSE;
	}

	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 4", "ERROR", MB_OK);
		return FALSE;
	}
	mSERVER_INFO.mServerPort = atoi( tempString01 );

	if( ( mSERVER_INFO.mServerPort < 10000 ) || ( mSERVER_INFO.mServerPort > 99999 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 5", "ERROR", MB_OK);
		return FALSE;
	}

	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 6", "ERROR", MB_OK);
		return FALSE;
	}
	mSERVER_INFO.mWorldNumber = atoi( tempString01 );

	if( ( mSERVER_INFO.mWorldNumber < 1 ) || ( mSERVER_INFO.mWorldNumber > 999 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 7", "ERROR", MB_OK);
		return FALSE;
	}

	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 8", "ERROR", MB_OK);
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_IP, tempString01 );

	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 9", "ERROR", MB_OK);
		return FALSE;
	}
	mSERVER_INFO.mDB_1_PORT = atoi( tempString01 );

	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 10", "ERROR", MB_OK);
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_ID, tempString01 );

	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 11", "ERROR", MB_OK);
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_1_PASSWORD, tempString01 );
	
	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_2_IP, tempString01 );

	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 13", "ERROR", MB_OK);
		return FALSE;
	}
	mSERVER_INFO.mDB_2_PORT = atoi( tempString01 );

	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 14", "ERROR", MB_OK);
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_2_ID, tempString01 );

	if( !GetOneValueFromFile( hFile, &tempString01[0], 100 ) )
	{
		CloseHandle( hFile );
		::MessageBox(NULL, "@ReadServerInfo 15", "ERROR", MB_OK);
		return FALSE;
	}
	strcpy( mSERVER_INFO.mDB_2_PASSWORD, tempString01 );
	
	CloseHandle( hFile );
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