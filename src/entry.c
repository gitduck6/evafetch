#include <entry.h>
#include <info.h>

int entry_count;
entry entries[] =
{
    {.active = 1, .name = "Hostname", .func_ptr = &get_hostname},
    {.active = 1, .name = "Kernel", .func_ptr = &get_kernel},
    {.active = 1, .name = "RAM", .func_ptr = &get_ram},

    {.active = 0, .name = NULL, .func_ptr = NULL},
};
