/****************************************************************************

   CTSD : Common Transaction Service

   CopyRight(C) 2003 Sean Kim All Rights reserved.
   Author : Sean Kim (sean@0x31.com)

   $Id: cts_util.h,v 1.2 2007/08/26 17:05:03 sean Exp $

   Redistribution and use in source and binary forms, with or with out
   modification, are not permitted without author's permission.

 ****************************************************************************/

#ifndef __CTS_UTIL_H__
#define __CTS_UTIL_H__

#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include "gjrand.h"

extern struct gjrand g;
extern void  spin_wait(unsigned int dfs_sec, unsigned int dfs_usec);
extern int create_pid_file(void);
extern int unlink_pid_file(void);
extern pid_t get_pid_file(void);
extern void rand_mir_init(void);
extern unsigned int rand_mir(void);

#endif
