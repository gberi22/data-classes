#include "2darr.h"

#include <stdlib.h>
#include <string.h>

static void strfree(void* ptr){
  free(*(char**)ptr);
}

void StrArray2DInit(Array2D* arr, int n, int m) {
  Array2DInit(arr, n, m, sizeof(char*), strfree);
}

void StrArray2DDestroy(Array2D* arr) {
  Array2DDestroy(arr);
}

void StrArray2DSet(Array2D* arr, int i, int j, char* str) {
  Array2DSet(arr, i, j, &str);
}

const char* StrArray2DGet(Array2D* arr, int i, int j) {
  return *(char**)Array2DGet(arr, i, j);
}

typedef struct{
  bool if_found;
  const char* elem;
  Array2D* arr; 
}Aux;

void iterfn(void* aux, const void* elem, int i, int j){
  Aux* auxD = (Aux*)aux;
  if(auxD->if_found) return;
  int comp = strcmp(auxD->elem, *(char**)elem);
  if(comp == 0) {
    auxD->if_found = true;
    Array2DRemove(auxD->arr, i, j);
  }
}

bool StrArray2DRemove(Array2D* arr, const char* str) {
  // IMPLEMENT
  // მხოლოდ შეგიძლიათ აღწეროთ ლოკალური ცვლადები,
  // გამოიძახოთ Array2DIterate ფუნქცია და დააბრუნოთ მნიშვნელობა.
  Aux aux;
  aux.arr = arr;
  aux.if_found = false;
  aux.elem = str;
  Array2DIterate(arr, 0, 0, Array2DN(arr) - 1, Array2DM(arr) - 1, iterfn, &aux);
  return aux.if_found;
}