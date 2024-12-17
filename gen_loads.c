#include "inventory.h"

void loadProducts(struct Product products[], int *productCount) {
    FILE *file = fopen("./csv/products.csv", "r");
    if (file == NULL) {
        printf("No products file found.\n");
        return;
    }
    
    char line[MAX_LINE];
    *productCount = 0;
    while (fgets(line, MAX_LINE, file) && *productCount < MAX_PRODUCTS) {
        char *delim = ",\n";

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
        char *delim = ",\n";

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

void loadThreshold(int *threshold) {
    FILE *file = fopen("./csv/threshold.txt", "r");
    if (file == NULL) {
        printf("No threshold setted.\n");
        return;
    }

    fscanf(file, "%d", threshold);
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
        char *delim = ",\n";

        char *token = strtok(line, delim);
        strcpy(autoPurchases[*autoPurchaseCount].productName, token);

        token = strtok(NULL, delim);
        autoPurchases[*autoPurchaseCount].quantity = atoi(token);

        token = strtok(NULL, delim);
        strcpy(autoPurchases[*autoPurchaseCount].couponCode, token);

        token = strtok(NULL, delim);
        strcpy(autoPurchases[*autoPurchaseCount].purchaseDay, token);

        token = strtok(NULL, delim);
        strcpy(autoPurchases[*autoPurchaseCount].lastPurchase, token);

        (*autoPurchaseCount)++;
    }
    fclose(file);
}

void loadAutoRestocks(struct AutoRestock autoRestocks[], int *autoRestockCount) {
    FILE *file = fopen("./csv/autorestock.csv", "r");
    if (file == NULL) {
        printf("No auto-restock file found.\n");
        return;
    }

    char line[MAX_LINE];
    *autoRestockCount = 0;
    while (fgets(line, MAX_LINE, file) && *autoRestockCount < MAX_AUTORESTOCKS) {
        char *delim = ",\n";

        char *token = strtok(line, delim);
        strcpy(autoRestocks[*autoRestockCount].productName, token);

        token = strtok(NULL, delim);
        autoRestocks[*autoRestockCount].quantity = atoi(token);

        token = strtok(NULL, delim);
        strcpy(autoRestocks[*autoRestockCount].restockDay, token);

        token = strtok(NULL, delim);
        strcpy(autoRestocks[*autoRestockCount].lastRestock, token);

        (*autoRestockCount)++;
    }
    fclose(file);
}

void loadPurchaseLogs(struct PurchaseLog purchaseLogs[], int *purchaseLogCount) { 
    FILE *file = fopen("./csv/purchaselog.csv", "r");
    if (file == NULL) {
        printf("No purchase log file found.\n");
        return;
    }
 
    char line[MAX_LINE];
    *purchaseLogCount = 0;
    while (fgets(line, MAX_LINE, file) && *purchaseLogCount < MAX_PURCHASELOGS) {
        char *delim = ",\n";

        char *token = strtok(line, delim);
        strcpy(purchaseLogs[*purchaseLogCount].productName, token);

        token = strtok(NULL, delim);
        purchaseLogs[*purchaseLogCount].quantity = atoi(token);

        token = strtok(NULL, delim);
        strcpy(purchaseLogs[*purchaseLogCount].couponCode, token);

        token = strtok(NULL, delim);
        purchaseLogs[*purchaseLogCount].discount = atof(token);

        token = strtok(NULL, delim);
        purchaseLogs[*purchaseLogCount].totalPrice = atof(token);

        token = strtok(NULL, delim);
        strcpy(purchaseLogs[*purchaseLogCount].dateTime, token);

        (*purchaseLogCount)++;
    }
    fclose(file);
}

void loadRestockLogs(struct RestockLog restockLogs[], int *restockLogCount) {
    FILE *file = fopen("./csv/restocklog.csv", "r");
    if (file == NULL) {
        printf("No restock log file found.\n");
        return;
    }

    char line[MAX_LINE];
    *restockLogCount = 0;
    while (fgets(line, MAX_LINE, file) && *restockLogCount < MAX_RESTOCKLOGS) {
        char *delim = ",\n";

        char *token = strtok(line, delim);
        strcpy(restockLogs[*restockLogCount].productName, token);

        token = strtok(NULL, delim);
        restockLogs[*restockLogCount].quantity = atoi(token);

        token = strtok(NULL, delim);
        strcpy(restockLogs[*restockLogCount].dateTime, token);

        (*restockLogCount)++;
    }
    fclose(file);
}