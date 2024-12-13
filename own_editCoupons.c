#include "inventory.h"

void editCoupons(struct Coupon coupons[], int couponCount) {
    int choice;
    float totalPrice;

    loadCoupons(coupons, &couponCount);
    do {
        printf("\n=== Coupon Menu ===\n");
        printf("1. View Coupons\n");
        printf("2. Add Coupon\n");
        printf("3. Remove Coupon\n");
        printf("4. Apply Coupon\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        system("cls");
        switch(choice) {
            case 1:
                viewCoupons(coupons, couponCount);
                break;
            case 2:
                addCoupon(coupons, &couponCount);
                break;
            case 3:
                removeCoupon(coupons, &couponCount);
                break;
            case 4:
                printf("Enter the total price: ");
                scanf("%f", &totalPrice);
                applyCoupon(coupons, couponCount, &totalPrice);
                printf("Total price after discount: %.2f\n", totalPrice);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while(choice != 0);

    sortCoupons(coupons, couponCount);
    saveCouponsToCSV(coupons, couponCount);
}

void viewCoupons(struct Coupon coupons[], int couponCount) {
    printf("\n=== Coupons ===\n");
    printf("%-20s %-10s %-12s\n", "Code", "Discount", "Expiry Date");
    for (int i = 0; i < couponCount; i++) {
        printf("%-20s %-10.2f %-10s\n", coupons[i].code, coupons[i].discount, coupons[i].expiryDate);
    }
}

void addCoupon(struct Coupon coupons[], int *couponCount) {
    char code[20];
    float discount;
    char expiryDate[11];

    while (getchar() != '\n');
    printf("Enter coupon code: ");
    fgets(code, sizeof(code), stdin);
    code[strcspn(code, "\n")] = 0;

    printf("Enter discount percentage: ");
    scanf("%f", &discount);

    while (getchar() != '\n');
    printf("Enter expiry date (YYYY-MM-DD): ");
    fgets(expiryDate, sizeof(expiryDate), stdin);
    expiryDate[strcspn(expiryDate, "\n")] = 0;

    strcpy(coupons[*couponCount].code, code);
    coupons[*couponCount].discount = discount;
    strcpy(coupons[*couponCount].expiryDate, expiryDate);
    (*couponCount)++;

    sortCoupons(coupons, *couponCount);
    saveCouponsToCSV(coupons, *couponCount);
    printf("Coupon added!\n");
}

void removeCoupon(struct Coupon coupons[], int *couponCount) {
    char code[20];
    int found = 0;

    while (getchar() != '\n');
    printf("Enter coupon code to remove: ");
    fgets(code, sizeof(code), stdin);
    code[strcspn(code, "\n")] = 0;

    for (int i = 0; i < *couponCount; i++) {
        if (strcmp(coupons[i].code, code) == 0) {
            for (int j = i; j < *couponCount - 1; j++) {
                coupons[j] = coupons[j + 1];
            }
            (*couponCount)--;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Coupon removed!\n");
    } else {
        printf("Coupon not found!\n");
    }
}

void applyCoupon(struct Coupon coupons[], int couponCount, float *totalPrice) {
    char code[20];
    float discount = 0.0;

    while (getchar() != '\n');
    printf("Enter coupon code: ");
    fgets(code, sizeof(code), stdin);
    code[strcspn(code, "\n")] = 0;

    for (int i = 0; i < couponCount; i++) {
        if (strcmp(coupons[i].code, code) == 0) {
            if (isCouponValid(coupons[i].expiryDate)) {
                discount = coupons[i].discount;
                break;
            }
        }
    }

    *totalPrice -= (*totalPrice * discount / 100);
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