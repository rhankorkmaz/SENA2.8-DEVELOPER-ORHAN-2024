
#include "TimeLog.h"


R_ProLog::R_ProLog(void)
{
	InitializeCriticalSection(&m_kCritical);
	//char buf[128];
	//char tmpTime[32];
	//char tmpDate[32];
	//_strtime( tmpTime );
	//_strdate( tmpDate );
	m_bShowPrint = true;
	//sprintf( buf, "日志文件创建时间: [%s %s]\r\n", tmpDate, tmpTime );
}

R_ProLog::~R_ProLog(void)
{
	//m_File.CloseFile();
	DeleteCriticalSection(&m_kCritical);
}

void R_ProLog::Log( const char *szText, ... )
{
#ifndef NO_PROGRAM_LOG

	if (m_bMultithreading)
	{
		EnterCriticalSection(&m_kCritical);
	}

	++m_dwLogCount;

	int iPos = 0;
	//iPos += sprintf( m_szBuffer + iPos,"[%5d]", m_dwLogCount );
	char tmpTime[32];
	_strtime(tmpTime);
	//iPos += sprintf( m_szBuffer + iPos, "[%s]", tmpTime );

	va_list args;
	va_start(args, szText);
	iPos += _vsnprintf(m_szBuffer + iPos, 1024 * 6 - 50, szText, args);
	m_szBuffer[iPos] = '\r';
	m_szBuffer[iPos + 1] = '\n';
	m_szBuffer[iPos + 2] = '\0';
	if (m_bShowPrint)
	{
		std::cout << m_szBuffer;
	}
#ifdef WIN32
	//printf( m_szBuffer );
#endif
//	m_File.WriteBuffer( m_szBuffer, iPos );
//	m_File.Flush();
	va_end(args);

	if (m_bMultithreading)
	{
		LeaveCriticalSection(&m_kCritical);
	}
#endif	
	return;
}

R_ProLog* __LogMgr()
{
	static R_ProLog s_kProgramLog;
	return &s_kProgramLog;
}

//void R_ProLog::GameLog(int tSort, char* tLogData, ...)
//{
//	char tempString01[10000];
//	char tempString02[10000];
//	time_t tCountSeconds;
//	struct tm* tPresentTime;
//	HANDLE hFile;
//	DWORD nWriteByte;
//
//	time(&tCountSeconds);
//	tPresentTime = localtime(&tCountSeconds);
//	if (tPresentTime == NULL)
//	{
//		return;
//	}
//	if (tSort == 1)
//	{
//		strcpy(tempString01, "C:\\ips");
//	}
//	else if (tSort == 2)
//	{
//		strcpy(tempString01, "LOG\\CHAT_LOG");
//	}
//	else if (tSort == 3)
//	{
//		strcpy(tempString01, "LOG\\GM_LOG");
//	}
//	else if (tSort == 4)
//	{
//		strcpy(tempString01, "LOG\\QUIT_LOG");
//	}
//	else if (tSort == 5)
//	{
//		strcpy(tempString01, "LOG\\ITEM_MALL_LOG");
//	}
//	//_itoa((tPresentTime->tm_year + 1900), tempString02, 10);
//	//strcat(tempString01, tempString02);
//	//strcat(tempString01, "-");
//	/*if (tPresentTime->tm_mon < 9)
//	{
//		tempString02[0] = '0';
//		tempString02[1] = tPresentTime->tm_mon + 1 + '0';
//		tempString02[2] = '\0';
//	}
//	else
//	{
//		_itoa((tPresentTime->tm_mon + 1), tempString02, 10);
//	}
//	strcat(tempString01, tempString02);
//	strcat(tempString01, "-");
//	if (tPresentTime->tm_mday < 10)
//	{
//		tempString02[0] = '0';
//		tempString02[1] = tPresentTime->tm_mday + '0';
//		tempString02[2] = '\0';
//	}
//	else
//	{
//		_itoa(tPresentTime->tm_mday, tempString02, 10);
//	}*/
//	strcat(tempString01, tempString02);
//	strcat(tempString01, ".TXT");
//	char m_szBuffer[1024 * 6];
//	int iPos = 0;
//	va_list args;
//	va_start(args, tLogData);
//	//iPos += sprintf(tempString02 + iPos, "[%d:%d:%d] ", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec);
//	//sprintf(tempString02, "[%d:%d:%d] %s\r\n", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData, args);
//	iPos += _vsnprintf(tempString02 + iPos, 1024 * 6 - 50, tLogData, args);
//	tempString02[iPos] = '\r';
//	tempString02[iPos + 1] = '\n';
//	tempString02[iPos + 2] = '\0';
//	hFile = CreateFile(tempString01, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//	if (hFile == INVALID_HANDLE_VALUE)
//	{
//		return;
//	}
//	if (SetFilePointer(hFile, 0, 0, FILE_END) == 0xFFFFFFFF)
//	{
//		CloseHandle(hFile);
//		return;
//	}
//	if (!WriteFile(hFile, tempString02, strlen(tempString02), &nWriteByte, NULL))
//	{
//		CloseHandle(hFile);
//		return;
//	}
//	if (nWriteByte != strlen(tempString02))
//	{
//		CloseHandle(hFile);
//		return;
//	}
//	if (!CloseHandle(hFile))
//	{
//		return;
//	}
//	va_end(args);
//}

