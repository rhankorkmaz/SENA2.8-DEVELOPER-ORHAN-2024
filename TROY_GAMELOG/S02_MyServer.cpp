//-------------------------------------------------------------------------------------------------
//HEADER
//-------------------------------------------------------------------------------------------------
#include "H01_MainApplication.h"
//-------------------------------------------------------------------------------------------------


using namespace std;

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_SERVER
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyServer mSERVER;
//CREATE
MyServer::MyServer(void)
{
}
//INIT
BOOL MyServer::Init(int* tResult)
{
	srand((unsigned int)time(NULL));
	ZeroMemory(&mWsaData, sizeof(WSADATA));
	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != 0)
	{
		*tResult = 2;
		return FALSE;
	}
	mSocket = socket(PF_INET, SOCK_DGRAM, 0);
	if (mSocket == INVALID_SOCKET)
	{
		*tResult = 3;
		return FALSE;
	}
	ZeroMemory(&mAddress, sizeof(mAddress));
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	mAddress.sin_port = htons(mSERVER_INFO.mServerPort);
	if (bind(mSocket, (LPSOCKADDR)&mAddress, sizeof(mAddress)) == SOCKET_ERROR)
	{
		*tResult = 4;
		return FALSE;
	}
	if (WSAAsyncSelect(mSocket, hMainWindow, WM_NETWORK_MESSAGE_1, FD_READ) == SOCKET_ERROR)
	{
		*tResult = 5;
		return FALSE;
	}
	printf("Logger Açýldý\n");
	return TRUE;
}
//FREE
void MyServer::Free(void)
{
	closesocket(mSocket);
	WSACleanup();
}
//PROCESS_FOR_NETWORK
void MyServer::PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm)
{

	SOCKADDR_IN	tAddress;
	int tAddressLength = 0;
	short tTotalQuerySize = 0;
	short tTotalPacketSize = 0;
	int tRecvSizeFromUser = -1;
	char tRecvData[10000] = { 0, };
	int Map;
	int LogSort;

	ZeroMemory(tRecvData, 10000);
	switch (WSAGETSELECTEVENT(lPrm))
	{
	case FD_READ:
		tAddressLength = sizeof(tAddress);
		tRecvSizeFromUser = recvfrom(mSocket, &tRecvData[0], 10000, 0, (LPSOCKADDR)&tAddress, &tAddressLength);
		if (tRecvSizeFromUser < 2)
		{
			return;
		}
		tRecvData[9999] = '\0';
		CopyMemory(&LogSort, &tRecvData[2], 4);
		CopyMemory(&Map, &tRecvData[6], 4);
		if (LogSort == 400)
		{
			WRITE_FOR_USE_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 401)
		{
			WRITE_FOR_IMPROVE_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 402)
		{
			WRITE_FOR_ADD_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 403)
		{
			WRITE_FOR_EXCHANGE_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 404)
		{
			WRITE_FOR_MAKE_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 405)
		{
			WRITE_FOR_SHOP_BUY_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 406)
		{
			WRITE_FOR_COSTUME_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 407)
		{
			WRITE_FOR_CRAFT_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 408)
		{
			WRITE_FOR_DAILY_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 409)
		{
			WRITE_FOR_PET_COMBINE_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 410)
		{
			WRITE_FOR_OPEN_HOLE_SOKET_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 411)
		{
			WRITE_FOR_DELETE_SOKET_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 412)
		{
			WRITE_FOR_RANK_REWARDS_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 413)
		{
			WRITE_FOR_BUY_CAPSULE_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 414)
		{
			WRITE_FOR_BUY_VALET_SHOP_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 415)
		{
			WRITE_FOR_BUY_VALET_SHOP_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 416)
		{
			WRITE_FOR_FISHING_ITEM_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 417)
		{
			WRITE_FOR_QUIT_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 418)
		{
			WRITE_FOR_KILL_OTHER_TRIBE(Map, &tRecvData[10]);
		}
		else if (LogSort == 419 || LogSort == 420)
		{
			WRITE_FOR_TRADE_LOG(Map, &tRecvData[10]);
		}
		else if (LogSort == 421)
		{
			WRITE_FOR_BAN(Map, &tRecvData[10]);
		}
		else if (LogSort == 424)
		{
			WRITE_SKILL_PLUSS(Map, &tRecvData[10]);
		}
		else if (LogSort == 425)
		{
			WRITE_BUY_CASH_ITEM(Map, &tRecvData[10]);
		}
		else if (LogSort == 426)
		{
			WRITE_BUY_GET_ITEM(Map, &tRecvData[10]);
		}
		else if (LogSort == 427)
		{
			WRITE_BUY_STORE_ITEM(Map, &tRecvData[10]);
		}
		else if (LogSort == 428)
		{
			WRITE_BUY_SAVE_ITEM(Map, &tRecvData[10]);
		}

		return;
	}
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_USE_ITEM_LOG(int Map, char* tLogData)
{
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	setlocale(LC_ALL, "Turkish");
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/USEITEM", Map);
	_mkdir(tempString05);
	
	sprintf(tempString01, "LOG\\%03d\\USEITEM\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {

		
		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
void MyServer::WRITE_FOR_IMPROVE_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/IMPROVEITEM", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\IMPROVEITEM\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_ADD_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/ADDITEM", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\ADDITEM\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_EXCHANGE_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/EXCHANGEITEM", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\EXCHANGEITEM\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_MAKE_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/MAKEITEM", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\MAKEITEM\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_SHOP_BUY_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/BUY_SHOP", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\BUY_SHOP\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_COSTUME_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/COSTUME", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\COSTUME\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_CRAFT_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/DOKUM", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\DOKUM\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
void MyServer::WRITE_FOR_DAILY_ITEM_LOG(int Map, char* tLogData)
{
	// Set the locale to Germany
	setlocale(LC_ALL, "Germany");

	// Declare variables for time and file manipulation
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	struct tm* tPresentTime;
	char tempString01[64];
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];

	// Initialize memory
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);

	// Get the current time
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);

	// Check if getting the local time was successful
	if (tPresentTime == NULL)
	{
		return;
	}

	// Create folders if they don't exist
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/DAILY", Map);
	_mkdir(tempString05);

	// Construct the log file path and log entry
	sprintf(tempString01, "LOG\\%03d\\DAILY\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	// Open the file in append mode
	if (!(w_fp = fopen(tempString01, "a+")))
	{
		return;
	}

	// Write the log entry to the file
	fputs(tempString02, w_fp);

	// Close the file
	fclose(w_fp);
}

//WRITE_FOR_LOG
void MyServer::WRITE_FOR_PET_COMBINE_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/MAKEPET", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\MAKEPET\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_OPEN_HOLE_SOKET_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/OPENSOKET", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\OPENSOKET\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_DELETE_SOKET_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/DELLSOKET", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\DELLSOKET\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_RANK_REWARDS_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/RANKPRIZE", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\RANKPRIZE\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_BUY_CAPSULE_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/CAPSUL", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\CAPSUL\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_BUY_VALET_SHOP_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);

	if (tPresentTime == NULL)
	{
		return;
	}

	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/VALET", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\VALET\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_FISHING_ITEM_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Bucharest");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/FISHING", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\FISHING\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_KILL_OTHER_TRIBE(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/KILL", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\KILL\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_QUIT_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Bucharest");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/QUIT", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\QUIT\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_TRADE_LOG(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/TRADE", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\TRADE\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_FOR_BAN(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/BAN", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\BAN\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_SKILL_PLUSS(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/StatPlus", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\StatPlus\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_BUY_CASH_ITEM(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/CashItem", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\CashItem\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_BUY_GET_ITEM(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/GetItem", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\GetItem\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_BUY_STORE_ITEM(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/StoreItem", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\StoreItem\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}
//WRITE_FOR_LOG
void MyServer::WRITE_BUY_SAVE_ITEM(int Map, char* tLogData)
{
	setlocale(LC_ALL, "Turkish");
	FILE* w_fp = NULL;
	time_t tCountSeconds;
	char tempString01[64];
	struct tm* tPresentTime;
	char tempString02[10000];
	char tempString03[9];
	char tempString04[9];
	char tempString05[9];
	ZeroMemory(tempString01, 64);
	ZeroMemory(tempString02, 10000);
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	//Klasör Oluþturma
	sprintf(tempString03, "./LOG");
	_mkdir(tempString03);
	sprintf(tempString04, "./LOG/%03d", Map);
	_mkdir(tempString04);
	sprintf(tempString05, "./LOG/%03d/SaveItem", Map);
	_mkdir(tempString05);

	sprintf(tempString01, "LOG\\%03d\\SaveItem\\gamelog_%04d-%02d-%02d.log", Map, tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	sprintf(tempString02, "[%02d:%02d:%02d] %s\r", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData);

	if (!(w_fp = fopen(tempString01, "a+"))) {


		return;
	}

	fputs(tempString02, w_fp);
	fclose(w_fp);
}