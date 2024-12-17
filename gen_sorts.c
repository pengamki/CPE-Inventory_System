#include "inventory.h"

void sortProducts(struct Product products[], int productCount) {
    for (int i = 0; i < productCount; i++) {
        for (int j = i + 1; j < productCount; j++) {
            if (strcmp(products[i].description, products[j].description) > 0) {
                struct Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
}

void sortCoupons(struct Coupon coupons[], int couponCount) {
    for (int i = 0; i < couponCount; i++) {
        for (int j = i + 1; j < couponCount; j++) {
            if (strcmp(coupons[i].expiryDate, coupons[j].expiryDate) > 0) {
                struct Coupon temp = coupons[i];
                coupons[i] = coupons[j];
                coupons[j] = temp;
            }
        }
    }
}