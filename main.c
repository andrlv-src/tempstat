/*
* temperature
* Utility for show statistics from temperature sensor.
*
*
*/

/*
 * TODO
 * TODO #ifndef in h file
 * TODO Makefile
 * TODO 
 *
 */


#include <stdio.h>
#include <unistd.h>
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
                                printf("Found arg \"h\".\n");
                                //print_help
                                break;
                        case 'm':
                                printf("Found arg \"m = %s\".\n", optarg);
                                break;
                        case 'v':
                                printf("Found arg \"v\".\n");
                                //print_version
                                break;
                        case 'y':
                                printf("Found arg \"y = %s\".\n", optarg);
                                break;
                        case '?':
                                printf("Error! Wrong argument!\n");
                                break;
                        default:
                                printf("Error! Wrong argument!\n");
                                // print_help();
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

