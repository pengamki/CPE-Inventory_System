#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100
#define MAX_LINE 256

struct Product {
    char name[50];
    char description[100];
    float price;
    int stock;
};

struct User {
    char username[50];
    char password[50];
    int isOwner;  // 1 for owner, 0 for customer
};

// Authentication functions
int authenticateUser(const char* username, const char* password, int isOwner);
void loadUsers();


// !!Customer functions!!

// View Products
void viewAllProducts(struct Product products[], int productCount);
void viewByName(struct Product products[], int productCount);
void viewByDescription(struct Product products[], int productCount);
void viewByPrice(struct Product products[], int productCount);

// Purchase Product



// !!Owner functions!!

// View Reports

// Edit Products

// Restock Products

// Edit Coupons

#endif