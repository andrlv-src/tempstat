/*      main.c
 *
 *      "tempstat" - Temperature statistics console utility for show statistics
 *      from csv file gathered by temperature sensor.
 *
 *      Written 2021 by Andrey Lvov
 */

/*
 * TODO additonal options, for example gistogram of somthing the same
 * TODO check for run without arguments and print help
 *
 */


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "temp_functions.h"

int main(int argc, char *argv[])
{

        FILE *f;
        _Bool is_file_set = false;
        char fname[100] = {1}; /* csv file, which will be read for dada */
        int arg = 0;        

        if (argc == 1) {
                printf("ERROR: using without arguments.\n");
                printf("Try tempstat -h for help.\n");
                exit(1);
        }
        opterr = 0;

        while ((arg = getopt(argc, argv, "f:hm:vy:")) != -1) {
                switch (arg) {
                        case 'f':
                                is_file_set = true;
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
                                 follow only when file is set */
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
        read_file(f, fname);


        /* data structure *inp_file, "r" */

        /* parse data , TODO check csv file errors, show line __LINE__
           processing through scanf
           scanf("%4d;%2d;%2d;%2d;%2d;%d", &in);
           there need to test different delimiter for additonal functionality
        */


        
        /* out/printing */
        
        /* additonal func */

        /* test args */

        return 0;
}

