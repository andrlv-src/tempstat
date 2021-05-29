/*      temp_functions.c
 *      tempstat functions
 *
 *      written 2021 by Andrey Lvov
 */
#include <stdio.h>
#include "temp_functions.h"

void print_help()
{
        printf("Usage: tempstat [OPTION]... [FILE]...\n");
        printf("  -f\tfile for processing\n");
        printf("Examples:\n");
        printf("  tempstat -f file.csv -m 1\n");
}
