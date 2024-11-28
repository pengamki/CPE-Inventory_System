#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void customerMenu(void);
void ownerMenu(void);

int main()
{
    int choice;

    while (1)
    {
        printf("\n==Welcome to the System!==\n");
        printf("1. Customer\n");
        printf("2. Owner\n");
        printf("0. Exit\n");
        printf("Please select your role: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customerMenu();
                break;
            case 2:
                ownerMenu();
                break;
            case 0:
                printf("Exiting the system. Goodbye!\n");
                usleep(500000);
                return (0);
            default:
                printf("Invalid choice. Please try again.\n");
                usleep(500000);
                break;
        }
    }
    return (0);
}

void customerMenu(void)
{
    int choice;
    
    // login

    while (1)
    {
        printf("\n==You're in the Customer menu==\n");
        printf("1. View Products\n");
        printf("2. Purchase Products\n");
        printf("0. Exit\n");
        printf("Please select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // viewProducts()
                break;
            case 2:
                // purchaseProducts()
                break;
            case 0:
                printf("Returning to main menu...\n");
                usleep(500000);
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                usleep(500000);
                break;
        }
    }
}

void ownerMenu(void)
{
    int choice;

    //login

    while (1)
    {
        printf("\n==You're in the Owner Menu==\n");
        printf("1. View Products\n");
        printf("2. Purchase Products\n");
        printf("0. Exit\n");
        printf("Please select an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // viewReports()
                break;
            case 2:
                // editProducts()
                break;
            case 3:
                // restock()
                break;
            case 4:
                // editCoupons()
                break;
            case 0:
                printf("Returning to main menu...\n");
                usleep(500000);
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                usleep(500000);
                break;
        }
    }
}