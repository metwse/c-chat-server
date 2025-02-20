#include "../../include/collections/bstree.h"
#include "../testutils/rand.h"
#include "../testutils/collections.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main() {
    BSTree *bt = BSTree_new(Collectable_identify, Collectable_drop);
    
    srand(time(NULL));
    char **identifiers = gen_identifiers(16);
    char **sameIdentifiers = calloc(sizeof(char *), 16);

    for (int i = 0; i < 16; i++) {
         sameIdentifiers[i] = calloc(24, 1);
         memcpy(sameIdentifiers[i], identifiers[i], 24);
    }

    printf("test: BSTree_push\n");
    for(int i = 0; i < 16; i++)
        assert(BSTree_push(bt, Collectable_new(identifiers[i])));

    printf("test: BSTree_contains\n");
    for(int i = 0; i < 16; i++) 
        assert(BSTree_contains(bt, identifiers[i]));

    printf("test: BSTree_remove\n");
    for(int i = 0; i < 16; i++)
        assert(BSTree_remove(bt, identifiers[i]));

    printf("test: BSTree_contains after removing tree's elements\n");
    for(int i = 0; i < 16; i++) 
        assert(!BSTree_contains(bt, sameIdentifiers[i]));

    printf("test: BSTree_push using the same identifiers as previous push\n");
    for(int i = 0; i < 16; i++)
        assert(BSTree_push(bt, Collectable_new(sameIdentifiers[i])));

    printf("test: BSTree_drop and reinitializing anohter tree with the same identifiers\n");
    BSTree_drop(bt);
    bt = BSTree_new(Collectable_identify, Collectable_drop);
    for(int i = 0; i < 16; i++)
        assert(BSTree_push(bt, Collectable_new(sameIdentifiers[i])));

    printf("test: Check if new the reinitialized tree contains identifiers\n");
    for(int i = 0; i < 16; i++) 
        assert(BSTree_contains(bt, identifiers[i]));

    printf("test: BSTree_clear\n");
    BSTree_clear(bt);

    return 0;
}
