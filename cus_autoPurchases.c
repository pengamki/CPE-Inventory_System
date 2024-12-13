#include "inventory.h"

void setAutoPurchase(struct Product products[], int productCount, struct Coupon coupons[], int couponCount, struct AutoPurchase autoPurchases[], int autoPurchaseCount) {
    int purchaseChoice;

    loadAutoPurchases(autoPurchases, &autoPurchaseCount);
    printf("\n1. View Auto-buy Schedule\n");
    printf("2. Schedule Auto-buy\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &purchaseChoice);

    system("cls");
    switch (purchaseChoice) {
        case 1:
            autoPurchase(products, productCount, coupons, couponCount);
            break;
        case 2:
            viewAutoPurchases(autoPurchases, autoPurchaseCount);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}

void autoPurchase(struct Product products[], int productCount, struct Coupon coupons[], int couponCount) {
    char productName[50];
    int quantity;
    char couponCode[20];
    char purchaseDay[10];
    char lastPurchase[11];
    int found = 0;
    float totalPrice = 0.0;
    float discount = 0.0;

    printf("Enter the product name: ");
    scanf("%s", productName);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    printf("Enter the coupon code (or press enter to skip): ");
    scanf("%s", couponCode);
    printf("Enter the purchase day (e.g., Monday): ");
    scanf("%s", purchaseDay);

    if (!isValidDay(purchaseDay)) {
        printf("Invalid purchase day! Aborting process.\n");
        return;
    }

    if (quantity <= 0) {
        printf("Invalid quantity! Aborting process.\n");
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
        printf("Error opening autopurchase file!\n");
        return;
    }

    fprintf(file, "%s,%d,%s,%s,%s\n", productName, quantity, couponCode, purchaseDay, lastPurchase);
    fclose(file);

    printf("Auto-purchase scheduled successfully!\n");
}

void performAutoPurchases(struct Product products[], int productCount, struct Coupon coupons[], int couponCount, struct AutoPurchase autoPurchases[], int autoPurchaseCount) {
    time_t now = time(NULL);
    struct tm *currentDate = localtime(&now);

    for (int i = 0; i < autoPurchaseCount; i++) {
        struct tm lastPurchaseDate;
        if (!custom_strptime(autoPurchases[i].lastPurchase, &lastPurchaseDate)) {
            printf("Error parsing last purchase date for %s\n", autoPurchases[i].productName);
            continue;
        }

        int daysDiff = daysBetween(&lastPurchaseDate, currentDate);
        int weeksDiff = daysDiff / 7;

        for (int w = 1; w <= weeksDiff; w++) {
            struct tm purchaseDate = lastPurchaseDate;
            purchaseDate.tm_mday += w * 7;
            mktime(&purchaseDate);

            if (isDayOfWeek(autoPurchases[i].purchaseDay, &purchaseDate)) {
                char productName[50];
                int quantity = autoPurchases[i].quantity;
                float totalPrice = 0.0;
                char couponCode[20];
                strcpy(couponCode, autoPurchases[i].couponCode);
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

                // Apply coupon if available and valid for the purchase date
                for (int k = 0; k < couponCount; k++) {
                    if (strcmp(coupons[k].code, couponCode) == 0) {
                        struct tm couponExpiryDate;
                        if (custom_strptime(coupons[k].expiryDate, &couponExpiryDate) && difftime(mktime(&couponExpiryDate), mktime(&purchaseDate)) >= 0) {
                            discount = coupons[k].discount;
                            break;
                        }
                    }
                }

                if (discount > 0.0) {
                    totalPrice = totalPrice * (1 - discount / 100);
                    printf("Coupon applied! Discount: %.2f%%\n", discount);
                }

                // Log the purchase
                char purchaseDateStr[11];
                strftime(purchaseDateStr, sizeof(purchaseDateStr), "%Y-%m-%d", &purchaseDate);
                logPurchase(autoPurchases[i].productName, quantity, totalPrice, discount, couponCode);

                // Update last purchase date
                strcpy(autoPurchases[i].lastPurchase, purchaseDateStr);

                printf("Auto-purchase for %s on %s completed successfully! Total price: %.2f\n", autoPurchases[i].productName, purchaseDateStr, totalPrice);
            }
        }
    }

    // Save updated auto-purchase details
    saveAutoPurchases(autoPurchases, autoPurchaseCount);
}

void viewAutoPurchases(struct AutoPurchase autoPurchases[], int autoPurchaseCount) {
    printf("\n=== Auto-Purchase Schedule ===\n");
    printf("%-20s %-10s %-10s %-15s %-10s\n", "Product Name", "Quantity", "Coupon", "Purchase Day", "Last Purchase");
    for (int i = 0; i < autoPurchaseCount; i++) {
        printf("%-20s %-10d %-10s %-15s %-10s\n", 
            autoPurchases[i].productName, 
            autoPurchases[i].quantity, 
            autoPurchases[i].couponCode, 
            autoPurchases[i].purchaseDay, 
            autoPurchases[i].lastPurchase);
    }
}