#include "inventory.h"

void restockProducts(struct Product products[], int productCount, int *threshold) {
    int choice;

    do {
        belowThreshold(products, productCount, *threshold);

        printf("\n=== Restock Products Menu ===\n");
        printf("1. View Products\n");
        printf("2. Restock Product\n");
        printf("3. Set Restock Threshold\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        system("cls");
        switch(choice) {
            case 1:
                viewAllProducts(products, productCount);
                break;
            case 2:
                restockProduct(products, productCount);
                break;
            case 3:
                setTreshold(threshold);
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while(choice != 0);
}

void restockProduct(struct Product products[], int productCount) {
    char productName[50];
    int quantity;
    int found = 0;
    char restockTime[20];

    while (getchar() != '\n');
    printf("Enter the product name: ");
    fgets(productName, sizeof(productName), stdin);
    productName[strcspn(productName, "\n")] = 0;

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found!\n");
        return;
    }

    printf("Enter the quantity to restock: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Invalid quantity!\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            products[i].stock += quantity;
            break;
        }
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(restockTime, sizeof(restockTime), "%Y-%m-%d %H:%M:%S", t);

    logRestock(productName, quantity, restockTime);
    saveProducts(products, productCount);
    printf("Restock successful!\n");
}

void setTreshold(int *threshold) {
    printf("Enter the restock threshold: ");
    scanf("%d", threshold);

    if (*threshold < 0) {
        printf("Invalid threshold!\n");
        return;
    }

    saveThreshold(*threshold);
    printf("Restock threshold set to %d\n", *threshold);
}

void belowThreshold(struct Product products[], int productCount, int threshold) {
    int found = 0;

    for (int i = 0; i < productCount; i++) {
        if (products[i].stock < threshold) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No products below restock threshold.\n");
        return;
    }

    printf("\n=== Products Below Restock Threshold ===\n");
    printf("%-20s %-30s %-10s %-10s\n", "Name", "Description", "Price", "Stock");
    for (int i = 0; i < productCount; i++) {
        if (products[i].stock < threshold) {
            printf("%-20s %-30s $%-9.2f %-10d\n", 
                products[i].name, 
                products[i].description, 
                products[i].price, 
                products[i].stock);
        }
    }
}