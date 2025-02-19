#include "../include/collections/bstree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* id;
} User;

const char* userIdentifier(void* user) {
    return ((User*) user)->id;
}

void userRemover(void* instance) {
    free(((User*) instance)->id);
    free(instance);
}


void addUser(BSTree* bt, char* id) {
    User *user = malloc(sizeof(User));
    char *heapString = malloc(strlen(id) + 1);
    strcpy(heapString, id);
    user->id = heapString;
    
    BSTree_push(bt, user);
}

int main() {
    BSTree *bt = BSTree_new(userIdentifier, userRemover);


    addUser(bt, "user1");

    printf("%d\n", BSTree_contains(bt, "user1"));
    BSTree_remove(bt, "user1");
    addUser(bt, "user1");

    printf("%d\n", BSTree_contains(bt, "user1"));
    BSTree_remove(bt, "user1");


    return 0;
}
