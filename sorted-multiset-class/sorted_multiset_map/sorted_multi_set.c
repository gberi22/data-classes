#include "sorted_multi_set.h"
#include "vector.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void VectorFree(void* elem){
  VectorItem* item = (VectorItem*)elem;
  if(item->free_fn != NULL) item->free_fn(item->elem); 
  free(item->elem);
}


void SortedMultiSetInit(SortedMultiSet *s, int elem_size, CmpFn cmp_fn,
                        FreeFn free_fn) {
  s->elem_size = elem_size;
  s->cmp_fn = cmp_fn;
  s->free_fn = free_fn;
  VectorInit(&s->v, sizeof(VectorItem), VectorFree);                        
}

void SortedMultiSetDestroy(SortedMultiSet *s) {
  VectorDestroy(&s->v);
}

typedef struct{
  int index;
  CmpFn cmp_fn;
  bool found_match;
  void* user_elem;
}AddAux;

void map_add(int index, void* elem, void* aux){
  AddAux* auxA = (AddAux*)aux;
  VectorItem* item = (VectorItem*)elem;
  int comp = auxA->cmp_fn(auxA->user_elem, item->elem);
  if(comp == 0){
    auxA->found_match = true;
    item->count++;
    auxA->index = index;
  }else if((comp < 0) && (auxA->index == -1)){
    auxA->index = index;
  }
}

int SortedMultiSetInsert(SortedMultiSet *s, void *elem) {
  AddAux aux_add;
  aux_add.cmp_fn = s->cmp_fn;
  aux_add.user_elem = elem;
  aux_add.index = -1;
  aux_add.found_match = false;
  VectorMap(&s->v, map_add, &aux_add);
  if(aux_add.found_match == true){
    return aux_add.index;
  }
  if(aux_add.index == -1){
    aux_add.index = VectorSize(&s->v);
  }
  VectorItem item;
  item.count = 1;
  item.free_fn = s->free_fn;
  item.elem = malloc(s->elem_size);
  memcpy(item.elem, elem, s->elem_size);
  VectorInsert(&s->v, aux_add.index, &item);
  return aux_add.index;
}

typedef struct{
  int index;
  void* elem;
}GetAux;

void map_get(int index, void* elem, void* aux){
  GetAux* auxG = (GetAux*)aux;
  VectorItem* item = (VectorItem*)elem;
  if(auxG->index == index){
    auxG->elem = item->elem;
  }
}

void *SortedMultiSetGet(SortedMultiSet *s, int index) {
  GetAux aux_get;
  aux_get.index = index;
  aux_get.elem = NULL;
  VectorMap(&s->v, map_get, &aux_get);
  return aux_get.elem;
}

typedef struct{
  int counter;
  CmpFn cmp;
  void* elem;
}CountAux;

void map_count(int index, void* elem, void* aux){
  CountAux* auxG = (CountAux*)aux;
  VectorItem* item = elem;
  int comp = auxG->cmp(item->elem, auxG->elem);
  if(comp == 0){
    auxG->counter = item->count;
  }
}

int SortedMultiSetGetCount(SortedMultiSet *s, void *elem) {
  CountAux aux_count;
  aux_count.counter = 0;
  aux_count.cmp = s->cmp_fn; 
  aux_count.elem = elem;
  VectorMap(&s->v, map_count, &aux_count);
  return aux_count.counter;
}
