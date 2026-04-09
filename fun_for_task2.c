#include "functions_task2.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void ensure_memory(BankCustomer **customer, int *size, int *capacity) {
    if (*size >= *capacity) {
        *capacity = (*capacity == 0) ? 2 : *capacity * 2;
        *customer = realloc(*customer, *capacity * sizeof(BankCustomer));
        if (*customer == NULL) {
            printf("No more memory");
            exit(1);
        }
    }
}

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void read_line(char *string, int size) {
    fgets(string, size, stdin);
    string[strcspn(string, "\n")] = '\0';
}

void get_current_date(DateTime *date) {
    time_t raw_time = time(NULL);
    struct tm *time_info = localtime(&raw_time);

    date->day = time_info->tm_mday;
    date->month = time_info->tm_mon + 1;
    date->year = time_info->tm_year + 1900;
    date->hour = time_info->tm_hour;
    date->minute = time_info->tm_min;
}

void add_bank_customer(BankCustomer **customer, int *size , int *capacity) {
    ensure_memory(customer, size, capacity);

    BankCustomer *p = &((*customer)[*size]);
    printf("Enter customer's name:");
    read_line(p->name, sizeof(p->name));
    printf("\n");

    printf("Enter customer's surname:");
    read_line(p->surname, sizeof(p->surname));
    printf("\n");

    printf("Enter customer's account number:");
    scanf("%d", &p->account_number);
    printf("\n");

    printf("Enter customer's deposit rate:");
    scanf("%f", &p->deposit_rate);
    printf("\n");

    char choice;
    printf("Add opening date as today? (y/n)\n");
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        get_current_date(&p->opening_date);
        printf("Opening date set to today: %02d/%02d/%d %02d:%02d\n",
            p->opening_date.day,
            p->opening_date.month,
            p->opening_date.year,
            p->opening_date.hour,
            p->opening_date.minute);
    }
    else {
        get_current_date(&p->opening_date);
        printf("Enter date in the format (DD/MM/YYYY): ");
        scanf("%d/%d/%d", &p->opening_date.day, &p->opening_date.month, &p->opening_date.year);
    }
    printf("\n");

    printf("Enter the amount of money: ");
    scanf("%lf", &p->deposit_money);
    get_current_date(&p->access_date);
    clear_buffer();
    (*size)++; // Increment the size after adding the new customer
    printf("Customer added successfully!\n");
}

void display_bank_customers(BankCustomer *customer, int size) {
    if (size == 0) {
        printf("\nNo customers!\n");
        return;
    }

    printf("\n================ CUSTOMERS LIST ==================\n");
    for (int i = 0; i < size; i++) {
        BankCustomer *b = &customer[i];

        printf("\nCustomer %d\n", i + 1);
        printf("Name: %s\n", b->name);
        printf("Surname: %s\n", b->surname);
        printf("Account number: %d\n", b->account_number);
        printf("Deposit rate: %.2f (%%) \n", b->deposit_rate);
        printf("Deposit money: %.2lf \n", b->deposit_money);
        printf("Opening date: %02d/%02d/%d %02d:%02d\n",
            b->opening_date.day,
            b->opening_date.month,
            b->opening_date.year,
            b->opening_date.hour,
            b->opening_date.minute);
        printf("Last access date: %02d/%02d/%d %02d:%02d\n",
            b->access_date.day,
            b->access_date.month,
            b->access_date.year,
            b->access_date.hour,
            b->access_date.minute);
        printf("\n----------------------------------------------\n");
    }
    printf("\n===============================================\n");
    printf("\n");
}


void calculate_duration(DateTime opening_date, int *years, int *months, int *days) {
    DateTime today;
    get_current_date(&today);

    *years  = today.year - opening_date.year;
    *months = today.month - opening_date.month;
    *days   = today.day - opening_date.day;

    if (*days < 0) {
        (*months)--;
        *days += 30;
    }
    if (*months < 0) {
        (*years)--;
        *months += 12;
    }
}

void write_experiment_file(BankCustomer *customers, int size) {
    FILE *file = fopen("experiment.txt", "w");
    if (file == NULL) {
        printf("Cannot open experiment.txt\n");
        return;
    }

    fprintf(file, "=== Bank Customer Registry ===\n\n");
    for (int i = 0; i < size; i++) {
        BankCustomer *p = &customers[i];
        fprintf(file, "Customer %d\n", i + 1);
        fprintf(file, "  Name         : %s %s\n", p->name, p->surname);
        fprintf(file, "  Account #nr  : %d\n", p->account_number);
        fprintf(file, "  Deposit Rate : %.2f%%\n", p->deposit_rate);
        fprintf(file, "  Amount       : %.2lf\n", p->deposit_money);
        fprintf(file, "  Opened       : %02d/%02d/%04d %02d:%02d\n",
            p->opening_date.day,
            p->opening_date.month,
            p->opening_date.year,
            p->opening_date.hour,
            p->opening_date.minute);
        fprintf(file, "  Last Access  : %02d/%02d/%04d %02d:%02d\n\n",
            p->access_date.day,
            p->access_date.month,
            p->access_date.year,
            p->access_date.hour,
            p->access_date.minute);
    }
    fclose(file);
    printf("Registry saved to experiment.txt\n");
}

