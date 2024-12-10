#include "inventory.h"

void displayMainMenu();
void displayOwnerMenu();
void displayCustomerMenu();
void loadProductsFromCSV(struct Product products[], int *productCount);
void loadUsers();

int main() {
    struct Product products[MAX_PRODUCTS];
    int productCount = 0;
    int choice;
    
    loadProductsFromCSV(products, &productCount);
    loadUsers();
    
    while(1) {
        displayMainMenu();
        scanf("%d", &choice);
        system("cls");
        switch(choice) {
            case 0:
                printf("Thank you for using the system!\n");
                return 0;
            case 1: {
                char username[50], password[50];
                printf("\nOwner Login\n");
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf("%s", password);
                system("cls");

                if (authenticateUser(username, password, 1)) {
                    displayOwnerMenu();
                    int ownerChoice;
                    int reportChoice; // Yang Mai Dai Tam Report Na
                    int editChoice; // Yang Mai
                    int restockChoice; // Dai Tam
                    int couponChoice; // Loeyyyy

                    do {
                        printf("\n0. Return to Main Menu\n");
                        printf("1. View Reports\n");
                        printf("2. Edit Products\n");
                        printf("3. Restock Products\n");
                        printf("4. Edit Coupons\n");
                        printf("Enter your choice: ");
                        scanf("%d", &ownerChoice);
                        system("cls");
                        switch (ownerChoice) {
                            case 0:
                                printf("Returning to Main Menu...\n");
                                break;
                            case 1:
                                // View Reports
                                break;
                            case 2:
                                // Edit Products
                                break;
                            case 3:
                                // Restock Products
                                break;
                            case 4:
                                // Edit Coupons
                                break;
                            default:
                                printf("Invalid choice!\n");
                                break;
                        }
                    } while (ownerChoice!=0);
                } else {
                    printf("Authentication failed!\n");
                }
                break;
            }
            case 2: {
                char username[50], password[50];
                printf("\nCustomer Login\n");
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf("%s", password);
                system("cls");
                
                if (authenticateUser(username, password, 0)) {
                    displayCustomerMenu();
                    int customerChoice;
                    int viewChoice;
                    int purchaseChoice; // Yang mai sed

                    do {
                        printf("\n0. Return to Main Menu\n");
                        printf("1. View Products\n");
                        printf("2. Purchase Product\n");
                        printf("Enter your choice: ");
                        scanf("%d", &customerChoice);
                        system("cls");
                        
                        switch(customerChoice) {
                            case 0:
                                printf("Returning to Main Menu...\n");
                                break;
                            case 1:
                                printf("\n1. View All Products\n");
                                printf("2. View by Name\n");
                                printf("3. View by Description\n");
                                printf("4. View by Price\n");
                                printf("Enter your choice: ");
                                scanf("%d", &viewChoice);
                                system("cls");
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
                                printf("\n1. Purchase product\n");
                                printf("2. Schedule Auto-buy\n");
                                printf("Enter your choice: ");
                                scanf("%d", &purchaseChoice);
                                system("cls");
                                switch (purchaseChoice) {
                                    case 1:
                                        // Purchase product
                                        break;
                                    case 2:
                                        // Schedule Auto-buy
                                        break;
                                    default:
                                        printf("Invalid choice!\n");
                                        break;
                                }
                                break;
                            default:
                                printf("Invalid choice!\n");
                                break;
                        }
                    } while(customerChoice != 0);
                } else {
                    printf("Authentication failed!\n");
                }
                break;
            }
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