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

    printf("testing: BSTree_push\n");
    for(int i = 0; i < 16; i++)
        assert(BSTree_push(bt, Collectable_new(identifiers[i])));

    printf("testing: BSTree_contains\n");
    for(int i = 0; i < 16; i++) 
        assert(BSTree_contains(bt, identifiers[i]));

    printf("testing: BSTree_remove\n");
    for(int i = 0; i < 16; i++)
        assert(BSTree_remove(bt, identifiers[i]));

    printf("testing: BSTree_contains after removing tree's elements\n");
    for(int i = 0; i < 16; i++) 
        assert(!BSTree_contains(bt, sameIdentifiers[i]));

    printf("testing: BSTree_push using the same identifiers as previous push\n");
    for(int i = 0; i < 16; i++)
        assert(BSTree_push(bt, Collectable_new(sameIdentifiers[i])));


    return 0;
}
