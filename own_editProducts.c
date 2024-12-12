#include "inventory.h"

void editProducts(struct Product products[], int productCount) {
    int choice;

    do {
        printf("\n=== Edit Products Menu ===\n");
        printf("1. View Products\n");
        printf("2. Add Product\n");
        printf("3. Remove Product\n");
        printf("4. Edit Product\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        system("cls");
        switch(choice) {
            case 1:
                viewAllProducts(products, productCount);
                break;
            case 2:
                addProduct(products, &productCount);
                break;
            case 3:
                removeProduct(products, &productCount);
                break;
            case 4:
                editProduct(products, productCount);
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

void addProduct(struct Product products[], int *productCount) {
    char name[50];
    char description[100];
    float price;
    int stock;

    while (getchar() != '\n');
    printf("Enter product name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("Enter product description: ");
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = 0;

    printf("Enter product price: ");
    scanf("%f", &price);

    printf("Enter product stock: ");
    scanf("%d", &stock);

    if (price < 0 || stock < 0) {
        printf("Invalid price or stock!\n");
        return;
    }

    strcpy(products[*productCount].name, name);
    strcpy(products[*productCount].description, description);
    products[*productCount].price = price;
    products[*productCount].stock = stock;
    (*productCount)++;

    sortProducts(products, *productCount);
    saveProductsToCSV(products, *productCount);
    printf("Product added!\n");
}

void removeProduct(struct Product products[], int *productCount) {
    char name[50];
    int found = 0;

    while (getchar() != '\n');
    printf("Enter product name to remove: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < *productCount; i++) {
        if (strcmp(products[i].name, name) == 0) {
            for (int j = i; j < *productCount - 1; j++) {
                products[j] = products[j + 1];
            }
            (*productCount)--;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Product removed!\n");
    } else {
        printf("Product not found!\n");
    }
}

void editProduct(struct Product products[], int productCount) {
    char productName[50];
    char newProductName[50];
    char newDescription[100];
    float newPrice;
    int newStock;
    int pos = -1;

    printf("Enter the product name to edit: ");
    scanf("%s", productName);

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Product not found!\n");
        return;
    }

    printf("Enter new product name: ");
    scanf("%s", newProductName);
    if (strlen(newProductName) == 0) {
        printf("Invalid product name!\n");
        return;
    }

    printf("Enter new product description: ");
    scanf(" %[^\n]", newDescription);
    if (strlen(newDescription) == 0) {
        printf("Invalid product description!\n");
        return;
    }

    printf("Enter new product price: ");
    if (scanf("%f", &newPrice) != 1 || newPrice < 0) {
        printf("Invalid product price!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter new product stock: ");
    if (scanf("%d", &newStock) != 1 || newStock < 0) {
        printf("Invalid product stock!\n");
        while (getchar() != '\n');
        return;
    }

    strcpy(products[pos].name, newProductName);
    strcpy(products[pos].description, newDescription);
    products[pos].price = newPrice;
    products[pos].stock = newStock;

    sortProducts(products, productCount);
    saveProductsToCSV(products, productCount);

    printf("Product updated successfully!\n");
}
