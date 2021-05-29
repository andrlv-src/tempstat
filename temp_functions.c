/*      temp_functions.c
 *      tempstat functions
 *
 *      written 2021 by Andrey Lvov
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "temp_functions.h"

#define DATA_FORMAT "%4d;%2d;%2d;%2d;%2d;%d"

enum {
        LINES = 1000,
        LENGTH = 25
};

int parse_data(FILE *fp, data_s *months)
{
        int datacnt = 0; /* data count -  correct count of input items */
        int line = 0;   /* current line in file, for catch errors and log it*/
        int y = 0;      /* year         */
        int m = 0;      /* month        */
        int d = 0;      /* day          */
        int h = 0;      /* hour         */
        int mn = 0;     /* minute       */
        int t = 0;      /* temperature  */
        int lcnt = 0;   /* error lines counter */
        int erlines[LINES] = {0}; /* numbers of broken lines */
        char tmpl[LENGTH] = {0};  /* keep temporary line */
        _Bool loop = true;

        /*      csv file format example
                YEAR;MONTH;DAY;HOUR;MINUTE;TEMPERATURE
                2021;01;01;23;03;-6
         */

        while (fgets(tmpl, LENGTH, fp)) {
                datacnt = sscanf(tmpl, DATA_FORMAT, &y, &m, &d, &h, &mn, &t);
                line++;

                printf("processing line: %d | line: %s", line, tmpl);

                /* line is broken */
                if (datacnt != 6) {
                        erlines[lcnt++] = line;
                        continue;
                }


        }

        for (int i = 0; i < LINES; ++i) {
                if (erlines[i] != 0)
                        printf("\nDEBUG: error line number: %d\n", erlines[i]);
        }

        return 1;
}

void argcheck(int args)
{
        if (args == 1) {
                printf("ERROR: using without arguments.\n");
                printf("Try tempstat -h for help.\n");
                exit(1);
        }
}

void check_file_len(int max_flen, int flen)
{
        if (max_flen < flen) {
                printf("ERROR: file name is over\
                                100 symbols.\n");
                exit(1);
        }
}

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
        printf("  -m\tDisplay particular month by using numbers from 1 to 12\n");
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


