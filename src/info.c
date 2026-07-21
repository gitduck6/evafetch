#include "entry.h"
#include <info.h>
#include <stdio.h>

char * get_hostname()
{
    int status = 0;

    if (Uname.sysname[0] == '\0')
        status = uname(&Uname);

    if (status == -1)
    {
        perror("uname");
        return NULL;
    }


    char * hostname = strdup(Uname.nodename);
    if (hostname == NULL)
    {
        perror("malloc");
    }
    return hostname;
}

char * get_kernel()
{
    int status = 0;

    if (Uname.sysname[0] == '\0')
        status = uname(&Uname);

    if (status == -1)
    {
        perror("uname");
        return NULL;
    }


    int sysname_len = strlen(Uname.sysname);
    int release_len = strlen(Uname.release);

    char * kernel = malloc(sysname_len + release_len + 2);

    strcpy(kernel, Uname.sysname);
    kernel[sysname_len] = ' ';
    strcpy(kernel + sysname_len + 1, Uname.release);

    return kernel;
}


char * get_ram()
{
    int status = 0;
    /*\
    * uptime is only 0 if sysinfo() hasnt been run yet
    * we do this in order to run sysinfo once even if multiple functions require its output
    * ill do something similar with uname
    \*/
    if (Systeminfo.uptime == 0)
        status = sysinfo(&Systeminfo);


    if (status != 0) {
        perror("sysinfo");
        return NULL;
    }

    char *msg = "%.2fG/%.2fG (%.0f%%)";

    float total = ((float)Systeminfo.totalram * Systeminfo.mem_unit)
    / (1024 * 1024 * 1024);

    float used = total - (((float)Systeminfo.freeram * Systeminfo.mem_unit)
    / (1024 * 1024 * 1024));

    int len = snprintf(NULL, 0, msg, used, total, (used/total) * 100);
    if (len < 0 )
    {
        perror("snprintf");
        return NULL;
    }

    char * ram_data = malloc(len + 1);
    if (ram_data == NULL)
    {
        perror("malloc");
        return NULL;
    }

    snprintf(ram_data,  len + 1, msg, used, total, (used/total) * 100);
    return ram_data;
}


char * get_uptime()
{
    int status = 0;

    if (Systeminfo.uptime == 0)
        status = sysinfo(&Systeminfo);


    if (status != 0)
    {
        perror("sysinfo");
        return NULL;
    }
    long raw_uptime = Systeminfo.uptime;
    long formatted_uptime[4];

    char * msg = "%dd %dh %dm %ds";
    formatted_uptime[0] = raw_uptime / (60*60*24);
    raw_uptime %= 60*60*24;
    formatted_uptime[1] = raw_uptime / (60*60);
    raw_uptime %= 60*60;
    formatted_uptime[2] = raw_uptime / 60;
    raw_uptime %= 60;
    formatted_uptime[3] = raw_uptime;


    int len = snprintf(NULL, 0, msg, formatted_uptime[0], formatted_uptime[1], formatted_uptime[2],formatted_uptime[3]);
    if (len < 0 )
    {
        perror("snprintf");
        return NULL;
    }

    char * uptime_string = malloc(len + 1);
    if (uptime_string == NULL)
    {
        perror("malloc");
        return NULL;
    }

    snprintf(uptime_string, len+1, msg, formatted_uptime[0], formatted_uptime[1], formatted_uptime[2],formatted_uptime[3]);
    return uptime_string;
}
