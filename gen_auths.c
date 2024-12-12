#include "inventory.h"

int authenticateUser(struct User users[], int userCount, const char* username, const char* password, int isOwner) {
    for(int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && 
            strcmp(users[i].password, password) == 0 && 
            users[i].isOwner == isOwner) {
            return 1;
        }
    }
    return 0;
}

void registerUser(const char* username, const char* password, int isOwner) {
    FILE *file = fopen("./csv/users.csv", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%s,%s,%d\n", username, password, isOwner);
    fclose(file);
}