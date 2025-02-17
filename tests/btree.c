#include "../include/collections/btree.h"
#include <stdio.h>

typedef struct {
    char* id;
} User;

const char* userIdentifier(void* user) {
    return ((User*)user)->id;
}

int main() {
    BTree* bt = newBTree(userIdentifier);

    User user1 = { .id = "user1" };
    BTree_push(bt, &user1);

    printf("%d\n", BTree_contains(bt, "user1"));

    return 0;
}
