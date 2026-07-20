#include <info.h>
#include <stdio.h>

char * get_hostname()
{
    struct utsname name;
    if (uname(&name) == -1)
    {
        perror("uname");
        return NULL;
    }


    char * hostname = strdup(name.nodename);
    if (hostname == NULL)
    {
        perror("malloc");
    }
    return hostname;
}

char * get_kernel()
{
    struct utsname name;
    if (uname(&name) == -1)
    {
        perror("uname");
        return NULL;
    }


    int sysname_len = strlen(name.sysname);
    int release_len = strlen(name.release);

    char * kernel = malloc(sysname_len + release_len + 2);

    strcpy(kernel, name.sysname);
    kernel[sysname_len] = ' ';
    strcpy(kernel + sysname_len + 1, name.release);

    return kernel;
}


char * get_ram()
{
    struct sysinfo info;
    sysinfo(&info);
    char *msg = "%.2fG/%.2fG (%.0d%%)";

    float total = (float)info.totalram / (1024 * 1024 * 1024);
    float used = total - ((float)info.freeram / (1024 * 1024 * 1024));

    int len = snprintf(NULL, 0, msg, used, total, (used/total) * 100);

    char * ram_data = malloc(len + 1);
    if (ram_data == NULL)
    {
        perror("malloc");
        return NULL;
    }

    snprintf(ram_data,  len + 1, msg, used, total, (used/total) * 100);
    return ram_data;
}
