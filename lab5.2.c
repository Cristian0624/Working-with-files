#include "fun_for_task2.c"

int main() {
    BankCustomer *customers = NULL;
    int size = 0, capacity = 0;
    int choice;

    while (1) {
        printf("\n========= BANK REGISTRY MENU =========\n");
        printf("(1) Add customer\n");
        printf("(2) Display customers\n");
        printf("(3) Save registry to experiment.txt\n");
        printf("(4) Write sorted durations to output.txt\n");
        printf("(5) Merge into result.txt and display\n");
        printf("(6) Read from a file\n");
        printf("(0) Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        clear_buffer();

        switch (choice) {
            case 1: {
                add_bank_customer(&customers, &size, &capacity);
                break;
            }
            case 2: {
                display_bank_customers(customers, size);
                break;
            }
            case 3: {
                write_experiment_file(customers, size);
                break;
            }

            case 4: {
                write_output_sorted(customers, size);
                break;
            }
            case 5: {
                merge_files("experiment.txt", "output2.txt", "result.txt");
                break;
            }
            case 6: {
                read_from_file(&customers, &size, &capacity);
                break;
            }
            case 0: {
                printf("Goodbye!\n");
                return 0;
            }
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
    free(customers);
}