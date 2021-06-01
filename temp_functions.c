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
        LINES = 100,
        LENGTH = 25
};

void dbinit(data_s *tdata)
{
        int i = 0;
        for (i = 0; i < NUMBER_OF_MONTHS; ++i) {
                tdata[i].year = 2021;
                tdata[i].month = i + 1;
                tdata[i].days = 0;
                tdata[i].tmax = 0;
                tdata[i].tmin = 0;
                tdata[i].avr_t = 0;
                tdata[i].minutes = 0;
                tdata[i].tsum = 0;
        }
/*
        switch (tdata[i].month) {
                case 1: tdata[i].month_name  "January"; break;
                case 2: tdata[i].month_name  "February"; break;
                case 3: tdata[i].month_name  "March"; break;
                case 4: tdata[i].month_name  "April"; break;
                case 5: tdata[i].month_name  "May"; break;
                case 6: tdata[i].month_name  "June"; break;
                case 7: tdata[i].month_name  "July"; break;
                case 8: tdata[i].month_name  "August"; break;
                case 9: tdata[i].month_name  "September"; break;
                case 10: tdata[i].month_name "October"; break;
                case 11: tdata[i].month_name "November"; break;
                case 12: tdata[i].month_name "December"; break;
                default: printf("ERROR: Wrong month number\n"); exit(1);
        }
*/
}

int read_data(FILE *fp, data_s *tdata)
{
        int dcnt = 0;            /* data count -  correct is 6 */
        int line = 0;            /* current processing line */
        int pstr[6] = {0};       /* array for parsed string: y,m,d,h,m,t */
        int lcnt = 0;            /* error lines counter */
        int errors[LINES] = {0}; /* array for numbers of lines with errors */
        char tmpl[LENGTH] = {0}; /* keep temporary line */

        /* read line from file fp */
        while (fgets(tmpl, LENGTH, fp)) {
                dcnt = sscanf(tmpl, DATA_FORMAT,\
                        &pstr[0], &pstr[1], &pstr[2],\
                        &pstr[3], &pstr[4], &pstr[5]);
                line++;
                //printf("processing line: %d | line: %s", line, tmpl);

                /* if line is broken, save it's number to errors array */
                if (dcnt != 6) {
                        errors[lcnt++] = line;
                        continue;
                }

                /* process parsed line contained in pstr array */
                process_data(pstr, tdata); /* TODO maybe rename this fuction? */
        }
        /* TODO delete DEBUG info and reazise getting of errors */
        for (int i = 0; i < LINES; ++i) {
                if (errors[i] != 0)
                        printf("\nDEBUG: error line number: %d\n", errors[i]);
        }

        return 1;
}

void process_data(int *pstr, data_s *tdata)
{
/*      pstr array format:

        pstr[0] - year
        pstr[1] - month
        pstr[2] - day
        pstr[3] - hour
        pstr[4] - minute
        pstr[5] - temperature
*/
        int i = 0;
        data_s *dp = NULL; /* pointer to particular month */

        dp = get_month(tdata, pstr[1]); /* get particular month struct */
        dp->minutes++;
        dp->tsum += pstr[5];
 
        for (i = 0; i < NUMBER_OF_MONTHS; ++i) {
                tdata[i].avr_t = tdata[i].tsum / tdata[i].minutes;
        }
}

data_s *get_month(data_s *tdata, int mn)
{
        data_s *mnth = NULL;
        int i = 0;
        for (i = 0; i < NUMBER_OF_MONTHS; ++i) {
                if (tdata[i].month == mn) {
                        mnth = &tdata[i];
                }
        }
        /* returns pointer to structure of selected month */
        return mnth;
}

void print_data(data_s *tdata, _Bool mopt)
{
/*
          typedef struct {
                int year;
                int month;
                int days;
                int tmax;
                int tmin;
                int avr_t;
          }
*/
        printf("Test data printing\n");
        for (int i = 0; i < NUMBER_OF_MONTHS; ++i) {
                printf("Month %d |minutes %d |tmax %d |tmin %d |temp sum %d |avr temp %d\n",\
                tdata[i].month, tdata[i].minutes, tdata[i].tmax, tdata[i].tmin, tdata[i].tsum, tdata[i].tsum / tdata[i].minutes);

        }
        printf("\nErrors found: %d, lines %d\n", 1, 1);
}

/* check for arguments, if args == 1 this means what did't set any argiments */
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

void print_error()
{
        printf("ERROR: Wrong argument(s).\n");
        printf("Try tempstat -h for help.\n");
}
