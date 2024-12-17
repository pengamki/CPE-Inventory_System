#include "inventory.h"
#include <limits.h>

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
        printf("1. View Purchases Report\n");
        printf("2. Filter Sales by Product Name\n");
        printf("3. Filter Sales by Price Range\n");
        printf("4. Summarize Today's Report\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &reportChoice);

        system("cls");
        switch(reportChoice) {
            case 1:
                viewSalesReport(purchaseLogs, purchaseLogCount);
                break;
            case 2:
                filterSalesByProductName(purchaseLogs, purchaseLogCount);
                break;
            case 3:
                filterSalesByPriceRange(purchaseLogs, purchaseLogCount);
                break;
            case 4:
                viewDailySummaryReport(purchaseLogs, purchaseLogCount, products);
                break;
            case 0:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while (reportChoice != 0);
}

void viewSalesReport(struct PurchaseLog purchaseLogs[], int purchaseLogCount) {
    printf("\n=== Sales Report ===\n");
    printf("%-20s %-10s %-10s %-10s %-10s\n", "Product", "Quantity", "Total Price", "Discount", "Coupon Code");
    for (int i = 0; i < purchaseLogCount; i++) {
        printf("%-20s %-10d $%-9.2f %-10.2f %-10s\n", purchaseLogs[i].productName, purchaseLogs[i].quantity, purchaseLogs[i].totalPrice, purchaseLogs[i].discount, purchaseLogs[i].couponCode);
    }
}

void filterSalesByProductName(struct PurchaseLog purchaseLogs[], int purchaseLogCount) {
    char productName[50];

    while (getchar() != '\n');    
    printf("Enter the product name to filter: ");
    fgets(productName, sizeof(productName), stdin);
    productName[strcspn(productName, "\n")] = 0;

    printf("\n=== Sales for Product: %s ===\n", productName);
    for (int i = 0; i < purchaseLogCount; i++) {
        if (strcmp(purchaseLogs[i].productName, productName) == 0) {
            printf("Date: %s, Quantity: %d, Total Price: %.2f, Discount: %.2f, Coupon Code: %s\n",
                   purchaseLogs[i].dateTime, purchaseLogs[i].quantity, purchaseLogs[i].totalPrice,
                   purchaseLogs[i].discount, purchaseLogs[i].couponCode);
        }
    }
}

void filterSalesByPriceRange(struct PurchaseLog purchaseLogs[], int purchaseLogCount) {
    float minPrice, maxPrice;
    printf("Enter the minimum price: ");
    scanf("%f", &minPrice);
    printf("Enter the maximum price: ");
    scanf("%f", &maxPrice);

    printf("\n=== Sales within Price Range: %.2f - %.2f ===\n", minPrice, maxPrice);
    for (int i = 0; i < purchaseLogCount; i++) {
        if (purchaseLogs[i].totalPrice >= minPrice && purchaseLogs[i].totalPrice <= maxPrice) {
            printf("Date: %s, Product: %s, Quantity: %d, Total Price: %.2f, Discount: %.2f, Coupon Code: %s\n",
                   purchaseLogs[i].dateTime, purchaseLogs[i].productName, purchaseLogs[i].quantity,
                   purchaseLogs[i].totalPrice, purchaseLogs[i].discount, purchaseLogs[i].couponCode);
        }
    }
}

void viewDailySummaryReport(struct PurchaseLog purchaseLogs[], int purchaseLogCount, struct Product products[]) {
    int totalSales = 0;
    float totalIncome = 0.0;
    char mostSoldProduct[50] = "";
    int mostSoldQuantity = 0;
    char leastSoldProduct[50] = "";
    int leastSoldQuantity = INT_MAX;
    int productSales[MAX_PRODUCTS] = {0};
    float productIncome[MAX_PRODUCTS] = {0.0};
    int productCount = 0;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char today[11];
    strftime(today, sizeof(today), "%Y-%m-%d", t);

    for (int i = 0; i < purchaseLogCount; i++) {
        if (strncmp(purchaseLogs[i].dateTime, today, 10) == 0) {
            totalSales += purchaseLogs[i].quantity;
            totalIncome += purchaseLogs[i].totalPrice;

            int found = 0;
            for (int j = 0; j < productCount; j++) {
                if (strcmp(purchaseLogs[i].productName, products[j].name) == 0) {
                    productSales[j] += purchaseLogs[i].quantity;
                    productIncome[j] += purchaseLogs[i].totalPrice;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                strcpy(products[productCount].name, purchaseLogs[i].productName);
                productSales[productCount] = purchaseLogs[i].quantity;
                productIncome[productCount] = purchaseLogs[i].totalPrice;
                productCount++;
            }
        }
    }

    for (int i = 0; i < productCount; i++) {
        if (productSales[i] > mostSoldQuantity) {
            mostSoldQuantity = productSales[i];
            strcpy(mostSoldProduct, products[i].name);
        }
        if (productSales[i] < leastSoldQuantity) {
            leastSoldQuantity = productSales[i];
            strcpy(leastSoldProduct, products[i].name);
        }
    }

    printf("\n=== Daily Summary Report ===\n");
    printf("Total Sales: %d\n", totalSales);
    printf("Total Income: %.2f\n", totalIncome);
    printf("Most Sold Product: %s (%d units)\n", mostSoldProduct, mostSoldQuantity);
    printf("Least Sold Product: %s (%d units)\n", leastSoldProduct, leastSoldQuantity);
    printf("Average Sales per Product: %.2f\n", (float)totalSales / productCount);

    saveReportSummary(today, totalSales, totalIncome, mostSoldProduct, mostSoldQuantity, leastSoldProduct, leastSoldQuantity);
}