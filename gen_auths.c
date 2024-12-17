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

int usernameExists(struct User users[], int userCount, const char* username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}