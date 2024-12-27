#include "circular_buffer.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void CircularBufferInit(CircularBuffer* cb, int elem_size, int capacity, FreeFn free_fn, CmpFn cmp_fn) {
  // IMPLEMENT
  cb->capacity = capacity;
  cb->elem_size = elem_size;
  cb->free = free_fn;
  cb->cmp = cmp_fn;
  cb->data = malloc(capacity*cb->elem_size);
  cb->log_len = 0;
}

void CircularBufferDestroy(CircularBuffer* cb) {
  if(cb->free != NULL){
    for(int i=0; i<cb->log_len; i++){
      cb->free(cb->data + i*cb->elem_size);
    }
  }
  free(cb->data);
}
// 3 4 5
void CircularBufferPush(CircularBuffer* cb, void* value) {
  if(cb->log_len != cb->capacity){
    memcpy(cb->data + cb->elem_size*cb->log_len, value, cb->elem_size);
    cb->log_len++;
  }else{
    if(cb->free != NULL) cb->free(cb->data);
    memmove(cb->data, cb->data + cb->elem_size, (cb->log_len - 1)*cb->elem_size);
    memcpy(cb->data + cb->elem_size*(cb->log_len-1), value, cb->elem_size);
  }
}

void CircularBufferPop(CircularBuffer* cb, void* value) {
  if(cb->log_len != 0){
    memcpy(value, cb->data, cb->elem_size);
    // if(cb->free != NULL) cb->free(cb->data);
    memmove(cb->data, cb->data + cb->elem_size, (cb->log_len - 1)*cb->elem_size);
    cb->log_len--;
  }
}

int CircularBufferCount(CircularBuffer* cb, void* value) {
  int counter = 0;
  for(int i=0; i<cb->log_len; i++){
    if(cb->cmp(cb->data + i*cb->elem_size, value) == 0){
      counter++;
    }
  }
  return counter;
}
