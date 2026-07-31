#include <stdio.h>
#include <entry.h>
#include <info.h>
#include <stdlib.h>

#define LOGO "logos/linux.txt"

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

int main(void)
{

    char logo_line[64];
    int entry_index = 0;
    FILE * fp = fopen(LOGO, "r");
    int logo_done = 0;
    int data_done = 0;

    int max_len = 0;

    while (fgets(logo_line, sizeof(logo_line), fp) != NULL)
    {
        int cur_len = strlen(logo_line);
        if (cur_len > max_len) max_len = cur_len;
    }
    rewind(fp);


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
