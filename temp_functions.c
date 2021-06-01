/*      temp_functions.c
 *      tempstat functions
 *
 *      Written 2021 by Andrey Lvov
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
                //tdata[i].year = 2021;
                tdata[i].month = i + 1;
                //tdata[i].days = 0;
                tdata[i].t_is_set = false;
                tdata[i].tmax = 0;
                tdata[i].tmin = 0;
                tdata[i].avg_t = 0;
                tdata[i].minutes = 0;
                tdata[i].tsum = 0;

                switch (tdata[i].month) {
                case 1: strcpy(tdata[i].month_name, "January"); break;
                case 2: strcpy(tdata[i].month_name, "February"); break;
                case 3: strcpy(tdata[i].month_name, "March"); break;
                case 4: strcpy(tdata[i].month_name, "April"); break;
                case 5: strcpy(tdata[i].month_name, "May"); break;
                case 6: strcpy(tdata[i].month_name, "June"); break;
                case 7: strcpy(tdata[i].month_name, "July"); break;
                case 8: strcpy(tdata[i].month_name, "August"); break;
                case 9: strcpy(tdata[i].month_name, "September"); break;
                case 10: strcpy(tdata[i].month_name, "October"); break;
                case 11: strcpy(tdata[i].month_name, "November"); break;
                case 12: strcpy(tdata[i].month_name, "December"); break;
                default: printf("ERROR: Wrong month number\n"); exit(1);
                }
        }
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

                /* if line is broken, save it's number to errors array */
                if (dcnt != 6) {
                        errors[lcnt++] = line;
                        continue;
                }

                /* process parsed line, contained in pstr array */
                process_data(pstr, tdata);
        }
 
        /* calculate average temperature of each month and save it in
           corresponding structure */
        for (int i = 0; i < NUMBER_OF_MONTHS; ++i) {
                tdata[i].avg_t = tdata[i].tsum / tdata[i].minutes;
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
        data_s *dp = NULL;

        /* get particular month struct */
        dp = get_month(tdata, pstr[1]);

        /* chack for first temperature entry and save to both, min and max */
        if (!dp->t_is_set) {
                dp->t_is_set = true;
                dp->tmax = pstr[5];
                dp->tmin = pstr[5];
        }

        dp->minutes++;
        dp->tsum += pstr[5];
 
        if (dp->tmax <= pstr[5])
                dp->tmax = pstr[5];
        if (dp->tmin >= pstr[5])
                dp->tmin = pstr[5];
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

void get_year_data(data_s *tdata, int *year)
{
        int i =0;
        int tsum = 0;
        year[0] = 2021; 
        year[1] = year[2] = tdata[0].tmax;

        for (i = 0; i < NUMBER_OF_MONTHS; ++i) {
                tsum += tdata[i].avg_t;
                if (year[1] <= tdata[i].tmax) year[1] = tdata[i].tmax;
                if (year[2] >= tdata[i].tmin) year[2] = tdata[i].tmin;
        }
        year[3] = tsum / NUMBER_OF_MONTHS;
}

void print_data(data_s *tdata, int *mopt)
{
        int y[4] = {0};
        int is_single_month = mopt[0];
        int single_month = mopt[1] - 1;
        get_year_data(tdata, y);

        int year        = y[0];
        int tmax_year   = y[1];
        int tmin_year   = y[2];
        int avg_t_year  = y[3];

        printf("Temperature reoprt:\n");

        if (is_single_month) {
                printf("%-25s\n", tdata[single_month].month_name);
                printf(" Max. t°: %d\n", tdata[single_month].tmax);
                printf(" Min. t°: %d\n", tdata[single_month].tmin);
                printf(" Avg. t°: %d\n", tdata[single_month].avg_t);
                printf("\n");        
        } else {
                printf("Year: %d\n", year);
                printf("Max. year t°: %d\n", tmax_year);
                printf("Min. year t°: %d\n", tmin_year);
                printf("Avg. year t°: %d\n", avg_t_year);

                printf("----------------------------------------------------------------------\n");

                printf("Detailed months report:\n");
                printf("%-25s%-25s%-25s\n", tdata[0].month_name, tdata[1].month_name, tdata[2].month_name);
                printf(" Max. t°: %-16dMax. t°: %-16dMax. t°: %-17d\n", tdata[0].tmax, tdata[1].tmax, tdata[2].tmax);
                printf(" Min. t°: %-16dMin. t°: %-16dMin. t°: %-17d\n", tdata[0].tmin, tdata[1].tmin, tdata[2].tmin);
                printf(" Avg. t°: %-16dAvg. t°: %-16dAvg. t°: %-17d\n", tdata[0].avg_t, tdata[1].avg_t, tdata[2].avg_t);
                printf("\n");

                printf("%-25s%-25s%-25s\n", tdata[3].month_name, tdata[4].month_name, tdata[5].month_name);
                printf(" Max. t°: %-16dMax. t°: %-16dMax. t°: %-17d\n", tdata[3].tmax, tdata[4].tmax, tdata[5].tmax);
                printf(" Min. t°: %-16dMin. t°: %-16dMin. t°: %-17d\n", tdata[3].tmin, tdata[4].tmin, tdata[5].tmin);
                printf(" Avg. t°: %-16dAvg. t°: %-16dAvg. t°: %-17d\n", tdata[3].avg_t, tdata[4].avg_t, tdata[5].avg_t);
                printf("\n");

                printf("%-25s%-25s%-25s\n", tdata[6].month_name, tdata[7].month_name, tdata[8].month_name);
                printf(" Max. t°: %-16dMax. t°: %-16dMax. t°: %-17d\n", tdata[6].tmax, tdata[7].tmax, tdata[8].tmax);
                printf(" Min. t°: %-16dMin. t°: %-16dMin. t°: %-17d\n", tdata[6].tmin, tdata[7].tmin, tdata[8].tmin);
                printf(" Avg. t°: %-16dAvg. t°: %-16dAvg. t°: %-17d\n", tdata[6].avg_t, tdata[7].avg_t, tdata[8].avg_t);
                printf("\n");

                printf("%-25s%-25s%-25s\n", tdata[9].month_name, tdata[10].month_name, tdata[11].month_name);
                printf(" Max. t°: %-16dMax. t°: %-16dMax. t°: %-17d\n", tdata[9].tmax, tdata[10].tmax, tdata[11].tmax);
                printf(" Min. t°: %-16dMin. t°: %-16dMin. t°: %-17d\n", tdata[9].tmin, tdata[10].tmin, tdata[11].tmin);
                printf(" Avg. t°: %-16dAvg. t°: %-16dAvg. t°: %-17d\n", tdata[9].avg_t, tdata[10].avg_t, tdata[11].avg_t);
                printf("\n");

                printf("----------------------------------------------------------------------\n");
        }
        printf("Total entries read: \n");
        printf("Total errors found: %d, in lines %d\n", 1, 1);

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

void check_moption(char *optstr, int *moption, _Bool is_file_set)
{
        int opt = atoi(optstr);

        if (opt > 12 || opt < 1 ) {
                print_error("ERROR: Wrong month number.\nPlease enter number in range from 1 to 12.\n");
                exit(1);
        }

        if (is_file_set) {
                moption[0] = true;
                moption[1] = opt;
        } else {
                print_error("ERROR: Wrong argument(s).\n");
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
        printf("  -m\tDisplay particular month by enter number in range form 1 to 12\n");
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

void print_error(char *str)
{
        printf("%s", str);
        printf("Try tempstat -h for help.\n");
}

