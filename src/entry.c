#include <entry.h>
#include <info.h>

struct sysinfo Systeminfo = {0};
struct utsname Uname = {0};
entry entries[] =
{
    {.last = 0, .name = NULL, .func_ptr = &get_userathost},
    {.last = 0, .name = "-------------", .func_ptr = NULL},
    {.last = 0, .name = "OS", .func_ptr = &get_prettyname},
    {.last = 0, .name = "Hostname", .func_ptr = &get_hostname},
    {.last = 0, .name = "Kernel", .func_ptr = &get_kernel},
    {.last = 0, .name = "RAM", .func_ptr = &get_ram},
    {.last = 0, .name = "Uptime", .func_ptr = &get_uptime},

    {.last = 1, .name = NULL, .func_ptr = NULL}
};
