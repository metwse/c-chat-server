#include "../../include/collections/linkedlist.h"
#include "../testutils/collections.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    LinkedList *ll = LinkedList_new(Collectable_identify, Collectable_drop);

    char **identifiers = calloc((sizeof(char *)), 16);

    printf("test: push\n");
    for (int i = 0; i < 16; i++) {
        char *id = (char *) malloc(3 * sizeof(char));
        snprintf(id, 3, "%d", i);
        identifiers[i] = id;

        LinkedList_push(ll, Collectable_new(id));
    }
    
    printf("test: get\n");
    assert(!strcmp(((Collectable *) LinkedList_get(ll, 0))->id, "0"));
    assert(!strcmp(((Collectable *) LinkedList_get(ll, 15))->id, "15"));
    assert(!strcmp(((Collectable *) LinkedList_getById(ll, "7"))->id, "7"));

    printf("test: remove\n");
    LinkedList_remove(ll, 0);
    LinkedList_removeById(ll, "2");

    printf("test: delete\n");
    LinkedList_delete(ll, 0);
    LinkedList_deleteById(ll, "3");


    printf("test: get after removing and deleting\n");
    assert(!strcmp(((Collectable *) LinkedList_get(ll, 0))->id, "4"));
    assert(!strcmp(((Collectable *) LinkedList_get(ll, 11))->id, "15"));
    assert(LinkedList_get(ll, 14) == NULL);
    assert(!strcmp(((Collectable *) LinkedList_getById(ll, "8"))->id, "8"));

    printf("test: unshift\n");
    for (int i = 0; i < 4; i++) {
        char *id = (char *) malloc(3 * sizeof(char));
        snprintf(id, 11, "unshift %d", i);

        LinkedList_unshift(ll, Collectable_new(id));
    }

    printf("test: get after unshifting\n");
    assert(!strcmp(((Collectable *) LinkedList_get(ll, 0))->id, "unshift 3"));

    printf("test: drop\n");
    LinkedList_drop(ll);

    printf("test: reinitializing a linkedlist using previously dropped list's elements\n");
    ll = LinkedList_new(Collectable_identify, Collectable_drop);

    identifiers[1] = (char *) malloc(sizeof(char) * 3);
    identifiers[3] = (char *) malloc(sizeof(char) * 3);
    strcpy(identifiers[1], "1");
    strcpy(identifiers[3], "3");

    for (int i = 0; i < 16; i++) LinkedList_push(ll, Collectable_new(identifiers[i]));

    assert(!strcmp(Collectable_identify(((Collectable *) LinkedList_get(ll, 0))), "0"));

    printf("test: clear\n");
    LinkedList_clear(ll);

    return 0;
}
