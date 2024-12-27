#include "sorted_multi_set.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void SortedMultiSetInit(SortedMultiSet* set, size_t elem_size, CmpFn cmp_fn, FreeFn free_fn){
    set->alloc_len = 4;
    set->cmp = cmp_fn;
    set->elem_size = elem_size + sizeof(int);
    set->elemSizekeeper = elem_size;
    set->free = free_fn;
    set->log_len = 0;
    set->data = malloc(set->alloc_len*set->elem_size);
}

void SortedMultiSetDestroy(SortedMultiSet* set){
    for (int i=0; i<set->log_len; i++){
        void* val = (char*)set->data + i*(set->elem_size);
        if(set->free != NULL){
            set->free(val);
        }
    }
    free(set->data);
}

void SortedMultiSetInsert(SortedMultiSet* set, void* elem){
    for(int i=0; i<set->log_len; i++){
        void* curr = (char*)set->data + set->elem_size*i;
        // find if we have that elem already count++
        if(set->cmp(curr, elem) == 0){
            void* counts = (char*)curr + set->elemSizekeeper;
            if(set->free != NULL) set->free(elem);
            (*(int*)counts)++;
            return;
        }
        if(set->alloc_len == set->log_len){
            set->alloc_len *= 2;
            set->data = realloc(set->data, set->alloc_len*set->elem_size);
        }
        // place it on its right place.
        if(set->cmp(curr, elem) > 0){
            memmove((char*)set->data + (i+1)*(set->elem_size), (char*)set->data + i*set->elem_size, 
                                            (set->log_len - i)*set->elem_size);
            memcpy((char*)set->data + i*set->elem_size, elem, set->elemSizekeeper);
            void* newcounter = (char*)set->data + i*set->elem_size + set->elemSizekeeper;
            *(int*)newcounter = 1;
            memcpy((char*)set->data + i*set->elem_size + set->elemSizekeeper, newcounter, sizeof(int));
            set->log_len++;
            return;
        }
    }
    memcpy((char*)set->data + set->log_len*set->elem_size, elem, set->elemSizekeeper);
    void* newcounter = (char*)set->data + set->log_len*set->elem_size + set->elemSizekeeper;
    *(int*)newcounter = 1;
    memcpy((char*)set->data + set->log_len*set->elem_size + set->elemSizekeeper, newcounter, sizeof(int));
    set->log_len++;
}

void SortedMultiSetRemove(SortedMultiSet* set, void* elem){
    for(int i=0; i<set->log_len; i++){
        void* curr = (char*)set->data + set->elem_size*i;
        // find if we have that elem already count-- and if count = 0 thyan remove it
        if(set->cmp(curr, elem) == 0){
            void* count = (char*)curr + set->elemSizekeeper;
            (*(int*)count)--;
            if((*(int*)count) == 0){
                // imena remove unda vqna mtlinai elementis znachit.
                if(set->free != NULL) set->free(curr);
                memmove(curr, (char*)curr + set->elem_size, (set->log_len - i - 1)*set->elem_size);
                set->log_len--;
            }
        }
    }
   
}

void* SortedMultiSetGet(SortedMultiSet* set, int index){
    return (char*)set->data + index*set->elem_size;
}

int SortedMultiSetGetCount(SortedMultiSet* set, int index){
    void* ragac = (char*)set->data + index*set->elem_size + set->elemSizekeeper;
    int ans = *(int*)ragac;
    return ans;
}

int SortedMultiSetSize(SortedMultiSet* set){
    return set->log_len;
}

