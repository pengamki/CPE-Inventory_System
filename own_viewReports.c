#include "inventory.h"

void viewReports(struct Product products[], int productCount) {
    int reportChoice;
    struct PurchaseLog purchaseLogs[MAX_PURCHASELOGS];
    int purchaseLogCount = 0;
    struct RestockLog restockLogs[MAX_RESTOCKLOGS];
    int restockLogCount = 0;
    
    loadPurchaseLogs(purchaseLogs, &purchaseLogCount);
    loadRestockLogs(restockLogs, &restockLogCount);
    do {
        printf("\n=== Reports Menu ===\n");
        printf("1. Daily Summary Report\n");
        printf("2. View Purchases Report\n");
        printf("3. View Stock Report\n");
        printf("4. Filter Sales by Product Name\n");
        printf("5. Filter Sales by Price Range\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &reportChoice);

        system("cls");
        switch(reportChoice) {
            // case 1:
            //     viewDailySummaryReport(purchaseLogs, purchaseLogCount);
            //     break;
            case 2:
                viewPurchasesReport(purchaseLogs, purchaseLogCount);
                break;
            case 3:
                viewStocksReport(products, productCount);
                break;
            // case 4:
            //     filterSalesByProductName(purchaseLogs, purchaseLogCount);
            //     break;
            // case 5:
            //     filterSalesByPriceRange(purchaseLogs, purchaseLogCount);
            //     break;
            case 0:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (reportChoice != 0);
}

// void viewDailySummaryReport(struct PurchaseLog purchaseLogs[], int purchaseLogCount) {
//     int totalSales = 0;
//     float totalIncome = 0.0;
//     char mostSoldProduct[50] = "";
//     int mostSoldQuantity = 0;
//     char leastSoldProduct[50] = "";
//     int leastSoldQuantity = INT_MAX;
//     int productSales[MAX_PRODUCTS] = {0};
//     float productIncome[MAX_PRODUCTS] = {0.0};
//     int productCount = 0;

//     time_t now = time(NULL);
//     struct tm *t = localtime(&now);
//     char today[11];
//     strftime(today, sizeof(today), "%Y-%m-%d", t);

//     for (int i = 0; i < purchaseLogCount; i++) {
//         if (strncmp(purchaseLogs[i].dateTime, today, 10) == 0) {
//             totalSales += purchaseLogs[i].quantity;
//             totalIncome += purchaseLogs[i].totalPrice;

//             int found = 0;
//             for (int j = 0; j < productCount; j++) {
//                 if (strcmp(purchaseLogs[i].productName, products[j].name) == 0) {
//                     productSales[j] += purchaseLogs[i].quantity;
//                     productIncome[j] += purchaseLogs[i].totalPrice;
//                     found = 1;
//                     break;
//                 }
//             }
//             if (!found) {
//                 strcpy(products[productCount].name, purchaseLogs[i].productName);
//                 productSales[productCount] = purchaseLogs[i].quantity;
//                 productIncome[productCount] = purchaseLogs[i].totalPrice;
//                 productCount++;
//             }
//         }
//     }

//     for (int i = 0; i < productCount; i++) {
//         if (productSales[i] > mostSoldQuantity) {
//             mostSoldQuantity = productSales[i];
//             strcpy(mostSoldProduct, products[i].name);
//         }
//         if (productSales[i] < leastSoldQuantity) {
//             leastSoldQuantity = productSales[i];
//             strcpy(leastSoldProduct, products[i].name);
//         }
//     }

//     printf("\n=== Daily Summary Report ===\n");
//     printf("Total Sales: %d\n", totalSales);
//     printf("Total Income: %.2f\n", totalIncome);
//     printf("Most Sold Product: %s (%d units)\n", mostSoldProduct, mostSoldQuantity);
//     printf("Least Sold Product: %s (%d units)\n", leastSoldProduct, leastSoldQuantity);
//     printf("Average Sales per Product: %.2f\n", (float)totalSales / productCount);
// }

void viewPurchasesReport(struct PurchaseLog purchaseLogs[], int purchaseLogCount) {
    printf("\n=== Purchase Report ===\n");
    printf("%-20s %-10s %-10s\n", "Name", "Quantity", "Total Price");
    for (int i = 0; i < purchaseLogCount; i++) {
        printf("%-20s %-10d $%-9.2f\n", purchaseLogs[i].productName, purchaseLogs[i].quantity, purchaseLogs[i].totalPrice);
    }
}

void viewStocksReport(struct Product products[], int productCount) {
    printf("\n=== Stock Report ===\n");
    printf("%-20s %-10s\n", "Name", "Stock");
    for (int i = 0; i < productCount; i++) {
        printf("%-20s %-10d\n", products[i].name, products[i].stock);
    }
}

// void filterSalesByProductName(struct PurchaseLog purchaseLogs[], int purchaseLogCount) {
//     char productName[50];
//     printf("Enter the product name to filter: ");
//     scanf("%s", productName);

//     printf("\n=== Sales for Product: %s ===\n", productName);
//     for (int i = 0; i < purchaseLogCount; i++) {
//         if (strcmp(purchaseLogs[i].productName, productName) == 0) {
//             printf("Date: %s, Quantity: %d, Total Price: %.2f, Discount: %.2f, Coupon Code: %s\n",
//                    purchaseLogs[i].dateTime, purchaseLogs[i].quantity, purchaseLogs[i].totalPrice,
//                    purchaseLogs[i].discount, purchaseLogs[i].couponCode);
//         }
//     }
// }

// void filterSalesByPriceRange(struct PurchaseLog purchaseLogs[], int purchaseLogCount) {
//     float minPrice, maxPrice;
//     printf("Enter the minimum price: ");
//     scanf("%f", &minPrice);
//     printf("Enter the maximum price: ");
//     scanf("%f", &maxPrice);

//     printf("\n=== Sales within Price Range: %.2f - %.2f ===\n", minPrice, maxPrice);
//     for (int i = 0; i < purchaseLogCount; i++) {
//         if (purchaseLogs[i].totalPrice >= minPrice && purchaseLogs[i].totalPrice <= maxPrice) {
//             printf("Date: %s, Product: %s, Quantity: %d, Total Price: %.2f, Discount: %.2f, Coupon Code: %s\n",
//                    purchaseLogs[i].dateTime, purchaseLogs[i].productName, purchaseLogs[i].quantity,
//                    purchaseLogs[i].totalPrice, purchaseLogs[i].discount, purchaseLogs[i].couponCode);
//         }
//     }
// }