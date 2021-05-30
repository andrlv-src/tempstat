/*      temp_functions.c
 *      tempstat functions
 *
 *      Written 2021 by Andrey Lvov
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

static int current_month = 1;
static int current_day   = 0;
static int dt[4] = {0}; /* days, t sum, tmax, tmin */

int flread(FILE *fp, data_s *months)
{
        int dcnt = 0;     /* data count -  correct count of input items */
        int line = 0;     /* current line in file, for catch errors and log it*/
        int dtmp[6] = {0};/* array for keep temporary data: y,m,d,h,m,t */
        int lcnt = 0;     /* error lines counter */
        int erlines[LINES] = {0}; /* array for numbers of broken lines */
        char tmpl[LENGTH] = {0};  /* keep temporary line */
        _Bool loop = true;

/*              csv file format example
                YEAR;MONTH;DAY;HOUR;MINUTE;TEMPERATURE
                2021;01;01;23;03;-6
*/

        while (fgets(tmpl, LENGTH, fp)) {
                dcnt = sscanf(tmpl, DATA_FORMAT, &dtmp[0], &dtmp[1], &dtmp[2],\
                                                 &dtmp[3], &dtmp[4], &dtmp[5]);
                line++;

                printf("processing line: %d | line: %s", line, tmpl);

                /* line is broken */
                if (dcnt != 6) {
                        erlines[lcnt++] = line;
                        continue;
                }

                /* process data */
                parse_data(dtmp, months);


        }

        for (int i = 0; i < LINES; ++i) {
                if (erlines[i] != 0)
                        printf("\nDEBUG: error line number: %d\n", erlines[i]);
        }

        return 1;
}

void parse_data(int *data, data_s *months)
{
/*      data array format:

        data[0] - year
        data[1] - month
        data[2] - day
        data[3] - hour
        data[4] - minute
        data[5] - temperature
*/

        /* changing month */
        if (current_month != data[1]) {
                months[current_month].days = dt[0]; /* save amount of days */
                months[current_month].tmax = dt[2]; /* save tmax */
                months[current_month].tmin = dt[3]; /* save tmin */
                months[current_month].avr_month_temp = dt[1] / dt[0];

                current_month = data[1];
                /* reset temporary data */
                for (int i = 0; i < 4; ++i)
                        dt[i] = 0;
        }

        if (current_day != data[2]) dt[0]++;   /* new day */
        if (dt[2] < data[5]) dt[2] = data[5];  /* set new highest temp */
        if (dt[3] > data[5]) dt[3] = data[5];  /* set new lowest temp  */
        dt[1] += data[5];                      /* set temperature sum  */
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

