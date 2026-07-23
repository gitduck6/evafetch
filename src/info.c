#include <entry.h>
#include <info.h>

char * get_prettyname()
{
    // Basically reads PRETTY_NAME from /etc/os-release
    // might add something with uname as fallback
    char line[512];
    char needle[] = "PRETTY_NAME";

    FILE * fp = fopen("/etc/os-release","rb");
    if (fp != NULL)
    {
        while (fgets(line, sizeof(line), fp))
        {
            char * pos = strstr(line,needle);
            if (pos != NULL)
            {
                pos += strlen(needle);
                while (*++pos != '"')
                {
                    if (*pos == '\0') return NULL;
                }
                int len;
                for (len = 1;(pos[len] != '"') && (pos[len] != '\0');len++ );

                char * buffer = malloc(len);
                if (buffer == NULL)
                {
                    perror("malloc");
                    return NULL;
                }
                memcpy(buffer,pos,len);

                return buffer;
            }

        }
    }

    return NULL;
}

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
    // every index is a different unit
    // for example [0] is days, [1] is hours and so on
    // i made it this way for easier iteration

    char * msg = "%ldd, %ldh, %ldm, %lds";
    long days = raw_uptime / (60*60*24);
    raw_uptime %= 60*60*24;
    long hours = raw_uptime / (60*60);
    raw_uptime %= 60*60;
    long minutes = raw_uptime / 60;
    raw_uptime %= 60;
    long seconds = raw_uptime;

    int len = snprintf(NULL, 0, msg, days, hours, minutes, seconds);
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

    int pos = 0;

    if (days)
        pos += snprintf(uptime_string + pos, len+1-pos,"%ld%c, ", days, 'd');
    if (hours)
        pos += snprintf(uptime_string + pos, len+1-pos,"%ld%c, ", hours, 'h');
    if (minutes)
        pos += snprintf(uptime_string + pos, len+1-pos,"%ld%c, ", minutes, 'm');
    if (seconds)
        pos += snprintf(uptime_string + pos, len+1-pos,"%ld%c, ", seconds, 's');
    uptime_string[pos - 2] = '\0';

    return uptime_string;
}
