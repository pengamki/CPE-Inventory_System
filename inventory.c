#include "inventory.h"

void displayMainMenu();
void displayOwnerMenu();
void displayCustomerMenu();
void loadProductsFromCSV(struct Product products[], int *productCount);

int main() {
    struct Product products[MAX_PRODUCTS];
    int productCount = 0;
    int choice;
    
    loadProductsFromCSV(products, &productCount);
    
    while(1) {
        displayMainMenu();
        scanf("%d", &choice);
        
        switch(choice) {
            case 0:
                printf("Thank you for using the system!\n");
                return 0;
            case 1:
                displayOwnerMenu();
                int ownerChoice;

                do {
                    printf("\n0. Return to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &ownerChoice);
                    
                    switch(ownerChoice) {
                        case 0:
                            printf("Returning to Main Menu...\n");
                            break;
                        default:
                            printf("Invalid choice!\n");
                            break;
                    }
                } while(ownerChoice != 0);
                break;
            case 2:
                displayCustomerMenu();
                int customerChoice;
                int viewChoice;
                int purchaseChoice;

                do {
                    printf("\n0. Return to Main Menu\n");
                    printf("1. View Products\n");
                    printf("2. Purchase Product\n");
                    printf("Enter your choice: ");
                    scanf("%d", &customerChoice);
                    
                    switch(customerChoice) {
                        case 0:
                            printf("Returning to Main Menu...\n");
                            break;
                        case 1:
                            printf("1. View All Products\n");
                            printf("2. View by Name\n");
                            printf("3. View by Description\n");
                            printf("4. View by Price\n");
                            printf("Enter your choice: ");
                            scanf("%d", &viewChoice);
                            switch(viewChoice) {
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
                                default:
                                    printf("Invalid choice!\n");
                                    break;
                            }
                            break;
                        case 2:
                            printf("1. Purchase product");
                            printf("2. Auto-buy products");
                            printf("Enter your choice: ");
                            scanf("%d", &purchaseChoice);
                            switch(purchaseChoice) {
                                case 1:
                                    // purchaseProduct(products, productCount);
                                    break;
                                case 2:
                                    // autoBuyProducts(products, productCount);
                                    break;
                                default:
                                    printf("Invalid choice!\n");
                                    break;
                            }
                        default:
                            printf("Invalid choice!\n");
                            break;
                    }
                } while(customerChoice != 0);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

void displayMainMenu() {
    printf("\n=== Inventory Management System ===\n");
    printf("0. Exit\n");
    printf("1. Owner Menu\n");
    printf("2. Customer Menu\n");
    printf("Enter your choice: ");
}

void displayOwnerMenu() {
    printf("\n=== Owner Menu ===\n");
}

void displayCustomerMenu() {
    printf("\n=== Customer Menu ===\n");
}

void loadProductsFromCSV(struct Product products[], int *productCount) {
    FILE *file = fopen("./csv/products.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, file) && *productCount < MAX_PRODUCTS) {
        char *token = strtok(line, ",");
        strcpy(products[*productCount].name, token);
        
        token = strtok(NULL, ",");
        strcpy(products[*productCount].description, token);
        
        token = strtok(NULL, ",");
        products[*productCount].price = atof(token);
        
        token = strtok(NULL, ",");
        products[*productCount].stock = atoi(token);
        
        (*productCount)++;
    }
    fclose(file);
}