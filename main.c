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
        _Bool is_file_set = false;
        char fname[MAX_FILE_NAME_LEN] = {0};
        int arg = 0;        
        data_s tdata[NUMBER_OF_MONTHS]; /* tdata - temperature database */
        dbinit(tdata);
        argcheck(argc);
        opterr = 0;
        while ((arg = getopt(argc, argv, "f:hm:vy:")) != -1) {
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
                        /* TODO check for file set because all options
                           follow only when file is set
                        */
                        printf("Found arg \"m = %s\".\n", optarg);
                        break;
                case 'y':
                        printf("Found arg \"y = %s\".\n", optarg);
                        break;
                case '?':
                        printf("ERROR: Wrong argument(s).\n");
                        printf("Try tempstat -h for help.\n");
                        exit(1);
                        break;
                default:
                        printf("Error! Wrong argument! Default case exit.\n");
                        exit(1);
                        break;
                }
        }

        /* read file */
        fp = fopen(fname, "r");
        if (fp == NULL) {
                printf("ERROR: file \"%s\" not found.\n", fname);
                exit(1);
        }

        read_data(fp, tdata);
        fclose(fp);
        print_data(tdata);

/*
        there need to test different delimiter for additonal functionality
        out/printing
        additonal func
*/

        return 0;
}

