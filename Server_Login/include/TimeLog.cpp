
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

	if ( m_bMultithreading )
	{
		EnterCriticalSection(&m_kCritical);
	}

	++m_dwLogCount;

	int iPos = 0;
	//iPos += sprintf( m_szBuffer + iPos,"[%5d]", m_dwLogCount );
	char tmpTime[32];
	_strtime( tmpTime );
	//iPos += sprintf( m_szBuffer + iPos, "[%s]", tmpTime );

	va_list args;
	va_start( args, szText );
	iPos += _vsnprintf( m_szBuffer + iPos,1024*6 - 50, szText, args );
	m_szBuffer[iPos]	 = '\r';
	m_szBuffer[iPos+1] = '\n';
	m_szBuffer[iPos+2] = '\0';
	if ( m_bShowPrint )
	{
		std::cout<<m_szBuffer;
	}
#ifdef WIN32
	//printf( m_szBuffer );
#endif
//	m_File.WriteBuffer( m_szBuffer, iPos );
//	m_File.Flush();
	va_end( args );

	if ( m_bMultithreading )
	{
		LeaveCriticalSection(&m_kCritical);
	}
#endif	
}

R_ProLog* __LogMgr()
{
	static R_ProLog s_kProgramLog;
	return &s_kProgramLog;
}
