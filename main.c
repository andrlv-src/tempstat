/*      main.c
 *
 *      "tempstat" - Temperature statistics console utility for show statistics
 *      from csv file gathered by temperature sensor.
 *
 *      Written 2021 by Andrey Lvov
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "temp_functions.h"

int main(int argc, char *argv[])
{
        FILE *fp = NULL;
        int *ld= NULL; /* lines data array pointer */
        _Bool is_file_set = false;
        _Bool error_log = false;
        int moption[2] = {0};
        char fname[MAX_FILE_NAME_LEN] = {0};
        int arg = 0;        
        data_s tdata[NUMBER_OF_MONTHS]; /* tdata - temperature database */
        dbinit(tdata);
        argcheck(argc);
        opterr = 0;

        while ((arg = getopt(argc, argv, "f:hm:ve")) != -1) {
                switch (arg) {
                case 'f':
                        is_file_set = true;
                        check_file_len(MAX_FILE_NAME_LEN, strlen(optarg));
                        strcpy(fname, optarg);
                        break;
                case 'h':
                        print_help();
                        return 0;
                        break;
                case 'v':
                        print_version();
                        return 0;
                        break;
                case 'm':
                        check_moption(optarg, moption, is_file_set);
                        break;
                case 'e':
                        error_log = true;
                        break;
                case '?':
                        print_error("ERROR: Wrong argument(s).\n");
                        exit(1);
                        break;
                default:
                        print_error("ERROR: Wrong argument! Default exit.\n");
                        exit(1);
                        break;
                }
        }

        /* check for running with no args, but with random entry */
        if (strcmp(fname, "") == 0 && is_file_set == false) {
                print_error("ERROR: wrong argument(s).\n");
                exit(1);
        }

        fp = fopen(fname, "r");
        if (fp == NULL) {
                printf("ERROR: file \"%s\" not found.\n", fname);
                exit(1);
        }
        ld = read_data(fp, tdata);
        fclose(fp);
        print_data(tdata, moption);
        print_lines_data(ld, error_log);
        free(ld);

        return 0;
}

