#include "inventory.h"

// Debugging function

static void displayUsers(struct User users[], int userCount) {
    for (int i = 0; i < userCount; i++) {
        printf("Username: %s\n", users[i].username);
        printf("Password: %s\n", users[i].password);
        printf("Is Owner: %d\n", users[i].isOwner);
    }
}

static void displayProducts(struct Product products[], int productCount) {
    for (int i = 0; i < productCount; i++) {
        printf("Name: %s\n", products[i].name);
        printf("Description: %s\n", products[i].description);
        printf("Price: %.2f\n", products[i].price);
        printf("Stock: %d\n", products[i].stock);
    }
}

static void displayCoupons(struct Coupon coupons[], int couponCount) {
    for (int i = 0; i < couponCount; i++) {
        printf("Code: %s\n", coupons[i].code);
        printf("Discount: %.2f\n", coupons[i].discount);
        printf("Expiry Date: %s\n", coupons[i].expiryDate);
    }
}

// Main function

int main() {
    struct Product products[MAX_PRODUCTS];
    int productCount = 0;
    struct User users[MAX_USERS];
    int userCount = 0;
    struct Coupon coupons[MAX_COUPONS];
    int couponCount = 0;
    struct AutoPurchase autoPurchases[MAX_AUTOPURCHASES];
    int autoPurchaseCount = 0;
    struct AutoRestock autoRestocks[MAX_AUTORESTOCKS];
    int autoRestockCount = 0;
    int choice;
    
    system("cls");
    printf("Loading data...\n");
    loadProductsFromCSV(products, &productCount);
    loadCoupons(coupons, &couponCount);
    loadAutoPurchases(autoPurchases, &autoPurchaseCount);
    loadAutoRestocks(autoRestocks, &autoRestockCount);
    sortProducts(products, productCount);
    sortCoupons(coupons, couponCount);
    performAutoPurchases(products, productCount, coupons, couponCount, autoPurchases, autoPurchaseCount);
    performAutoRestocks(products, productCount, autoRestocks, autoRestockCount);
    while(1) {
        loadUsers(users, &userCount);
        printf("\n=== Inventory Management System ===\n");
        printf("1. Owner Menu\n");
        printf("2. Customer Menu\n");
        printf("3. Account Register\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        system("cls");
        switch(choice) {
            case 1: {
                // Owner Login
                char username[50], password[50];
                printf("\nOwner Login\n");
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf("%s", password);

                if (authenticateUser(users, userCount, username, password, 1)) {
                    // Owner Menu
                    int ownerChoice;

                    system("cls");
                    do {
                        printf("\n=== Owner Menu ===\n");
                        printf("1. View Reports\n");
                        printf("2. Edit Products\n");
                        printf("3. Restock Products\n");
                        printf("4. Edit Coupons\n");
                        printf("5. View Auto-restock schedule\n");
                        printf("0. Return to Main Menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &ownerChoice);

                        system("cls");
                        switch (ownerChoice) {
                            case 1:
                                viewReports(products, productCount);
                                break;
                            case 2:
                                editProducts(products, productCount);
                                break;
                            case 3:
                                restockProducts(products, productCount);
                                break;
                            case 4:
                                editCoupons(coupons, couponCount);
                                break;
                            case 5:
                                loadAutoRestocks(autoRestocks, &autoRestockCount);
                                viewAutoRestocks(autoRestocks, autoRestockCount);
                                break;
                            case 0:
                                printf("Returning to Main Menu...\n");
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
                // Customer Login
                char username[50], password[50];
                printf("\nCustomer Login\n");
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf("%s", password);

                if (authenticateUser(users, userCount, username, password, 0)) {
                    // Customer Menu
                    int customerChoice;

                    system("cls");
                    do {
                        printf("\n=== Customer Menu ===\n");
                        printf("1. View Products\n");
                        printf("2. Purchase Product\n");
                        printf("3. View Auto-buy Schedule\n");
                        printf("0. Return to Main Menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &customerChoice);

                        system("cls");
                        switch(customerChoice) {
                            case 1:
                                viewProducts(products, productCount);
                                break;
                            case 2:
                                purchaseProducts(products, productCount, coupons, couponCount);
                                break;
                            case 3:
                                loadAutoPurchases(autoPurchases, &autoPurchaseCount);
                                viewAutoPurchases(autoPurchases, autoPurchaseCount);
                                break;
                            case 0:
                                printf("Returning to Main Menu...\n");
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
            case 3: {
                // Account Register
                char username[50], password[50];
                int isOwner;

                system("cls");
                printf("\nAccount Register\n");
                printf("Username: ");
                scanf("%s", username);
                printf("Password: ");
                scanf("%s", password);
                printf("Are you an owner? (1 for yes, 0 for no): ");
                scanf("%d", &isOwner);
                system("cls");

                if (isOwner != 0 && isOwner != 1) {
                    printf("Invalid choice!\n");
                    break;
                }
                registerUser(username, password, isOwner);
                printf("Account registered successfully!\n");
                break;
            case 0:
                printf("Thank you for using the system!\n\n");
                return 0;
            default:
                printf("Invalid choice!\n");
                break;
            }
        }
    }
    return 0;
}