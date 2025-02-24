#include "../../include/collections/heap.h"
#include "../testutils/collections.h"


int main() {
    Heap *h = Heap_new(Collectable_ordering, Collectable_drop);

    Heap_insert(h, Collectable_new("4"));
    Heap_insert(h, Collectable_new("3"));
    Heap_insert(h, Collectable_new("1"));
    Heap_insert(h, Collectable_new("2"));
}
