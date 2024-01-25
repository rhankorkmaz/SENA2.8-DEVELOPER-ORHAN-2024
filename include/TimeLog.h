#pragma once
#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
using namespace std;
class R_ProLog
{
public:
	R_ProLog(void);
	~R_ProLog(void);

	void Log( const char *szText, ... );	
	void GameLog(int tSort, char* tLogData, ...);

	__inline void MultithreadingOn()
	{
		m_bMultithreading = true;
	}

	__inline void MultithreadingOff()
	{
		m_bMultithreading = false;
	}


	__inline void ShowPrintOn()
	{
		m_bShowPrint = true;
	}

	__inline void ShowPrintOff()
	{
		m_bShowPrint = false;
	}


protected:
	CRITICAL_SECTION m_kCritical;
	DWORD m_dwLogCount;
	/*R_File m_File;*/
	bool m_bShowPrint;
	bool m_bMultithreading;
	char m_szBuffer[1024*6];

private:
	R_ProLog( const R_ProLog &object );
	R_ProLog &operator= ( const R_ProLog &object );
};
R_ProLog* __LogMgr();