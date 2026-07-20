#ifndef INFO_H
#define INFO_H

#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <entry.h>

char * get_hostname();
char * get_kernel();
char * get_ram();

#endif
