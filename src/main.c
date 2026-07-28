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
            if (entries[i].name != NULL)
                printf("%s", entries[i].name);
            if ((entries[i].name != NULL) && (entries[i].func_ptr != NULL))
                printf(": ");

            if (entries[i].func_ptr != NULL)
            {
                char * value = entries[i].func_ptr();
                printf("%s", value);
                free(value);
            }

            fputc('\n', stdout);

        }
    }

    return 0;
}
