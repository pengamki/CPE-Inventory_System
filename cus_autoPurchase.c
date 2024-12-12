#include "inventory.h"

void autoPurchase(struct Product products[], int productCount, struct Coupon coupons[], int couponCount) {
    char productName[50];
    int quantity;
    char purchaseDay[10];
    char lastPurchase[11];
    int found = 0;
    float totalPrice = 0.0;

    printf("Enter the product name: ");
    scanf("%s", productName);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    printf("Enter the purchase day (e.g., Monday): ");
    scanf("%s", purchaseDay);

    if (!isValidDay(purchaseDay)) {
        printf("Invalid purchase day!\n");
        return;
    }

    if (quantity <= 0) {
        printf("Invalid quantity!\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Product not found!\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(lastPurchase, sizeof(lastPurchase), "%Y-%m-%d", t);

    FILE *file = fopen("./csv/autopurchase.csv", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s,%d,%s,%s\n", productName, quantity, purchaseDay, lastPurchase);
    fclose(file);

    printf("Auto-purchase scheduled successfully!\n");
}

void performAutoPurchases(struct Product products[], int productCount, struct Coupon coupons[], int couponCount, struct AutoPurchase autoPurchases[], int autoPurchaseCount) {
    for (int i = 0; i < autoPurchaseCount; i++) {
        if (isDayOfWeek(autoPurchases[i].purchaseDay)) {
            char productName[50];
            int quantity = autoPurchases[i].quantity;
            float totalPrice = 0.0;
            char couponCode[20] = "";
            float discount = 0.0;
            int found = 0;

            for (int j = 0; j < productCount; j++) {
                if (strcmp(products[j].name, autoPurchases[i].productName) == 0) {
                    if (products[j].stock >= quantity) {
                        totalPrice = products[j].price * quantity;
                        products[j].stock -= quantity;
                        found = 1;
                        break;
                    } else {
                        printf("Insufficient stock for %s!\n", autoPurchases[i].productName);
                        return;
                    }
                }
            }

            if (!found) {
                printf("Product %s not found!\n", autoPurchases[i].productName);
                return;
            }

            logPurchase(autoPurchases[i].productName, quantity, totalPrice, discount, couponCode);

            time_t now = time(NULL);
            struct tm *t = localtime(&now);
            strftime(autoPurchases[i].lastPurchase, sizeof(autoPurchases[i].lastPurchase), "%Y-%m-%d", t);

            printf("Auto-purchase for %s completed successfully! Total price: %.2f\n", autoPurchases[i].productName, totalPrice);
        }
    }
    saveAutoPurchases(autoPurchases, autoPurchaseCount);
}

int isValidDay(const char* day) {
    const char* validDays[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < 7; i++) {
        if (strcmp(day, validDays[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isDayOfWeek(const char* day) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char currentDay[10];
    strftime(currentDay, sizeof(currentDay), "%A", t);
    return strcmp(currentDay, day) == 0;
}