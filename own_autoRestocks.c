#include "inventory.h"

void autoRestock(struct Product products[], int productCount) {
    char productName[50];
    int quantity;
    char restockDay[10];
    char lastRestock[11];
    int found = 0;

    printf("Enter the product name: ");
    scanf("%s", productName);
    printf("Enter the quantity: ");
    scanf("%d", &quantity);
    printf("Enter the restock day (e.g., Monday): ");
    scanf("%s", restockDay);

    // Validate restock day
    if (!isValidDay(restockDay)) {
        printf("Invalid restock day! Aborting process.\n");
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

    // Get the current date
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(lastRestock, sizeof(lastRestock), "%Y-%m-%d", t);

    // Save the auto-restock details to autorestock.csv
    FILE *file = fopen("./csv/autorestock.csv", "a");
    if (file == NULL) {
        printf("Error opening autorestock file!\n");
        return;
    }

    fprintf(file, "%s,%d,%s,%s\n", productName, quantity, restockDay, lastRestock);
    fclose(file);

    printf("Auto-restock scheduled successfully!\n");
}

void performAutoRestocks(struct Product products[], int productCount, struct AutoRestock autoRestocks[], int autoRestockCount) {
    time_t now = time(NULL);
    struct tm *currentDate = localtime(&now);

    for (int i = 0; i < autoRestockCount; i++) {
        struct tm lastRestockDate;
        if (!custom_strptime(autoRestocks[i].lastRestock, &lastRestockDate)) {
            printf("Error parsing last restock date for %s\n", autoRestocks[i].productName);
            continue;
        }

        int daysDiff = daysBetween(&lastRestockDate, currentDate);
        int weeksDiff = daysDiff / 7;

        for (int w = 1; w <= weeksDiff; w++) {
            struct tm restockDate = lastRestockDate;
            restockDate.tm_mday += w * 7;
            mktime(&restockDate);

            if (isDayOfWeek(autoRestocks[i].restockDay, &restockDate)) {
                char productName[50];
                int quantity = autoRestocks[i].quantity;
                int found = 0;

                for (int j = 0; j < productCount; j++) {
                    if (strcmp(products[j].name, autoRestocks[i].productName) == 0) {
                        products[j].stock += quantity;
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Product %s not found!\n", autoRestocks[i].productName);
                    return;
                }

                // Log the restock
                char restockDateStr[11];
                strftime(restockDateStr, sizeof(restockDateStr), "%Y-%m-%d", &restockDate);
                logRestock(products, productCount, autoRestocks[i].productName, quantity);

                // Update last restock date
                strcpy(autoRestocks[i].lastRestock, restockDateStr);

                printf("Auto-restock for %s on %s completed successfully! Quantity: %d\n", autoRestocks[i].productName, restockDateStr, quantity);
            }
        }
    }

    // Save updated auto-restock details
    saveAutoRestocks(autoRestocks, autoRestockCount);
}

void viewAutoRestocks(struct AutoRestock autoRestocks[], int autoRestockCount) {
    printf("\n=== Auto-Restock Schedules ===\n");
    for (int i = 0; i < autoRestockCount; i++) {
        printf("Product Name: %s\n", autoRestocks[i].productName);
        printf("Quantity: %d\n", autoRestocks[i].quantity);
        printf("Restock Day: %s\n", autoRestocks[i].restockDay);
        printf("Last Restock: %s\n", autoRestocks[i].lastRestock);
        printf("-----------------------------\n");
    }
}