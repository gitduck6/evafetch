#include <stdio.h>
#include <entry.h>
#include <info.h>
#include <stdlib.h>


int main(void)
{
    entry_count = 2;


    for (int i = 0;i < entry_count;i++)
    {
        if (entries[i].active)
        {
            char * value = entries[i].func_ptr();
            printf("%s: %s\n", entries[i].name, value);
            free(value);
        }
    }

    return 0;
}
