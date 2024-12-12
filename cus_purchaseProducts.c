#include "inventory.h"

void purchaseProducts(struct Product products[], int productCount, struct Coupon coupons[], int couponCount) {
    int purchaseChoice;

    printf("\n1. Purchase product\n");
    printf("2. Schedule Auto-buy\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &purchaseChoice);

    system("cls");
    switch (purchaseChoice) {
        case 1:
            purchaseProduct(products, productCount, coupons, couponCount);
            break;
        case 2:
            autoPurchase(products, productCount, coupons, couponCount);
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}

void purchaseProduct(struct Product products[], int productCount, struct Coupon coupons[], int couponCount) {
    char productName[50];
    int quantity;
    int found = 0;
    float totalPrice = 0.0;
    char couponCode[20];
    float discount = 0.0;

    printf("Enter the product name: ");
    scanf("%s", productName);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Invalid quantity!\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            if (products[i].stock >= quantity) {
                totalPrice = products[i].price * quantity;
                products[i].stock -= quantity;
                found = 1;
                break;
            } else {
                printf("Insufficient stock!\n");
                return;
            }
        }
    }

    if (!found) {
        printf("Product not found!\n");
        return;
    }

    while (getchar() != '\n');
    printf("Enter coupon code (or press enter to skip): ");
    fgets(couponCode, sizeof(couponCode), stdin);
    couponCode[strcspn(couponCode, "\n")] = 0;

    if (strlen(couponCode) == 0) {
        printf("No coupon applied.\n");
    } else {
        for (int i = 0; i < couponCount; i++) {
            if (strcmp(coupons[i].code, couponCode) == 0) {
                if (isCouponValid(coupons[i].expiryDate)) {
                    discount = coupons[i].discount;
                    break;
                }
                break;
            }
        }

        if (discount > 0.0) {
            totalPrice = totalPrice * (1 - discount / 100);
            printf("Coupon applied! Discount: %.2f%%\n", discount);
        } else {
            printf("Coupon not found or expired!\n");
        }
    }

    logPurchase(productName, quantity, totalPrice, discount, couponCode);
    sortProducts(products, productCount);
    saveProductsToCSV(products, productCount);

    printf("Purchase successful! Total price: %.2f\n", totalPrice);
}

int isCouponValid(const char* expirationDate) {
    int year, month, day;
    sscanf(expirationDate, "%d-%d-%d", &year, &month, &day);

    time_t now = time(NULL);
    struct tm *current = localtime(&now);

    if (year < (current->tm_year + 1900)) {
        return 0;
    } else if (year == (current->tm_year + 1900)) {
        if (month < (current->tm_mon + 1)) {
            return 0;
        } else if (month == (current->tm_mon + 1)) {
            if (day < current->tm_mday) {
                return 0;
            }
        }
    }
    return 1;
}
