#include "../include/shared_state.h"
#include "../include/database.h"

#include <pthread.h>
#include <stdlib.h>


struct shared_state *initialize_shared_state() 
{
    struct shared_state *ss = malloc(sizeof(struct shared_state));

    ss->channels = bstree_new(channel_ordering, channel_identify, NULL);
    ss->users = bstree_new(user_ordering, user_identify, NULL);

    if (pthread_mutex_init(&ss->lock, NULL))
        return NULL;
    else 
        return ss;
}
