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



    for (int i = 0;entries[i].last == 0;i++)
    {
        print_entry(entries[i]);

        fputc('\n', stdout);

    }

    return 0;
}
