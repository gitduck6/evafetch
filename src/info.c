#include <info.h>

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
