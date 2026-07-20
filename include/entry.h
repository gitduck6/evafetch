#ifndef ENTRY_H
#define ENTRY_H

#include <sys/sysinfo.h>

typedef struct
{
    char active;
    char *name;
    char* (*func_ptr)();
} entry;

extern struct sysinfo Systeminfo;
struct utsname Uname;
extern entry entries[];
extern int entry_count;

#endif