void counting_sort_by_digit(BankCustomer *customers, int *keys, int size, int exp) {
    BankCustomer *output = malloc(size * sizeof(BankCustomer));
    int *output_keys = malloc(size * sizeof(int));
    if (!output || !output_keys) { printf("No more memory\n"); exit(1); }

    int count[10] = {0};

    for (int i = 0; i < size; i++)
        count[(keys[i] / exp) % 10]++;

    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--) {
        int digit = (keys[i] / exp) % 10;
        output[count[digit] - 1] = customers[i];
        output_keys[count[digit] - 1] = keys[i];
        count[digit]--;
    }

    for (int i = 0; i < size; i++) {
        customers[i] = output[i];
        keys[i]  = output_keys[i];
    }

    free(output);
    free(output_keys);
}

void swap(BankCustomer *a, BankCustomer *b) {
    BankCustomer customer = *a;
    *a = *b;
    *b = customer;
}

void radix_sort(BankCustomer *customers, int size) {
    if (size <= 1) return;

    int *keys = malloc(size * sizeof(int));
    if (!keys) {
        printf("No more memory\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        int y, m, d;
        calculate_duration(customers[i].opening_date, &y, &m, &d);
        keys[i] = y * 365 + m * 30 + d;
    }

    int max_key = keys[0];
    for (int i = 1; i < size; i++)
        if (keys[i] > max_key) max_key = keys[i];

    if (max_key == 0) {  // guard — all durations are 0
        free(keys);
        return;
    }

    for (int exp = 1; max_key / exp > 0; exp *= 10)
        counting_sort_by_digit(customers, keys, size, exp);

    for (int i = 0; i < size / 2; i++)
        swap(&customers[i], &customers[size - 1 - i]);

    free(keys);
}

void write_output_sorted(BankCustomer *customers, int size) {
    if (size == 0) {
        printf("\nNo customers to sort!\n");
        return;
    }

    BankCustomer *sorted = malloc(size * sizeof(BankCustomer));
    if (!sorted) {
        printf("No more memory\n");
        return;
    }
    for (int i = 0; i < size; i++)
        sorted[i] = customers[i];

    radix_sort(sorted, size);

    FILE *fp = fopen("output2.txt", "w");
    if (fp == NULL) {
        printf("Cannot open output2.txt\n");
        free(sorted);
        return;
    }

    fprintf(fp, "=== Customer Duration (Descending) ===\n\n");
    for (int i = 0; i < size; i++) {
        int y, m, d;
        calculate_duration(sorted[i].opening_date, &y, &m, &d);
        fprintf(fp, "Account #%d - %s %s: %d years, %d months, %d days\n",
            sorted[i].account_number,
            sorted[i].name,
            sorted[i].surname,
            y, m, d);
    }
    fclose(fp);
    free(sorted);
    printf("Sorted durations saved to output2.txt\n");
}

void merge_files(const char *file1, const char *file2, const char *result) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    FILE *fr = fopen(result, "w");

    if (!f1 || !f2 || !fr) {
        printf("Error: make sure experiment.txt and output.txt exist first.\n");
        if (f1) fclose(f1);
        if (f2) fclose(f2);
        if (fr) fclose(fr);
        return;
    }

    char ch;
    fprintf(fr, "=== %s ===\n", file1);
    while ((ch = fgetc(f1)) != EOF)
        fputc(ch, fr);
    fprintf(fr, "\n=== %s ===\n", file2);
    while ((ch = fgetc(f2)) != EOF)
        fputc(ch, fr);

    fclose(f1); fclose(f2); fclose(fr);
    printf("Merged into %s successfully.\n", result);

    FILE *read_result = fopen(result, "r");
    if (read_result == NULL) {
        printf("Cannot open result.txt for reading.\n");
        return;
    }
    printf("\n=== Contents of result.txt ===\n");
    while ((ch = fgetc(read_result)) != EOF)
        putchar(ch);
    fclose(read_result);
}

void read_from_file(BankCustomer **customer, int *size, int *capacity) {
    char filename[100];
    printf("Enter the file name to read from: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found.\n");
        return;
    }

    int count;
    if (fscanf(file, "%d", &count) != 1) {
        fclose(file);
        return;
    }
    *size = 0;
    *capacity = count;
    *customer = realloc(*customer, (*capacity) * sizeof(BankCustomer));

    for (int i = 0; i < count; i++) {
        BankCustomer *p = &((*customer)[i]);
        fscanf(file, "%s %s %d %f %lf %d %d %d %d %d %d %d %d %d %d",
               p->name, p->surname, &p->account_number, &p->deposit_rate, &p->deposit_money,
               &p->opening_date.day, &p->opening_date.month, &p->opening_date.year,
               &p->opening_date.hour, &p->opening_date.minute,
               &p->access_date.day, &p->access_date.month, &p->access_date.year,
               &p->access_date.hour, &p->access_date.minute);
        (*size)++;
    }
    fclose(file);
    printf("Loaded %d customers from file.\n", *size);
}