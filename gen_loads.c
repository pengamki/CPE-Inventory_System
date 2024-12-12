#include "inventory.h"

void loadProductsFromCSV(struct Product products[], int *productCount) {
    FILE *file = fopen("./csv/products.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    char line[MAX_LINE];
    *productCount = 0;
    while (fgets(line, MAX_LINE, file) && *productCount < MAX_PRODUCTS) {
        char *delim = ",";

        char *token = strtok(line, delim);
        strcpy(products[*productCount].name, token);
        
        token = strtok(NULL, delim);
        strcpy(products[*productCount].description, token);
        
        token = strtok(NULL, delim);
        products[*productCount].price = atof(token);
        
        token = strtok(NULL, delim);
        products[*productCount].stock = atoi(token);
        
        (*productCount)++;
    }
    fclose(file);
}

void loadUsers(struct User users[], int *userCount) {
    FILE *file = fopen("./csv/users.csv", "r");
    if (file == NULL) {
        printf("No users file found. Creating default owner account...\n");
        FILE *newFile = fopen("./csv/users.csv", "w");
        if (newFile != NULL) {
            fprintf(newFile, "admin,admin123,1\n");
            fclose(newFile);
        }
        return;
    }
    char line[MAX_LINE];
    *userCount = 0;
    while (fgets(line, MAX_LINE, file) && *userCount < MAX_USERS) {
        char *delim = ",";

        char *token = strtok(line, delim);
        strcpy(users[*userCount].username, token);
        
        token = strtok(NULL, delim);
        strcpy(users[*userCount].password, token);
        
        token = strtok(NULL, delim);
        users[*userCount].isOwner = atoi(token);
        
        (*userCount)++;
    }
    fclose(file);
}

void loadCoupons(struct Coupon coupons[], int *couponCount) {
    FILE *file = fopen("./csv/coupons.csv", "r");
    if (file == NULL) {
        printf("No coupons file found.\n");
        return;
    }

    char line[MAX_LINE];
    *couponCount = 0;
    while (fgets(line, MAX_LINE, file) && *couponCount < MAX_COUPONS) {
        char *delim = ",\n";

        char *token = strtok(line, delim);
        strcpy(coupons[*couponCount].code, token);

        token = strtok(NULL, delim);
        coupons[*couponCount].discount = atof(token);

        token = strtok(NULL, delim);
        strcpy(coupons[*couponCount].expiryDate, token);

        (*couponCount)++;
    }
    fclose(file);
}

void loadAutoPurchases(struct AutoPurchase autoPurchases[], int *autoPurchaseCount) {
    FILE *file = fopen("./csv/autopurchase.csv", "r");
    if (file == NULL) {
        printf("No auto-purchase file found.\n");
        return;
    }

    char line[MAX_LINE];
    *autoPurchaseCount = 0;
    while (fgets(line, MAX_LINE, file) && *autoPurchaseCount < MAX_AUTOPURCHASES) {
        char *delim = ",";

        char *token = strtok(line, delim);
        strcpy(autoPurchases[*autoPurchaseCount].productName, token);

        token = strtok(NULL, delim);
        autoPurchases[*autoPurchaseCount].quantity = atoi(token);

        token = strtok(NULL, delim);
        strcpy(autoPurchases[*autoPurchaseCount].purchaseDay, token);

        token = strtok(NULL, delim);
        strcpy(autoPurchases[*autoPurchaseCount].lastPurchase, token);

        (*autoPurchaseCount)++;
    }
    fclose(file);
}
