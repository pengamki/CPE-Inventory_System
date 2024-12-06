#include "inventory.h"
#include <stdio.h>

static void listProducts_all(void);
static void listProducts_byname(char *prefix);
static void listProducts_bydesc(char *desc);
static void listProducts_byprice(float floor, float ceil);

void  viewProducts(void)
{
  // 0: exit, 1: all, 2: byname, 3: bydesc, 4: byprice
  int choice;
  char *prefix;
  char *desc;
  float floor;
  float ceil;

  while (1)
  {
    printf("\n==View Products==\n");
    printf("1. View All Products\n");
    printf("2. Filter by Name\n"); // input prefix
    printf("3. Filter by Description\n"); // input desc
    printf("4. Filter by Price\n"); // input floor, ceil
    printf("0. Exit\n");
    printf("Please select your role: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        listProducts_all();
        break;
      case 2:
        // scanning and validating inputs
        scanf("%s", prefix);
        

        listProducts_byname(prefix);
        break;
      case 3:
        // scanning and validating inputs
        scanf("%s", desc);

        listProducts_bydesc(desc);
        break;
      case 4:
        // scanning and validating inputs
        scanf("%f", floor);
        scanf("%f", ceil);

        break;
      case 0:
        printf("Exiting the Customer menu...\n");
        usleep(500000);
        return ;
      default:
        printf("Invalid choice. Please try again.\n");
        usleep(500000);
        break;
    }
  }
  return ;
}
