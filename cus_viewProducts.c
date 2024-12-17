#include "inventory.h"

void viewProducts(struct Product products[], int productCount) {
    int choice;

    printf("\n1. View All Products\n");
    printf("2. View by Name\n");
    printf("3. View by Description\n");
    printf("4. View by Price\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    system("cls");
    switch(choice) {
        case 1:
            viewAllProducts(products, productCount);
            break;
        case 2:
            viewByName(products, productCount);
            break;
        case 3:
            viewByDescription(products, productCount);
            break;
        case 4:
            viewByPrice(products, productCount);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}

void viewAllProducts(struct Product products[], int productCount) {
    printf("\n=== All Products ===\n");
    printf("%-20s %-30s %-10s %-10s\n", "Name", "Description", "Price", "Stock");
    for(int i = 0; i < productCount; i++) {
        printf("%-20s %-30s $%-9.2f %-10d\n", 
            products[i].name, 
            products[i].description, 
            products[i].price, 
            products[i].stock);
    }
}

void viewByName(struct Product products[], int productCount) {
    char searchName[50];

    while (getchar() != '\n');
    printf("Enter product name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;
    
    printf("\n=== Search Results ===\n");
    printf("%-20s %-30s %-10s %-10s\n", "Name", "Description", "Price", "Stock");
    for(int i = 0; i < productCount; i++) {
        if(strstr(products[i].name, searchName) != NULL) {
            printf("%-20s %-30s $%-9.2f %-10d\n", 
                products[i].name, 
                products[i].description, 
                products[i].price, 
                products[i].stock);
        }
    }
}

void viewByDescription(struct Product products[], int productCount) {
    char searchDesc[100];

    while (getchar() != '\n');
    printf("Enter description keyword to search: ");
    fgets(searchDesc, sizeof(searchDesc), stdin);
    searchDesc[strcspn(searchDesc, "\n")] = 0;
    
    printf("\n=== Search Results ===\n");
    printf("%-20s %-30s %-10s %-10s\n", "Name", "Description", "Price", "Stock");
    for(int i = 0; i < productCount; i++) {
        if(strstr(products[i].description, searchDesc) != NULL) {
            printf("%-20s %-30s $%-9.2f %-10d\n", 
                products[i].name, 
                products[i].description, 
                products[i].price, 
                products[i].stock);
        }
    }
}

void viewByPrice(struct Product products[], int productCount) {
    float minPrice;
    float maxPrice;

    printf("Enter minimum price to search: ");
    scanf("%f", &minPrice);
    printf("Enter maximum price to search: ");
    scanf("%f", &maxPrice);
    
    printf("\n=== Search Results ===\n");
    printf("%-20s %-30s %-10s %-10s\n", "Name", "Description", "Price", "Stock");
    for(int i = 0; i < productCount; i++) {
        if(minPrice <= products[i].price && products[i].price <= maxPrice) {
            printf("%-20s %-30s $%-9.2f %-10d\n", 
                products[i].name, 
                products[i].description, 
                products[i].price, 
                products[i].stock);
        }
    }
} 