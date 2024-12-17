#include "inventory.h"

void setAutoRestock(struct Product products[], int productCount, struct AutoRestock autoRestocks[], int *autoRestockCount) {
    int choice;

    do {
        printf("\n=== Restock Products Menu ===\n");
        printf("1. View Auto-restock Schedule\n");
        printf("2. Add Auto-restock Schedule\n");
        printf("3. Remove Auto-restock Schedule\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        system("cls");
        switch(choice) {
            case 1:
                viewAutoRestocks(autoRestocks, *autoRestockCount);
                break;
            case 2:
                addAutoRestock(products, productCount, autoRestocks, autoRestockCount);
                break;
            case 3:
                removeAutoRestock(autoRestocks, autoRestockCount);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    } while(choice != 0);
}

void viewAutoRestocks(struct AutoRestock autoRestocks[], int autoRestockCount) {
    printf("\n=== Auto-Restock Schedule ===\n");
    printf("%-20s %-10s %-10s %-15s\n", "Product Name", "Quantity", "Restock Day", "Last Restock");
    for (int i = 0; i < autoRestockCount; i++) {
        printf("%-20s %-10d %-10s %-15s\n", 
            autoRestocks[i].productName, 
            autoRestocks[i].quantity, 
            autoRestocks[i].restockDay, 
            autoRestocks[i].lastRestock);
    }
}

void addAutoRestock(struct Product products[], int productCount, struct AutoRestock autoRestocks[], int *autoRestockCount) {
    char productName[50];
    int quantity;
    char restockDay[10];
    char lastRestock[11];
    int found = 0;

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

    printf("Enter the restock day (e.g., Monday): ");
    scanf("%s", restockDay);

    if (!isValidDay(restockDay)) {
        printf("Invalid restock day! Aborting process.\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(lastRestock, sizeof(lastRestock), "%Y-%m-%d", t);

    strcpy(autoRestocks[*autoRestockCount].productName, productName);
    autoRestocks[*autoRestockCount].quantity = quantity;
    strcpy(autoRestocks[*autoRestockCount].restockDay, restockDay);
    strcpy(autoRestocks[*autoRestockCount].lastRestock, lastRestock);
    (*autoRestockCount)++;

    saveAutoRestocks(autoRestocks, *autoRestockCount);
    printf("Auto-restock scheduled successfully!\n");
}

void removeAutoRestock(struct AutoRestock autoRestocks[], int *autoRestockCount) {
    char productName[50];
    int found = 0;

    while (getchar() != '\n');
    printf("Enter product name to remove: ");
    fgets(productName, sizeof(productName), stdin);
    productName[strcspn(productName, "\n")] = 0;

    for (int i = 0; i < *autoRestockCount; i++) {
        if (strcmp(autoRestocks[i].productName, productName) == 0) {
            for (int j = i; j < *autoRestockCount - 1; j++) {
                autoRestocks[j] = autoRestocks[j + 1];
            }
            (*autoRestockCount)--;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Auto-restock schedule removed!\n");
    } else {
        printf("Product not found!\n");
    }

    saveAutoRestocks(autoRestocks, *autoRestockCount);
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

                char restockDateStr[11];
                strftime(restockDateStr, sizeof(restockDateStr), "%Y-%m-%d", &restockDate);
                strcpy(autoRestocks[i].lastRestock, restockDateStr);

                logRestock(autoRestocks[i].productName, quantity, restockDateStr);
                printf("Auto-restock for %s on %s completed successfully! Quantity: %d\n", autoRestocks[i].productName, restockDateStr, quantity);
            }
        }
    }

    saveAutoRestocks(autoRestocks, autoRestockCount);
}