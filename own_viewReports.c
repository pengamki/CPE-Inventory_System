#include "inventory.h"

void viewReports(struct Product products[], int productCount) {
    int reportChoice;
    
    printf("\n1. View Purchase Report\n");
    printf("2. View Stock Report\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &reportChoice);

    system("cls");
    switch(reportChoice) {
        case 1:
            viewPurchaseReport(products, productCount);
            break;
        case 2:
            viewStockReport(products, productCount);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}

void viewPurchaseReport(struct Product products[], int productCount) {
    printf("\n=== Purchase Report ===\n");
    printf("%-20s %-10s %-10s\n", "Name", "Quantity", "Total Price");
    FILE *file = fopen("./csv/purchaselog.csv", "r");
    if (file == NULL) {
        printf("No purchase report found.\n");
        return;
    }
    
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, file)) {
        char *delim = ",";
        char *token = strtok(line, delim);
        char productName[50];
        strcpy(productName, token);
        
        token = strtok(NULL, delim);
        int quantity = atoi(token);
        
        token = strtok(NULL, delim);
        float totalPrice = atof(token);
        
        printf("%-20s %-10d $%-9.2f\n", productName, quantity, totalPrice);
    }
    fclose(file);
}

void viewStockReport(struct Product products[], int productCount) {
    printf("\n=== Stock Report ===\n");
    printf("%-20s %-10s\n", "Name", "Stock");
    for (int i = 0; i < productCount; i++) {
        printf("%-20s %-10d\n", products[i].name, products[i].stock);
    }
}