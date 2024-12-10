#include "inventory.h"

#define USERS_FILE "./csv/users.csv"
#define MAX_USERS 100

struct User users[MAX_USERS];
int userCount = 0;

// Simple encoding function (XOR with a fixed key - very basic, not for production use)
void encodePassword(char* password) {
    const char key = 'K';
    for(int i = 0; password[i] != '\0'; i++) {
        password[i] = password[i] ^ key;
    }
}

void loadUsers() {
    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        printf("No users file found. Creating default owner account...\n");
        FILE *newFile = fopen(USERS_FILE, "w");
        if (newFile != NULL) {
            char defaultPass[] = "admin123";
            encodePassword(defaultPass);
            fprintf(newFile, "admin,%s,1\n", defaultPass);
            fclose(newFile);
        }
        return;
    }
    
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, file) && userCount < MAX_USERS) {
        char *token = strtok(line, ",");
        strcpy(users[userCount].username, token);
        
        token = strtok(NULL, ",");
        strcpy(users[userCount].password, token);
        
        token = strtok(NULL, ",");
        users[userCount].isOwner = atoi(token);
        
        userCount++;
    }
    fclose(file);
}

int authenticateUser(const char* username, const char* password, int isOwner) {
    char encodedPass[50];
    strcpy(encodedPass, password);
    encodePassword(encodedPass);
    
    for(int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && 
            strcmp(users[i].password, encodedPass) == 0 && 
            users[i].isOwner == isOwner) {
            return 1;  // Authentication successful
        }
    }
    return 0;  // Authentication failed
}