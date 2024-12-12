#include "inventory.h"

void logPurchase(char* productName, int quantity, float totalPrice, float discount, char* couponCode) {
    FILE *file = fopen("./csv/purchaselog.csv", "a");
    if (file == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    if (strlen(couponCode) == 0) {
        fprintf(file, "%s,%d,%.2f,%.2f\n", productName, quantity, totalPrice, discount);
    } else {
        fprintf(file, "%s,%d,%.2f,%.2f,%s\n", productName, quantity, totalPrice, discount, couponCode);
    }
    fclose(file);
}

void logRestock(struct Product products[], int productCount, char* productName, int quantity) {
    FILE *file = fopen("./csv/restocklog.csv", "a");
    if (file == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    fprintf(file, "%s,%d\n", productName, quantity);
    fclose(file);
}
