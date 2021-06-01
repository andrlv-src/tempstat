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
        char month_name[10];
        int days;
        signed int tmax;
        signed int tmin;
        int avr_t;       /* average month temperature */
        int minutes;     /* amount minutes correspond to temperature */
        signed int tsum; /* sum of all temper measures. tsum / minutes = avr_t */
} data_s;

void dbinit(data_s *tdata);
void print_help();
void print_version();
void print_error();
void check_file_len();
void argcheck(int args);
int read_data(FILE *f, data_s *tdata);
void process_data(int *data, data_s *tdata);
void print_data(data_s *tdata, _Bool opt);
data_s *get_month(data_s *tdata, int month);

#endif
