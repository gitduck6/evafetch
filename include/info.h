#ifndef INFO_H
#define INFO_H

#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <entry.h>

char * get_prettyname();
char * get_hostname();
char * get_kernel();
char * get_ram();
char * get_uptime();

#endif
