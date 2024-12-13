#include "inventory.h"

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
