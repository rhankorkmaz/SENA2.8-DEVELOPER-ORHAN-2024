/****************************************************************************

   CTSD : Common Transaction Service

   CopyRight(C) 2003 Sean Kim All Rights reserved.
   Author : Sean Kim (sean@0x31.com)

   $Id: cts_mysql.h,v 1.3 2007/11/08 05:47:02 wglee Exp $

   Redistribution and use in source and binary forms, with or with out
   modification, are not permitted without author's permission.

 ****************************************************************************/

#ifndef __MYSQL_H__
#define	__MYSQL_H__

#include <iostream>
#include <string>
#include <stdlib.h>

#include "mysql.h"

using namespace std;
class CMySQL
{
public:
	enum CFLAG { CLEAR = 1, NOT_CLEAR };
    CMySQL(void);
    CMySQL(bool auto_commit);
    ~CMySQL();
	void unset_db_conn_info(void);
	int set_db_conn_info(const char *hostname_str_const_ptr, int port_num, const char *db_name_str_const_ptr,
	                    const char *acct_str_const_ptr, const char *passwd_str_const_ptr);
	int set_db_conn_info(const char *hostname_str_const_ptr, const char *hostname2_str_const_ptr, int port_num, const char *db_name_str_const_ptr,
			const char *acct_str_const_ptr, const char *passwd_str_const_ptr);
	MYSQL *connect(const char *hostname_str_const_ptr, int port_num, const char *db_name_str_const_ptr,
			const char *acct_str_const_ptr, const char *passwd_str_const_ptr);
	MYSQL *connect(string hostname_str_obj, int port_num, string db_name_str_obj,
	                string db_acct_str_obj,  string db_passwd_str_obj);
	MYSQL *connect(void);
	void disconnect(void);
	int get_result(CFLAG flag);
	MYSQL *GetMYSQL(void);
	MYSQL_RES *get_res(void);
    my_ulonglong get_affected_rows(void);
	int do_ping();
    int get_num_rows(void);
	int get_num_fields(void);
	int get_result_code(void) { return m_result_code; }
	char *get_value(int tuple, int field);
	void clear_res(void);
	int exec_query(string &strQuery);
	int exec_query(char *pszQuery);
	int exec_query(char *pszQuery, CFLAG flag);
	unsigned long escape_string(char *to, const char *from, size_t length);
	string &get_error_msg(void);
	int IsConnected(void);
	int Reconnect(void);

private:
	bool initialized;
    unsigned int m_port_num;
	char *m_hostname_str_ptr[2];
	char *m_dbname_str_ptr;
	char *m_acct_str_ptr;
	char *m_passwd_str_ptr;
	int m_result_code;
	bool m_auto_commit;

	MYSQL mMYSQL;
	MYSQL *m_MYSQL;
    MYSQL_RES *m_result_ptr;
	string m_errmsg_str_obj;
};

#endif	/* _MYSQL_H */