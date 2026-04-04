#ifndef UNTITLED_FUNCTIONS_TASK2_H
#define UNTITLED_FUNCTIONS_TASK2_H

typedef struct {
    int day, month, year, hour, minute;
} DateTime;

typedef struct {
    char name[50];
    char surname[50];
    int account_number;
    float deposit_rate;
    double deposit_money;
    DateTime opening_date;
    DateTime access_date;
} BankCustomer;

void ensure_memory(BankCustomer **customer, int *size, int *capacity);
void clear_buffer();
void read_line(char *string, int size);
void get_current_date(DateTime *date);
void add_bank_customer(BankCustomer **customer, int *size , int *capacity);
void display_bank_customers(BankCustomer *customer, int size);
void calculate_duration(DateTime opening_date, int *years, int *months, int *days);
void write_experiment_file(BankCustomer *customers, int size);
void counting_sort_by_digit(BankCustomer *customers, int *keys, int size, int exp);
void swap(BankCustomer *a, BankCustomer *b);
void radix_sort(BankCustomer *customers, int size);
void write_output_sorted(BankCustomer *customers, int size);
void merge_files(const char *file1, const char *file2, const char *result);

#endif //UNTITLED_FUNCTIONS_TASK2_H