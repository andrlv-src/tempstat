/*      temp_functions.c
 *      tempstat functions
 *
 *      written 2021 by Andrey Lvov
 */
#include <stdio.h>
#include "temp_functions.h"

void print_help()
{
/* 
 *  options list
 *
 *  -f=filename.csv
 *  -h help
 *  -m=month number
 *  -v version
 *  -y=year
 *  -D delimiter . , ; : "
 *  -M default month
 *
 */
        printf("Usage: tempstat -f [FILE]...[OPTIONS]\n");
        // printf("  -D\tset specific argument for csv delimeter like , . " : ;\n");
        printf("  -f\t[FILE] for processing in csv format\n");
        printf("  -h\tShow this message\n");
        printf("  -v\tShow version info\n");
        printf("\n[OPTIONS]\n");
        printf("  -m\tDisplay particular month by using nubmers from 1 to 12\n");
        // you can choose delimeter by -D option
        printf("\nExamples:\n");
        printf("  tempstat -f file.csv -m 1\n");
}

void print_version()
{
        printf("tempstat version %s\n", VERSION);
        printf("  Copyright (C) 2021 Andrey Lvov\n");
        // printf("This is free software: you are free to change and redistribute it.\n");
        printf("  There is NO WARRANTY, to the extent permitted by law.\n");

}

