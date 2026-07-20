#include <stdio.h>
#include <entry.h>
#include <info.h>
#include <stdlib.h>

int main(void)
{

    for (int i = 0;entries[i].name != NULL;i++)
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
