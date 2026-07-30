#include <stdio.h>
#include <entry.h>
#include <info.h>
#include <stdlib.h>

#define LOGO "logo.txt"

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

int main(void)
{

    char line[64];
    int entry_index = 0;
    FILE * fp = fopen(LOGO, "r");
    int logo_done = 0;
    int data_done = 0;

    while (logo_done && data_done)
    {
        if (!logo_done && (fgets(line,sizeof(line),fp) != NULL))
        {
            printf("%s", line);
        } else logo_done = 1;

        if (!data_done && (entries[entry_index].last != 1))
        {
            print_entry(entries[entry_index]);
        } else data_done = 1;
    }

    return 0;
}
