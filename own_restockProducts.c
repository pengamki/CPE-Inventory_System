#include "inventory.h"

void restockProducts(struct Product products[], int productCount) {
    int choice;

    do {
        printf("\n=== Restock Products Menu ===\n");
        printf("1. View Products\n");
        printf("2. Restock Product\n");
        printf("3. Schedule Auto-restock\n");
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
                autoRestock(products, productCount);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while(choice != 0);

    sortProducts(products, productCount);
    saveProductsToCSV(products, productCount);
}

void restockProduct(struct Product products[], int productCount) {
    char productName[50];
    int quantity;
    int found = 0;

    printf("Enter the product name: ");
    scanf("%s", productName);
    printf("Enter the quantity to restock: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Invalid quantity!\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            products[i].stock += quantity;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found!\n");
        return;
    }

    logRestock(products, productCount, productName, quantity);
    sortProducts(products, productCount);
    saveProductsToCSV(products, productCount);

    printf("Restock successful!\n");
}
