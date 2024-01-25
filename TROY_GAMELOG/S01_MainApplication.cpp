//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "H01_MainApplication.h"
#include "../include/MAIN_DataTypeAndProtocol.h"
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CALLBACK_FUNCTION
//-------------------------------------------------------------------------------------------------
LRESULT CALLBACK WinMainProcedure( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm );
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//APPLICATION_FUNCTION
//-------------------------------------------------------------------------------------------------
BOOL ReadServerInfo( void );
BOOL GetOneValueFromFile( HANDLE hFile, char *tBuffer, int tBufferSize );
BOOL ApplicationInit( void );
void ApplicationFree( void );
void BugTrapInit( void );
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//GLOBAL_VARIABLES
//-------------------------------------------------------------------------------------------------
HWND hMainWindow;
SERVER_INFO mSERVER_INFO;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//WIN_MAIN
//-------------------------------------------------------------------------------------------------
int WINAPI WinMain( HINSTANCE hThis, HINSTANCE hPrev, LPSTR lArgs, int nMode )
{
	if (BUGTRAP_ACTIVE == 1)
	{
		BugTrapInit();
	}

	if( !ReadServerInfo() )
	{
		MessageBox( NULL, "[Error::ReadServerInfo()]", "SERVER", ( MB_OK | MB_SYSTEMMODAL ) );
		return FALSE;
	}

	WNDCLASSEX wCls;
	MSG nMss;

	wCls.cbSize	= sizeof( WNDCLASSEX );
	wCls.style = CS_HREDRAW | CS_VREDRAW;
	wCls.lpfnWndProc = WinMainProcedure;
	wCls.cbClsExtra = 0;
	wCls.cbWndExtra = 0;
	wCls.hInstance = hThis;
	wCls.hIcon = LoadIcon( hThis, MAKEINTRESOURCE(IDI_SERVER) );
	wCls.hCursor = LoadCursor( NULL, IDC_ARROW );
	wCls.hbrBackground = (HBRUSH) GetStockObject( BLACK_BRUSH );
	wCls.lpszMenuName = NULL;
	wCls.lpszClassName = mSERVER_INFO.mServerName;
	wCls.hIconSm = NULL;

	if( !RegisterClassEx( &wCls ) )
	{
		MessageBox( NULL, "[Error::RegisterClassEx()]", mSERVER_INFO.mServerName, ( MB_OK | MB_SYSTEMMODAL ) );

		return FALSE;
	}

	hMainWindow = CreateWindowEx( NULL, mSERVER_INFO.mServerName, mSERVER_INFO.mServerName, ( WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE ), ( GetSystemMetrics( SM_CXSCREEN ) / 2 - ( MAIN_WINDOW_SIZE_X / 2 ) ), ( GetSystemMetrics( SM_CYSCREEN ) / 2 - ( MAIN_WINDOW_SIZE_Y / 2 ) ), MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y, HWND_DESKTOP, NULL, hThis, NULL );
	if( !hMainWindow )
	{
		MessageBox( NULL, "[Error::CreateWindow()]", mSERVER_INFO.mServerName, ( MB_OK | MB_SYSTEMMODAL ) );

		return FALSE;
	}
	
	ShowWindow( hMainWindow, SW_MINIMIZE );
	UpdateWindow( hMainWindow );

	if( !ApplicationInit() )
	{
		ApplicationFree();
		MessageBox( NULL, "[Error::ApplicationInit()]", mSERVER_INFO.mServerName, ( MB_OK | MB_SYSTEMMODAL ) );

		return FALSE;
	}

	while( GetMessage( &nMss, NULL, 0, 0 ) )
	{
		TranslateMessage( &nMss );
		DispatchMessage( &nMss );
	}

	ApplicationFree();

	return nMss.wParam;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//CALLBACK_FUNCTION
//-------------------------------------------------------------------------------------------------
//WIN_MAIN_PROCEDURE
LRESULT CALLBACK WinMainProcedure( HWND hWnd, UINT nMss, WPARAM wPrm, LPARAM lPrm )
{
	switch( nMss )
	{
	case WM_NETWORK_MESSAGE_1 :
		mSERVER.PROCESS_FOR_NETWORK( hWnd, wPrm, lPrm );
		return 0;
	case WM_DESTROY :
		PostQuitMessage( 0 );
		return 0;
	}
	return DefWindowProc( hWnd,	nMss, wPrm,	lPrm );
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//APPLICATION_FUNCTION
//-------------------------------------------------------------------------------------------------
//READ_SERVER_INFO
BOOL ReadServerInfo( void )
{
	DWORD tResult = 0;
	char tKeyValue[100] = {0, };
	char *tIniFileName = "./CONFIG/Logger.ini";

	tResult = ::GetPrivateProfileString("Server Info", "ServerName", NULL, tKeyValue, 100, tIniFileName);
	if(tResult == 0) {
		return FALSE;
	}
	strcpy(mSERVER_INFO.mServerName, tKeyValue);
	if(::strlen(mSERVER_INFO.mServerName) == 0) {
		return FALSE;
	}

	tResult = ::GetPrivateProfileString("Server Info", "WorldNum", NULL, tKeyValue, 100, tIniFileName);
	if(tResult == 0) {
		return FALSE;
	}
	mSERVER_INFO.mWorldNumber = atoi(tKeyValue);
	if(mSERVER_INFO.mWorldNumber < 0 || mSERVER_INFO.mWorldNumber > 100) {
		return FALSE;
	}

	tResult = ::GetPrivateProfileString("Server Info", "ServerPort", NULL, tKeyValue, 100, tIniFileName);
	if(tResult == 0) {
		return FALSE;
	}
	mSERVER_INFO.mServerPort = atoi(tKeyValue);
	if(mSERVER_INFO.mServerPort < 0 || mSERVER_INFO.mServerPort > 65535) {
		return FALSE;
	}	

	return TRUE;
}

//APPLICATION_INIT
BOOL ApplicationInit( void )
{
	char tempString01[1000];
	int tResult;

	if( !mSERVER.Init( &tResult ) )
	{
		sprintf( tempString01, "[Error::mSERVER.Init()]-(%d)", tResult );
		MessageBox( NULL, tempString01, mSERVER_INFO.mServerName, ( MB_OK | MB_SYSTEMMODAL ) );
		return FALSE;
	}
	return TRUE;
}
//APPLICATION_FREE
void ApplicationFree( void )
{
	mSERVER.Free();
}
//BUG_TRAP_INIT
void BugTrapInit( void )
{
	BT_InstallSehFilter();
	BT_SetAppName("Inferno BugTrap");
	BT_SetReportFilePath("C:\\BugTrap");
	BT_SetFlags(BTF_DETAILEDMODE);
}
//-------------------------------------------------------------------------------------------------
