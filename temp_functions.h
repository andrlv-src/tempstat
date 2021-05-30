/*      temp_functions.h
 *
 *      Difinition of tempstat functions.
 *
 *      Written 2021 by Andrey Lvov
 */

#ifndef temp_functions_h
#define temp_functions_h

#define VERSION "0.1"

typedef struct {
        int year;
        int month;
        int days;
        int tmax;
        int tmin;
        int avr_month_temp;
} data_s;

void print_help();
void print_version();
void check_file_len();
void argcheck(int args);
void parse_data(int *data, data_s *months);
int flread(FILE *f, data_s *months);

#endif
