#include "../../include/collections/bstree.h"
#include "../testutils/rand.h"
#include "../testutils/collections.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main() {
    struct bstree *bt = bstree_new(test_collectable_ordering,
                                   test_collectable_identify,
                                   test_collectable_drop);
    
    srand(time(NULL));
    char **identifiers = gen_identifiers(16);
    char **same_identifiers = calloc(sizeof(char *), 16);

    for (int i = 0; i < 16; i++) {
         same_identifiers[i] = calloc(24, 1);
         memcpy(same_identifiers[i], identifiers[i], 24);
    }

    printf("test: bstree_push\n");
    for(int i = 0; i < 16; i++)
        assert(bstree_push(bt, test_collectable_new(identifiers[i])));

    printf("test: bstree_contains\n");
    for(int i = 0; i < 16; i++) 
        assert(bstree_contains(bt, identifiers[i]));

    printf("test: bstree_remove\n");
    for(int i = 0; i < 16; i++)
        assert(bstree_remove(bt, identifiers[i]));

    printf("test: bstree_contains after removing tree's elements\n");
    for(int i = 0; i < 16; i++) 
        assert(!bstree_contains(bt, same_identifiers[i]));

    printf("test: bstree_push using the same identifiers as previous push\n");
    for(int i = 0; i < 16; i++)
        assert(bstree_push(bt, test_collectable_new(same_identifiers[i])));

    printf("test: bstree_drop and reinitializing anohter tree with the same "
           "identifiers\n");
    bstree_drop(bt);
    bt = bstree_new(test_collectable_ordering,
                    test_collectable_identify,
                    test_collectable_drop);
    for(int i = 0; i < 16; i++)
        assert(bstree_push(bt, test_collectable_new(same_identifiers[i])));

    printf("test: Check if new the reinitialized tree contains identifiers\n");
    for(int i = 0; i < 16; i++) 
        assert(bstree_contains(bt, identifiers[i]));

    printf("test: bstree_clear\n");
    bstree_clear(bt);

    return 0;
}
