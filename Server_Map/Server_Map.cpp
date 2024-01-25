#include "Shengming.h"
#pragma comment(lib,"WS2_32")

BOOL GetOneValueFromFile(HANDLE hFile, char* tBuffer, int tBufferSize);
VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT_PTR iTimerID, DWORD dwTimer);
void BugTrapInit(void);
SERVER_INFO mSERVER_INFO;
DWORD mBaseTickCountForLogic;
DWORD mPostTickCountForLogic;
BOOL mCheckLogicFlag;
HWND hMainWindow;
#define MAIN_WINDOW_SIZE_X											300
#define MAIN_WINDOW_SIZE_Y											100

static    DWORD WINAPI DetectCar(LPVOID lpParameter);

int _tmain(int argc, _TCHAR* argv[])
{
	int ret;
	
	if (BUGTRAP_ACTIVE == 1)
	{
		BugTrapInit();
	}

  	mSERVER_INFO.mServerPort = atoi( argv[1] );
	mSERVER_INFO.mServerNumber = atoi( argv[2] );
	char MapAdý[20];
	char szClassName[30];
	mSERVER_INFO.IP = "127.0.0.1";

	sprintf(MapAdý, "Sailor Zone MAP : %03d", mSERVER_INFO.mServerNumber);
	sprintf(szClassName, "Sailor Zone MAP : %03d", mSERVER_INFO.mServerNumber);
	if (ReadServerInfo() == FALSE)
	{
		__LogMgr()->Log("ERROR READSERVERINFO");
	}
	
	
	WNDCLASSEX wndclass;
	//ÓÃÃèÊöÖ÷´°¿ÚµÄ²ÎÊýÌî³äWNDCLASSEX½á¹¹
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW|CS_VREDRAW;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.cbWndExtra = 0;
	wndclass.cbClsExtra = 0;
	wndclass.hInstance = NULL;
	wndclass.hIcon = ::LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = ::LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)::GetStockObject(LTGRAY_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szClassName;
	wndclass.hIconSm = NULL;

	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, "[Error::RegisterClassEx()]", MapAdý, (MB_OK | MB_SYSTEMMODAL));
		return FALSE;
	}
	hMainWindow = CreateWindowEx(NULL, szClassName, MapAdý, WS_DISABLED, (GetSystemMetrics(SM_CXSCREEN) / 2 - (MAIN_WINDOW_SIZE_X / 2)), (GetSystemMetrics(SM_CYSCREEN) / 2 - (MAIN_WINDOW_SIZE_Y / 2)), MAIN_WINDOW_SIZE_X, MAIN_WINDOW_SIZE_Y, HWND_DESKTOP, NULL, NULL, NULL);
	if (!hMainWindow)
	{
		MessageBox(NULL, "[Error::CreateWindow()]", MapAdý, (MB_OK | MB_SYSTEMMODAL));
		return FALSE;
	}

	printf("!mSERVER_INFO.mServerName: %s\n", mSERVER_INFO.mServerName);
	printf("!mSERVER_INFO.mServerPort: %d\n", mSERVER_INFO.mServerPort);
	printf("!mSERVER_INFO.mServerMaxUserNum: %d\n", mSERVER_INFO.mServerMaxUserNum);
	printf("!mSERVER_INFO.mServerNumber: %d\n", mSERVER_INFO.mServerNumber);
	printf("!mSERVER_INFO.mWorldNumber: %d\n", mSERVER_INFO.mWorldNumber);
	printf("!WORLD_EXP: %0.0f\n", mSERVER_INFO.WORLD_EXP);
	printf("!WORLD_ITEM_DROP: %0.0f\n", mSERVER_INFO.WORLD_ITEM_DROP);
	printf("!WORLD_ITEM_DROP_FM: %0.0f\n", mSERVER_INFO.WORLD_ITEM_DROP_FM);
	printf("!WORLD_KTAV: %d\n", mSERVER_INFO.WORLD_KTAV);
	printf("!WORLD_BINEKEXP: %d\n", mSERVER_INFO.WORLD_BINEKEXP);
	printf("!WORLD_PATEXP: %0.0f\n", mSERVER_INFO.WORLD_PATEXP);
	printf("!WORLD_EXPLOSS: %d\n", mSERVER_INFO.WORLD_EXPLOSS);
	printf("!WORLD_PVPXP: %d\n", mSERVER_INFO.WORLD_PVPXP);
	printf("!WORLD_MONEY: %d\n", mSERVER_INFO.WORLD_MONSTER_DROP_MONEY);
	printf("!WORLD_MONSTER_DROP_MONEY: %d\n", mSERVER_INFO.WORLD_MONSTER_DROP_MONEY);
	printf("!WORLD_GODITEM_DROP: %d\n", mSERVER_INFO.WORLD_GODITEM_DROP);
	printf("!WORLD_EARTH_CHEST_DROP: %d\n", mSERVER_INFO.WORLD_EARTH_CHEST_DROP);
	printf("!WORLD_DIAMOND_DROP: %d\n", mSERVER_INFO.WORLD_DIAMOND_DROP);
	printf("!WORLD_FEATHER_DROP: %d\n", mSERVER_INFO.WORLD_FEATHER_DROP);
	printf("!WORLD_SKILL_BOX_DROP: %d\n", mSERVER_INFO.WORLD_SKILL_BOX_DROP);
	printf("!WORLD_IMPROVE_STONE_DROP: %d\n", mSERVER_INFO.WORLD_IMPROVE_STONE_DROP);
	printf("!WORLD_8TH_DROP: %d\n", mSERVER_INFO.WORLD_8TH_DROP);
	printf("!OUTPOST_FEATHER_DROP: %d\n", mSERVER_INFO.OUTPOST_FEATHER_DROP);
	printf("!OUTPOST_DIAMOND_DROP: %d\n", mSERVER_INFO.OUTPOST_DIAMOND_DROP);
	printf("!OUTPOST_5_MOUNT_DROP: %d\n", mSERVER_INFO.OUTPOST_5_MOUNT_DROP);
	printf("!OUTPOST_HEAVENLY_CHEST_DROP: %d\n", mSERVER_INFO.OUTPOST_HEAVENLY_CHEST_DROP);
	printf("!OUTPOST_ASIRLIK_ALTIN_DROP: %d\n", mSERVER_INFO.OUTPOST_ASIRLIK_ALTIN_DROP);
	printf("!OUTPOST_BLACK_FEATHER_DROP: %d\n", mSERVER_INFO.OUTPOST_BLACK_FEATHER_DROP);
	printf("!OUTPOST_IKSIR_DROP: %d\n", mSERVER_INFO.OUTPOST_IKSIR_DROP);
	printf("!OUTPOST_SKILL_BOX_DROP: %d\n", mSERVER_INFO.OUTPOST_SKILL_BOX_DROP);
	printf("!OUTPOST_TREASURE_MONSTER_BOX: %d\n", mSERVER_INFO.OUTPOST_TREASURE_MONSTER_BOX);
	printf("!OUTPOST_10_MOUNT_BOX_DROP: %d\n", mSERVER_INFO.OUTPOST_10_MOUNT_BOX_DROP);
	printf("!OUTPOST_15_MOUNT_BOX_DROP: %d\n", mSERVER_INFO.OUTPOST_15_MOUNT_BOX_DROP);
	printf("!OUTPOST_8_BK_CRAFT_DROP: %d\n", mSERVER_INFO.OUTPOST_8_BK_CRAFT_DROP);
	printf("!PK_IOS_KEY_DROP: %d\n", mSERVER_INFO.PK_IOS_KEY_DROP);
	printf("!WORLD_2_SOCKET_RATE: %d\n", mSERVER_INFO.WORLD_2_SOCKET_RATE);
	printf("!WORLD_3_SOCKET_RATE: %d\n", mSERVER_INFO.WORLD_3_SOCKET_RATE);
	printf("!WORLD_4_SOCKET_RATE: %d\n", mSERVER_INFO.WORLD_4_SOCKET_RATE);
	printf("!WORLD_5_SOCKET_RATE: %d\n", mSERVER_INFO.WORLD_5_SOCKET_RATE);


 	mSERVER_INFO.m_iDeploymentStage = 4;
	mSERVER_INFO.mServerMaxUserNum = 200;
 	//mSERVER_INFO.mCheckPremiumServer = 1; // ÇÁ¸®¹Ì¾ö ¼­¹ö(¿ùµå) ¿©ºÎ(0ÀÌ¸é ÀÏ¹Ý ¼­¹ö, 1ÀÌ¸é ÇÁ¸®¹Ì¾ö ¼­¹ö). // @_Premium_Server_@
	switch( mSERVER_INFO.mServerNumber )
	{
	case  49 :
	case  51 :
	case  53 :
	case 146 :
	case 147 :
	case 148 :
	case 149 :
	case 150 :
	case 151 :
	case 152 :
	case 153 :
		mSERVER_INFO.mServerMaxUserNum = 90;
		break;
	case 154 :
	case 155 :
	case 156 :
	case 157 :
	case 158 :
	case 159 :
	case 160 :
	case 161 :
	case 162 :
	case 163 :
	case 164 :
		mSERVER_INFO.mServerMaxUserNum = 120;
		break;
	}
	UpdateWindow(hMainWindow);
	DWORD ID = NULL;
	int tResult = NULL;
	if( !mSERVER.Init( &tResult ) )
	{
		printf("[Error::mSERVER.Init()]-(%d)\n", tResult ); 
		MessageBox(NULL, "[Error::ApplicationInit()]", MapAdý, (MB_OK | MB_SYSTEMMODAL));
		getchar();
		return 0;
	}

	if (tResult == NULL)
	{
		printf("Zone %d Started listening in port : [%d]\n", mSERVER_INFO.mServerNumber, mSERVER_INFO.mServerPort);
		ID = SetTimer(NULL, ID_TIMER, 100, TimerProc);
	}

	mBaseTickCountForLogic = GetTickCount();
	mPostTickCountForLogic = mBaseTickCountForLogic;
	mCheckLogicFlag = FALSE;
	MSG msg;
	while (::GetMessage(&msg, NULL, 0, 0))
	{
		::DispatchMessage(&msg);//
		if (mCheckLogicFlag)
		{
			mCheckLogicFlag = FALSE;
			mGAME.Logic(0.5f);
		}
	}
	return msg.wParam;
}
VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT_PTR iTimerID, DWORD dwTimer)
{
	mBaseTickCountForLogic = GetTickCount();
	if ((mBaseTickCountForLogic - mPostTickCountForLogic) > 500)
	{
		mPostTickCountForLogic = mBaseTickCountForLogic;
		mCheckLogicFlag = TRUE;
	}
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	std::chrono::high_resolution_clock::time_point t1;
	std::chrono::high_resolution_clock::time_point t2;
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	int r = NULL;
	switch (uMsg)
	{
	case WM_NETWORK_MESSAGE_1:
		mSERVER.PROCESS_FOR_NETWORK(hWnd, wParam, lParam);
		return 0;
	case WM_NETWORK_MESSAGE_2:
		r = mCENTER_COM.PROCESS_FOR_NETWORK(hWnd, wParam, lParam);
		return r;
	case WM_NETWORK_MESSAGE_3:
		r = mRELAY_COM.PROCESS_FOR_NETWORK(hWnd, wParam, lParam);
		return r;
	}
}

