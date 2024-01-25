#include "Shengming.h"
/*#include "TimeLog.h"*/
const int vKB = 1024;
char m_szBuffer[vKB];

void Log_Pr(const TCHAR* msg, ...)
{
	int iPos = 0;
	char tmpTime[32];
	char tmpDate[32];
	_strtime( tmpTime );
	_strdate( tmpDate );
	iPos += sprintf( m_szBuffer + iPos, "[%s %s]", tmpDate, tmpTime  );

	va_list args;
	va_start( args, msg);
	iPos += _vsnprintf( m_szBuffer + iPos,vKB*6 - 50, msg, args );
	m_szBuffer[iPos]	 = '\r';
	m_szBuffer[iPos+1] = '\n';
	m_szBuffer[iPos+2] = '\0';
	va_end( args );
	printf(m_szBuffer);
}