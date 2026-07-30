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
    int done = 0;


    for (;fgets(line, sizeof(line), fp) != NULL;entry_index++)
    {
        if (entries[entry_index].last) done = 1;
        line[strcspn(line, "\n")] = '\0';

        printf("%s", line);
        if (!done) print_entry(entries[entry_index]);


        fputc('\n', stdout);

    }

    return 0;
}