BOOL ReadServerInfo(void)
{
	HANDLE hFile;
	char tempString01[100];
	hFile = CreateFile("CONFIG\\SERVER_INFO.TXT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		__LogMgr()->Log("[#001]");
		CloseHandle(hFile);
		return FALSE;
	}
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#002]");
		CloseHandle(hFile);
		return FALSE;
	}
	strcpy(mSERVER_INFO.mServerName, tempString01);
	if (strcmp(mSERVER_INFO.mServerName, "") == 0)
	{
		__LogMgr()->Log("[#003]");
		CloseHandle(hFile);
		return FALSE;
	}
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#006]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.mServerMaxUserNum = atoi(tempString01);
	if ((mSERVER_INFO.mServerMaxUserNum < 1) || (mSERVER_INFO.mServerMaxUserNum > MAX_AVATAR_OBJECT_NUM))
	{
		__LogMgr()->Log("[#007]");
		CloseHandle(hFile);
		return FALSE;
	}
	//hFile = CreateFile( "CONFIG\\SERVER_INFO.TXT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#012]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.mWorldNumber = atoi(tempString01);
	if ((mSERVER_INFO.mWorldNumber < 1) || (mSERVER_INFO.mWorldNumber > 999))
	{
		__LogMgr()->Log("[#013]");
		CloseHandle(hFile);
		return FALSE;
	}
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#014]");
		CloseHandle(hFile);
		return FALSE;
	}
	strcpy(mSERVER_INFO.mUpperServer_1_IP, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#015]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.mUpperServer_1_Port = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#016]");
		CloseHandle(hFile);
		return FALSE;
	}
	strcpy(mSERVER_INFO.mUpperServer_2_IP, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#017]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.mUpperServer_2_Port = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#018]");
		CloseHandle(hFile);
		return FALSE;
	}
	strcpy(mSERVER_INFO.mUpperServer_3_IP, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#019]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.mUpperServer_3_Port = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#020]");
		CloseHandle(hFile);
		return FALSE;
	}
	strcpy(mSERVER_INFO.mUpperServer_4_IP, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#021]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.mUpperServer_4_Port = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#022]");
		CloseHandle(hFile);
		return FALSE;
	}
	strcpy(mSERVER_INFO.mUpperServer_5_IP, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.mUpperServer_5_Port = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_EXP = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_ITEM_DROP = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_ITEM_DROP_FM = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_KTAV = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#0231]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_BINEKEXP = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_PATEXP = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_EXPLOSS = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#025]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_PVPXP = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#025]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_MONSTER_DROP_MONEY = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#018]");
		CloseHandle(hFile);
		return FALSE;
	}
	strcpy(mSERVER_INFO.mGameLogIp, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#019]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.mGameLogPort = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#030]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_EARTH_CHEST_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#031]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_DIAMOND_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#032]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_FEATHER_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#033]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_SKILL_BOX_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#034]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_IMPROVE_STONE_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#035]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_8TH_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#036]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_FEATHER_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#037]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_DIAMOND_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#038]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_5_MOUNT_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#039]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_HEAVENLY_CHEST_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#040]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_ASIRLIK_ALTIN_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#041]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_BLACK_FEATHER_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#042]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_IKSIR_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#043]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_SKILL_BOX_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#044]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_TREASURE_MONSTER_BOX = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#056]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_10_MOUNT_BOX_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#045]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_15_MOUNT_BOX_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#046]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_8_BK_CRAFT_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#047]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.PK_IOS_KEY_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#048]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_2_SOCKET_RATE = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#049]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_3_SOCKET_RATE = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#050]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_4_SOCKET_RATE = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#051]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_5_SOCKET_RATE = atoi(tempString01);
	
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#052]");
		CloseHandle(hFile);
		return FALSE;
	}
	strcpy(mSERVER_INFO.mValet_Ip, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#053]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.mValet_Port = atoi(tempString01);

	if (!CloseHandle(hFile))
	{
		__LogMgr()->Log("[#055]");
		CloseHandle(hFile);
		return FALSE;
	}
	return TRUE;

}
BOOL ReadServerInfoUpdate(void)
{
	HANDLE hFile;
	char tempString01[100];

	hFile = CreateFile("CONFIG\\SERVER_INFO.TXT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		__LogMgr()->Log("[#001]");
		CloseHandle(hFile);
		return FALSE;
	}
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#002]");
		CloseHandle(hFile);
		return FALSE;
	}
	//strcpy(mSERVER_INFO.mServerName, tempString01);
	if (strcmp(mSERVER_INFO.mServerName, "") == 0)
	{
		__LogMgr()->Log("[#003]");
		CloseHandle(hFile);
		return FALSE;
	}
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#006]");
		CloseHandle(hFile);
		return FALSE;
	}
	//mSERVER_INFO.mServerMaxUserNum = atoi(tempString01);
	if ((mSERVER_INFO.mServerMaxUserNum < 1) || (mSERVER_INFO.mServerMaxUserNum > MAX_AVATAR_OBJECT_NUM))
	{
		__LogMgr()->Log("[#007]");
		CloseHandle(hFile);
		return FALSE;
	}
	//hFile = CreateFile( "CONFIG\\SERVER_INFO.TXT", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#012]");
		CloseHandle(hFile);
		return FALSE;
	}
	//mSERVER_INFO.mWorldNumber = atoi(tempString01);
	if ((mSERVER_INFO.mWorldNumber < 1) || (mSERVER_INFO.mWorldNumber > 999))
	{
		__LogMgr()->Log("[#013]");
		CloseHandle(hFile);
		return FALSE;
	}
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#014]");
		CloseHandle(hFile);
		return FALSE;
	}
	//strcpy(mSERVER_INFO.mUpperServer_1_IP, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#015]");
		CloseHandle(hFile);
		return FALSE;
	}
	//mSERVER_INFO.mUpperServer_1_Port = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#016]");
		CloseHandle(hFile);
		return FALSE;
	}
	//strcpy(mSERVER_INFO.mUpperServer_2_IP, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#017]");
		CloseHandle(hFile);
		return FALSE;
	}
	//mSERVER_INFO.mUpperServer_2_Port = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#018]");
		CloseHandle(hFile);
		return FALSE;
	}
	//strcpy(mSERVER_INFO.mUpperServer_3_IP, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#019]");
		CloseHandle(hFile);
		return FALSE;
	}
	//mSERVER_INFO.mUpperServer_3_Port = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#020]");
		CloseHandle(hFile);
		return FALSE;
	}
	//strcpy(mSERVER_INFO.mUpperServer_4_IP, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#021]");
		CloseHandle(hFile);
		return FALSE;
	}
	//mSERVER_INFO.mUpperServer_4_Port = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#022]");
		CloseHandle(hFile);
		return FALSE;
	}
	//strcpy(mSERVER_INFO.mUpperServer_5_IP, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	//mSERVER_INFO.mUpperServer_5_Port = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_EXP = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_ITEM_DROP = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_ITEM_DROP_FM = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_KTAV = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#0231]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_BINEKEXP = atoi(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_PATEXP = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#023]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_EXPLOSS = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#025]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_PVPXP = atof(tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#025]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_MONSTER_DROP_MONEY = atoi(tempString01);


	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#018]");
		CloseHandle(hFile);
		return FALSE;
	}
	//strcpy(mSERVER_INFO.mGameLogIp, tempString01);
	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#019]");
		CloseHandle(hFile);
		return FALSE;
	}
	//mSERVER_INFO.mGameLogPort = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		printf("[#030]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_EARTH_CHEST_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		printf("[#031]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_DIAMOND_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		printf("[#032]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_FEATHER_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		printf("[#033]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_SKILL_BOX_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		printf("[#034]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_IMPROVE_STONE_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		printf("[#035]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_8TH_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#036]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_FEATHER_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#037]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_DIAMOND_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#038]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_5_MOUNT_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#039]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_HEAVENLY_CHEST_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#040]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_ASIRLIK_ALTIN_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#041]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_BLACK_FEATHER_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#042]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_IKSIR_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#043]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_SKILL_BOX_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#044]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_TREASURE_MONSTER_BOX = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#056]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_10_MOUNT_BOX_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#045]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_15_MOUNT_BOX_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#046]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.OUTPOST_8_BK_CRAFT_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#047]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.PK_IOS_KEY_DROP = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#048]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_2_SOCKET_RATE = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#049]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_3_SOCKET_RATE = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#050]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_4_SOCKET_RATE = atoi(tempString01);

	if (!GetOneValueFromFile(hFile, &tempString01[0], 100))
	{
		__LogMgr()->Log("[#051]");
		CloseHandle(hFile);
		return FALSE;
	}
	mSERVER_INFO.WORLD_5_SOCKET_RATE = atoi(tempString01);

	if (!CloseHandle(hFile))
	{
		printf("[#024]");
		CloseHandle(hFile);
		return FALSE;
	}
	return TRUE;

}
BOOL GetOneValueFromFile(HANDLE hFile, char* tBuffer, int tBufferSize)
{
	int index01;
	DWORD nReadByte;
	BOOL tCheckSaveState;
	char tData;

	index01 = 0;
	tCheckSaveState = FALSE;
	while (TRUE)
	{
		if (!ReadFile(hFile, &tData, 1, &nReadByte, NULL))
		{
			return FALSE;
		}
		if (nReadByte != 1)
		{
			return FALSE;
		}
		if (!tCheckSaveState)
		{
			if (tData == '[')
			{
				tCheckSaveState = TRUE;
			}
		}
		else
		{
			if (tData == ']')
			{
				tBuffer[index01] = '\0';
				break;
			}
			else
			{
				if (index01 < (tBufferSize - 1))
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
DWORD WINAPI DetectCar(LPVOID lpParameter)
{
	while (TRUE)
	{
		mBaseTickCountForLogic = GetTickCount();
		if ((mBaseTickCountForLogic - mPostTickCountForLogic) > 500)
		{
			mPostTickCountForLogic = mBaseTickCountForLogic;
			//mCheckLogicFlag = TRUE;
			mGAME.Logic(0.5f);
		}
		Sleep(100);
	}
	return 0;
}
//BUG_TRAP_INIT
void BugTrapInit(void)
{
	BT_InstallSehFilter();
	BT_SetAppName("SailorSky2 Zone BugTrap");
	BT_SetReportFilePath("C:\\BugTrap");
	BT_SetFlags(BTF_DETAILEDMODE);
}