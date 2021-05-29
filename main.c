/*      main.c
 *
 *      "tempstat" - Temperature statistics console utility for show statistics
 *      from csv file gathered by temperature sensor.
 *
 *      written 2021 by Andrey Lvov
 */

/*
 * TODO additonal options, for example gistogram of somthing the same
 * TODO check for run without arguments and print help
 *
 */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "temp_functions.h"

int main(int argc, char *argv[])
{
        /* process args
         *
         *  options list
         *
         *  -f=filename.csv
         *  -h help
         *  -m=month number
         *
         *  additonal options
         *
         *  -v version
         *  -y=year
         *
         *
         *  -D delimiter . , ; : "
         *  -M default month
         *
         */

        int arg = 0;        
        while ((arg = getopt(argc, argv, "f:hm:vy:")) != -1) {
                switch (arg) {
                        case 'f':
                                printf("Found arg \"f = %s\".\n", optarg);
                                break;
                        case 'h':
                                print_help();
                                break;
                        case 'm':
                                printf("Found arg \"m = %s\".\n", optarg);
                                break;
                        case 'v':
                                print_version();
                                break;
                        case 'y':
                                printf("Found arg \"y = %s\".\n", optarg);
                                break;
                        case '?':
                                printf("Try tempstat -h for help.\n");
                                exit(1);
                                break;
                        default:
                                printf("Error! Wrong argument! Default case exit.\n");
                                print_help();
                                exit(1);
                                break;
                }
        }

        // get help

        // read file

        // data structure
        
        // parse data , TODO check csv file errors, show line __LINE__
        
        // out/printing
        
        // makefile
        
        // additonal func

        // test args
        return 0;
}

