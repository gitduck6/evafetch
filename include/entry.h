#ifndef ENTRY_H
#define ENTRY_H

typedef struct
{
    char active;
    char *name;
    char* (*func_ptr)();
} entry;


extern entry entries[];
extern int entry_count;

#endif
