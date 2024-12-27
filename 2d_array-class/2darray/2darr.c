#include "2darr.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>



void Array2DInit(Array2D* arr, int n, int m, int elem_size, FreeFn free_fn) {
  arr->elem_size = elem_size;
  arr->w = m;
  arr->h = n;
  arr->free = free_fn;
  arr->data = malloc(arr->w*arr->h*arr->elem_size);
  assert(arr->data != NULL);
  arr->is_there = malloc(arr->w*arr->h*sizeof(bool));
  assert(arr->is_there != NULL);
  memset(arr->is_there, false, arr->w*arr->h*sizeof(bool));
}

void Array2DDestroy(Array2D* arr) {
  if(arr->free != NULL){
    for(int i=0; i<arr->h*arr->w; i++){
      if(*(arr->is_there + i*sizeof(bool))) arr->free((char*)arr->data + i*arr->elem_size);
    }
  }
  free(arr->data);
  free(arr->is_there);
}

int Array2DN(Array2D* arr) {
  return arr->h;
}

int Array2DM(Array2D* arr) {
  return arr->w;
}

void Array2DSet(Array2D* arr, int i, int j, void* value){
  if(*((char*)arr->is_there + (i*arr->w + j)*sizeof(bool)) == true){
    if(arr->free != NULL){
      arr->free((char*)arr->data + (i*arr->w + j)*arr->elem_size);
    }
  }
  memcpy((char*)arr->data + (i*arr->w + j)*arr->elem_size, value, arr->elem_size);
  *((char*)arr->is_there + (i*arr->w + j)*sizeof(bool)) = true;
}

const void* Array2DGet(Array2D* arr, int i, int j) {
  if(*((char*)arr->is_there + (i*arr->w + j)*sizeof(bool)) == false) return NULL;
  return (char*)arr->data + (arr->w*i + j)*arr->elem_size;
}

void Array2DRemove(Array2D* arr, int i, int j) {
  if(*((char*)arr->is_there + (i*arr->w + j)*sizeof(bool)) == false) return;
  if(arr->free != NULL){
    arr->free((char*)arr->data + (arr->w*i + j)*arr->elem_size);
  }
  *((char*)arr->is_there + (i*arr->w + j)*sizeof(bool)) = false;
}

void Array2DIterate(Array2D* arr, int x, int y, int w, int z, IterFn iter_fn, void* aux) {
  for(int i=x; i<=w; i++){
    for(int j=y; j<=z; j++){
      if(*((char*)arr->is_there + (i*arr->w+j)*sizeof(bool)) == true)
        iter_fn(aux, (char*)arr->data + (i*arr->w+j)*arr->elem_size, i, j);
    }
  }
}


void Array2DGrow(Array2D* arr, int n, int m) {
  void* negur = malloc(m*n*arr->elem_size);
  bool* niga = malloc(m*n*sizeof(bool));
  memset(niga, false, sizeof(bool));
  for(int i=0; i<arr->h; i++){
    for(int j=0; j<arr->w; j++){
      memcpy((char*)niga + (i*m + j), (char*)arr->is_there + (i*arr->w + j), sizeof(bool));
      memcpy((char*)negur + (i*m + j)*arr->elem_size, (char*)arr->data + (i*arr->w + j)*arr->elem_size, arr->elem_size);
    }
  }
  free(arr->data);
  free(arr->is_there);
  arr->is_there = niga;
  arr->data = negur;
  arr->w = m;
  arr->h = n;
}