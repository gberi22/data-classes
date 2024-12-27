#include <pthread.h>
#include "stackelem.h"

/*
    MUTEX:
    pthread.h is ari da ase iwereba pthread_mutex_t
    ra muagmi aq amas ra semaporas ro viyenebdit gasagebistvis done an lock rasac erqva 
    semaporas mnishvneloba xo sheileba iyos >= 0 da mutexshi kide an 0 an 1\
    da gvaq 2 funqcia mutexsze
    pthread_mutex_lock(*) 1 --> 0; 0 --> waiting
    pthread_mutex_unlock(*) 0 --> 1; 1 --> program crash.

    aseve gvaq conditionebi: 
    pthread_cond_t 
    pthread_cond_wait --> dablokavs mimdinare bloks sanam rame signals ar miigebs
    pthread_cond_signal --> dablokili blokebidan ert erts gaagvdizebs
    pthread_cond_broadcast --> dablokili blokebidan yvelas gaagvidzebs
*/

/*
    Queue davwerot nakadebit
    Push -- adds new element to the queue
    Get -- takes one element from queue
            if queue is empty wait until there is at least one element
*/

typedef struct{
    Stack s;
    pthread_mutex_t lock; 
    pthread_cond_t cond; // signali vagzavnot add-dan get-shi
 }BlockingQueue;

void BlockingQueueInit(BlockingQueue* q, int elem_size, void (*free_fn)(void*));

void BlockingQueueDestroy(BlockingQueue* q);

void BlockingQueueAdd(BlockingQueue* q, void* value_ptr);

void BlockingQueueGet(BlockingQueue* q, void* value_ptr);