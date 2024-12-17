#include "inventory.h"

void logPurchase(const char* productName, int quantity, float totalPrice, float discount, const char* couponCode, const char* purchaseTime) {
    FILE *file = fopen("./csv/purchaselog.csv", "a");
    if (file == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    fprintf(file, "%s,%d,%s,%.2f,%.2f,%s\n", productName, quantity, couponCode, discount, totalPrice, purchaseTime);
    fclose(file);
}

void logRestock(const char* productName, int quantity, const char* restockTime) {
    FILE *file = fopen("./csv/restocklog.csv", "a");
    if (file == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    fprintf(file, "%s,%d,%s\n", productName, quantity, restockTime);
    fclose(file);
}
