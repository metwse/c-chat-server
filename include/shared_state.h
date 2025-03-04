/*!
 * Shared state.
 */

#ifndef SHARED_STATE
#define SHARED_STATE

#include <pthread.h>
#include "collections/linked_list.h"
#include "collections/bstree.h"


/**
 * Server database.
 */
struct shared_state { 
    pthread_mutex_t lock; 
    struct bstree *channels;
    struct bstree *users;
};

struct shared_state *initialize_shared_state();

#endif
