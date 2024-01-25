/****************************************************************************

   CTSD : Common Transaction Service

   CopyRight(C) 2003 Sean Kim All Rights reserved.
   Author : Sean Kim (sean@0x31.com)

   $Id: cts_util.cpp,v 1.6 2007/08/26 17:05:03 sean Exp $

   Redistribution and use in source and binary forms, with or with out
   modification, are not permitted without author's permission.

 ****************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "log.h"
#include "util.h"
#include "raslib.h"
#include "global.h"
#include "cts_util.h"

#ifdef __RELEASE__
#define PID_FILE_PATH PROGPATH "/var/" SVR_NAME ".pid"
#else 
#define PID_FILE_PATH SVR_NAME ".pid"
#endif

using namespace std;
using namespace SDSocket;

struct gjrand g;

void  spin_wait(unsigned int dfs_sec, unsigned int dfs_usec)
{
	struct timeval tv = { dfs_sec, dfs_usec };

	::select(0, NULL, NULL, NULL, &tv);
}

int create_pid_file(void)
{
	FILE *pid_file_ptr = NULL;

#ifdef __DEBUG_UTIL__
	DEBUG1("create_pid_file::PID_FILE_PATH = %s\n", PID_FILE_PATH);
#endif
	pid_file_ptr = ::fopen(PID_FILE_PATH, "w+");
	if(!pid_file_ptr) {
		return -1;
	}

	::fprintf(pid_file_ptr, "%d", ::getpid());
	::fclose(pid_file_ptr);
	return 1;
}

int unlink_pid_file(void)
{
#ifdef __DEBUG_UTIL__
	DEBUG2("create_pid_file::PID_FILE_PATH = %s(%d)\n", PID_FILE_PATH, ::unlink(PID_FILE_PATH));
	return 1;
#else 
	return ::unlink(PID_FILE_PATH);
#endif
}

pid_t get_pid_file(void)
{
	int pid = -1;
	ifstream in(PID_FILE_PATH);
	char line_buffer_str[MAX_SIZE_OF_LINE_BUFFER];

	if(!in.is_open()) {
		return -1;
	}

	::memset(line_buffer_str, 0, MAX_SIZE_OF_LINE_BUFFER);
	in.getline(line_buffer_str, MAX_SIZE_OF_LINE_BUFFER);
	in.close();

	pid = (int)::atoi(line_buffer_str);
	if((pid < 0) && (pid > (2^32))) {
		return -2;
	}

#ifdef __DEBUG_UTIL__
	DEBUG1("get_pid_file::pid = %d\n", pid);
#endif
	return (pid_t)pid;
}

void rand_mir_init(void)
{
	gjrand_init(&g, time(NULL));
}

unsigned int rand_mir(void)
{
#if 0
	unsigned int r_rand = 0;
	r_rand = gjrand_rand(&g);
#endif
	return gjrand_rand(&g);
}
