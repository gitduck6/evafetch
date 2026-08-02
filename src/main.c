#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <entry.h>
#include <info.h>

static inline void print_entry(entry current_entry)
{
    if (current_entry.name != NULL)
        printf("%s", current_entry.name);
    if ((current_entry.name != NULL) && (current_entry.func_ptr != NULL))
        printf(": ");

    if (current_entry.func_ptr != NULL)
    {
        char * value = current_entry.func_ptr();
        printf("%s", value);
        free(value);
    }
}

static inline void print_space(int n)
{
    for (int i = 0;i < n;i++)
        fputc(' ', stdout);
}

int main(int argc, char ** argv)
{
    char * logo_file =  "logos/linux.txt";

    int c;
    while ((c = getopt(argc, argv, "l:")) != -1)
    {
        switch (c)
        {
            case 'l':
                logo_file = optarg;
                break;
            default:
                fprintf(stderr, "%s -l [LOGO_PATH]", argv[0]);
                return 1;
                break;

        }
    }

    char logo_line[64];
    FILE * fp = fopen(logo_file, "r");
    if (fp == NULL)
    {
        perror("fopen");
        return 2;
    }

    int max_len = 0;

    while (fgets(logo_line, sizeof(logo_line), fp) != NULL)
    {
        int cur_len = strlen(logo_line);
        if (cur_len > max_len) max_len = cur_len;
    }
    rewind(fp);


    int entry_index = 0;
    int logo_done = 0;
    int data_done = 0;
    while (!(logo_done && data_done)) // go untill both are 1
    {
        int printed = 0;

        if (!logo_done && (fgets(logo_line,sizeof(logo_line),fp) != NULL))
        {
            logo_line[strcspn(logo_line, "\n")] = '\0';
            printed += printf("%s", logo_line);
        } else logo_done = 1;

        if (!data_done && (entries[entry_index].last != 1))
        {
            print_space(max_len-printed);
            print_entry(entries[entry_index]);
            entry_index++;
        } else data_done = 1;

        fputc('\n', stdout);
    }

    return 0;
}
