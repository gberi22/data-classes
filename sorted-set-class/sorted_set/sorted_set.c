#include "sorted_set.h"

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

void SortedSetInit(SortedSet* s, int elem_size, CmpFn cmp_fn, FreeFn free_fn) {
  // IMPLEMENT
  s->free_fn = free_fn;
  s->cmp_fn = cmp_fn;
  VectorInit(&s->v, elem_size, s->free_fn);
}

void SortedSetDestroy(SortedSet* s) {
  // IMPLEMENT
  VectorDestroy(&s->v);
}


int SortedSetInsert(SortedSet* s, void* elem) {
  // IMPLEMENT
  for(int i=0; i<s->v.log_len; i++){
    if(s->cmp_fn((char*)s->v.base + i*(s->v.elem_size), elem) == 0){
      return -1;
    }
    if(s->cmp_fn((char*)s->v.base + i*(s->v.elem_size), elem) > 0){
      VectorInsert(&s->v, i, elem);
      return i;
    }
  }
  VectorInsert(&s->v, s->v.log_len, elem);
  return s->v.log_len-1;
}


void* SortedSetGet(SortedSet* s, int index) {
  // IMPLEMENT
  return ((char*)s->v.base + index* (s->v.elem_size));
}

int SortedSetSize(SortedSet* s) {
  // IMPLEMENT
  return VectorSize(&s->v);
}