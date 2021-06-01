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
        int minutes;     /* amount minutes correspond to temperature */
        _Bool t_is_set;
        signed int tmax;
        signed int tmin;
        signed int avg_t;       /* average month temperature */
        signed int tsum; /* sum of all temper measures. tsum/minutes = avg_t */
} data_s;

void dbinit(data_s *tdata);
void print_help();
void print_version();
void print_error(char *str);
void print_data(data_s *tdata, int *opt);
void print_lines_data(int *lines_data, _Bool error_log);
void check_file_len();
void argcheck(int args);
void check_moption(char *optstr, int *moption, _Bool is_file_set);
int *read_data(FILE *f, data_s *tdata);
void process_data(int *data, data_s *tdata);
data_s *get_month(data_s *tdata, int month);
void get_year_data(data_s *tdata, int *year);

#endif
