/*      temp_functions.h
 *
 *      Difinition of tempstat functions.
 *
 *      Written 2021 by Andrey Lvov
 */

#ifndef temp_functions_h
#define temp_functions_h

#define VERSION "0.1"

enum {
        MAX_FILE_NAME_LEN = 100,
        NUMBER_OF_MONTHS = 12
};

typedef struct {
        int year;
        int month;
        int days;
        int tmax;
        int tmin;
        int avr_t;   /* average month temperature */
        int minutes; /* amount minutes correspond to temperature */
        int tsum;    /* sum of all temper measures. tsum / minutes = avr_t */
} data_s;

void dbinit(data_s *tdata);
void dbset();/*TODO*/
void print_help();
void print_version();
void check_file_len();
void argcheck(int args);
int read_data(FILE *f, data_s *tdata);
void parse_data(int *data, data_s *tdata);
void print_data(data_s *tdata);

#endif
