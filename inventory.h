#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCTS 100
#define MAX_LINE 256
#define MAX_USERS 100
#define MAX_COUPONS 100
#define MAX_AUTOPURCHASES 100
#define MAX_AUTORESTOCKS 100

struct Product {
    char name[50];
    char description[100];
    float price;
    int stock;
};

struct Coupon {
    char code[20];
    float discount;
    char expiryDate[11]; // Format: YYYY-MM-DD
};

struct User {
    char username[50];
    char password[50];
    int isOwner;  // 1: owner, 0: customer
};

struct AutoPurchase {
    char productName[50];
    int quantity;
    char couponCode[20];
    char purchaseDay[10]; // Day of the week (e.g., Monday)
    char lastPurchase[11]; // Format: YYYY-MM-DD
};

struct AutoRestock {
    char productName[50];
    int quantity;
    char restockDay[10]; // Day of the week (e.g., Monday)
    char lastRestock[11]; // Format: YYYY-MM-DD
};

// !!General functions!!
// Loads functions
void loadProductsFromCSV(struct Product products[], int *productCount);
void loadUsers(struct User users[], int *userCount);
void loadCoupons(struct Coupon coupons[], int *couponCount);
void loadAutoPurchases(struct AutoPurchase autoPurchases[], int *autoPurchaseCount);
void loadAutoRestocks(struct AutoRestock autoRestocks[], int *autoRestockCount);
// Saves functions
void saveProductsToCSV(struct Product products[], int productCount);
void saveCouponsToCSV(struct Coupon coupons[], int couponCount);
void saveAutoPurchases(struct AutoPurchase autoPurchases[], int autoPurchaseCount);
void saveAutoRestocks(struct AutoRestock autoRestocks[], int autoRestockCount);
// Logging functions
void logRestock(struct Product products[], int productCount, char* productName, int quantity);
void logPurchase(char* productName, int quantity, float totalPrice, float discount, char* couponCode);
// Sorting functions
void sortProducts(struct Product products[], int productCount);
void sortCoupons(struct Coupon coupons[], int couponCount);
// Authentication functions
int authenticateUser(struct User users[], int userCount, const char* username, const char* password, int isOwner);
void registerUser(const char* username, const char* password, int isOwner);
// Auto functions utiities
int isValidDay(const char* day);
int isDayOfWeek(const char* day, struct tm *date);
int daysBetween(struct tm *start, struct tm *end);
int custom_strptime(const char *date_str, struct tm *tm);


// !!Customer functions!!
// View Products
void viewProducts(struct Product products[], int productCount); // Parent function
void viewAllProducts(struct Product products[], int productCount);
void viewByName(struct Product products[], int productCount);
void viewByDescription(struct Product products[], int productCount);
void viewByPrice(struct Product products[], int productCount);
// Purchase Product
void purchaseProducts(struct Product products[], int productCount, struct Coupon coupons[], int couponCount); // Parent function
void purchaseProduct(struct Product products[], int productCount, struct Coupon coupons[], int couponCount);
int isCouponValid(const char* expirationDate);
// Purchase : Auto Purchase
void autoPurchase(struct Product products[], int productCount, struct Coupon coupons[], int couponCount);
void performAutoPurchases(struct Product products[], int productCount, struct Coupon coupons[], int couponCount, struct AutoPurchase autoPurchases[], int autoPurchaseCount);
void viewAutoPurchases(struct AutoPurchase autoPurchases[], int autoPurchaseCount);


// !!Owner functions!!
// View Reports
void viewReports(struct Product products[], int productCount); // Parent function
void viewPurchaseReport(struct Product products[], int productCount);
void viewStockReport(struct Product products[], int productCount);
// Edit Products
void editProducts(struct Product products[], int productCount); // Parent function
void addProduct(struct Product products[], int *productCount);
void removeProduct(struct Product products[], int *productCount);
void editProduct(struct Product products[], int productCount);
// Restock Products
void restockProducts(struct Product products[], int productCount); // Parent function
void restockProduct(struct Product products[], int productCount);
// Restock : Auto Restock
void autoRestock(struct Product products[], int productCount);
void performAutoRestocks(struct Product products[], int productCount, struct AutoRestock autoRestocks[], int autoRestockCount);
void viewAutoRestocks(struct AutoRestock autoRestocks[], int autoRestockCount);

// Edit Coupons
void editCoupons(struct Coupon coupons[], int couponCount); // Parent function
void viewCoupons(struct Coupon coupons[], int couponCount);
void addCoupon(struct Coupon coupons[], int *couponCount);
void removeCoupon(struct Coupon coupons[], int *couponCount);
void applyCoupon(struct Coupon coupons[], int couponCount, float *totalPrice);

#endif