#include "inventory.h"

void saveProductsToCSV(struct Product products[], int productCount) {
    FILE *file = fopen("./csv/products.csv", "w");
    if (file == NULL) {
        printf("Error opening products file!\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%s,%s,%.2f,%d\n", products[i].name, products[i].description, products[i].price, products[i].stock);
    }

    fclose(file);
}

void saveCouponsToCSV(struct Coupon coupons[], int couponCount) {
    FILE *file = fopen("./csv/coupons.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < couponCount; i++) {
        fprintf(file, "%s,%.2f,%s\n", coupons[i].code, coupons[i].discount, coupons[i].expiryDate);
    }
    fclose(file);
}

void saveAutoPurchases(struct AutoPurchase autoPurchases[], int autoPurchaseCount) {
    FILE *file = fopen("./csv/autopurchase.csv", "w");
    if (file == NULL) {
        printf("Error opening autopurchase file!\n");
        return;
    }

    for (int i = 0; i < autoPurchaseCount; i++) {
        fprintf(file, "%s,%d,%s,%s,%s\n", autoPurchases[i].productName, autoPurchases[i].quantity, autoPurchases[i].couponCode, autoPurchases[i].purchaseDay, autoPurchases[i].lastPurchase);
    }
    fclose(file);
}

void saveAutoRestocks(struct AutoRestock autoRestocks[], int autoRestockCount) {
    FILE *file = fopen("./csv/autorestock.csv", "w");
    if (file == NULL) {
        printf("Error opening autorestock file!\n");
        return;
    }

    for (int i = 0; i < autoRestockCount; i++) {
        fprintf(file, "%s,%d,%s,%s\n", autoRestocks[i].productName, autoRestocks[i].quantity, autoRestocks[i].restockDay, autoRestocks[i].lastRestock);
    }
    fclose(file);
}