void R_ProLog::GameLog(int tSort, char* tLogData, ...)
{
	char tempString01[10000];
	char tempString02[10000];
	time_t tCountSeconds;
	struct tm* tPresentTime;
	HANDLE hFile;
	DWORD nWriteByte;

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	if (tSort == 1)
	{
		strcpy(tempString01, "LOG\\GAMELOG_");
	}
	else if (tSort == 2)
	{
		strcpy(tempString01, "LOG\\CHAT_LOG_");
	}
	else if (tSort == 3)
	{
		strcpy(tempString01, "LOG\\GM_LOG_");
	}
	else if (tSort == 4)
	{
		strcpy(tempString01, "LOG\\QUIT_LOG_");
	}
	else if (tSort == 5)
	{
		strcpy(tempString01, "LOG\\ITEM_MALL_LOG_");
	}
	_itoa((tPresentTime->tm_year + 1900), tempString02, 10);
	strcat(tempString01, tempString02);
	strcat(tempString01, "-");
	if (tPresentTime->tm_mon < 9)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mon + 1 + '0';
		tempString02[2] = '\0';
	}
	else
	{
		_itoa((tPresentTime->tm_mon + 1), tempString02, 10);
	}
	strcat(tempString01, tempString02);
	strcat(tempString01, "-");
	if (tPresentTime->tm_mday < 10)
	{
		tempString02[0] = '0';
		tempString02[1] = tPresentTime->tm_mday + '0';
		tempString02[2] = '\0';
	}
	else
	{
		_itoa(tPresentTime->tm_mday, tempString02, 10);
	}
	strcat(tempString01, tempString02);
	strcat(tempString01, ".TXT");
	char m_szBuffer[1024 * 6];
	int iPos = 0;
	va_list args;
	va_start(args, tLogData);
	iPos += sprintf(tempString02 + iPos, "[%d:%d:%d] ", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec);
	//sprintf(tempString02, "[%d:%d:%d] %s\r\n", tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec, tLogData, args);
	iPos += _vsnprintf(tempString02 + iPos, 1024 * 6 - 50, tLogData, args);
	tempString02[iPos] = '\r';
	tempString02[iPos + 1] = '\n';
	tempString02[iPos + 2] = '\0';
	hFile = CreateFile(tempString01, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}
	if (SetFilePointer(hFile, 0, 0, FILE_END) == 0xFFFFFFFF)
	{
		CloseHandle(hFile);
		return;
	}
	if (!WriteFile(hFile, tempString02, strlen(tempString02), &nWriteByte, NULL))
	{
		CloseHandle(hFile);
		return;
	}
	if (nWriteByte != strlen(tempString02))
	{
		CloseHandle(hFile);
		return;
	}
	if (!CloseHandle(hFile))
	{
		return;
	}
	va_end(args);
}