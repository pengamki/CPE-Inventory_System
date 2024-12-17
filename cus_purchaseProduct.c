#include "inventory.h"

void purchaseProduct(struct Product products[], int productCount, struct Coupon coupons[], int couponCount) {
    char productName[50];
    int quantity;
    int found = 0;
    float totalPrice = 0.0;
    char couponCode[20];
    float discount = 0.0;
    char purchaseTime[20];

    while (getchar() != '\n');
    printf("Enter the product name: ");
    fgets(productName, sizeof(productName), stdin);
    productName[strcspn(productName, "\n")] = 0;

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

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Invalid quantity!\n");
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

    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].name, productName) == 0) {
            if (products[i].stock >= quantity) {
                totalPrice = products[i].price * quantity;
                products[i].stock -= quantity;
                break;
            } else {
                printf("Insufficient stock for %s!\n", productName);
                return;
            }
        }
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(purchaseTime, sizeof(purchaseTime), "%Y-%m-%d %H:%M:%S", t);

    logPurchase(productName, quantity, totalPrice, discount, couponCode, purchaseTime);
    saveProducts(products, productCount);
    printf("Purchase successful! Total price: %.2f\n", totalPrice);
}
