#include <search.h>
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static const int defaultSize = 4;
void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation){
    assert(elemSize >= 1);
    assert(initialAllocation >= 0);
    v->elemSize = elemSize;
    v->free = freeFn;
    if(initialAllocation == 0) initialAllocation = defaultSize;
    v->vecSize = initialAllocation;
    v->vec = malloc((v->elemSize)*(v->vecSize));
    assert(v->vec != NULL);
    v->sizeNow = 0;
}

void VectorDispose(vector *v){
    if(v->free == NULL){
        free(v->vec);
        return;
    }
    
    for(int i=0; i<v->sizeNow; i++){
        v->free((char*)v->vec + i*(v->elemSize));
    }
    free(v->vec);
}

int VectorLength(const vector *v){
    return v->sizeNow; 
}

void *VectorNth(const vector *v, int position){
    assert(position >= 0 && position <= v->sizeNow - 1);
    return (char*)v->vec + (v->elemSize)*position;
}

void VectorReplace(vector *v, const void *elemAddr, int position){
    assert(elemAddr != NULL);
    assert(position >= 0 && position <= v->sizeNow - 1);
    if(v->free != NULL) v->free((char*)v->vec + (v->elemSize)*position);
    memcpy((char*)v->vec + (v->elemSize)*position, elemAddr, v->elemSize);
}

static const int toGrow = 2;
void grow(vector *v){
    v->vecSize *= toGrow;
    v->vec = realloc(v->vec, (v->vecSize)*(v->elemSize));
    assert(v->vec != NULL);
}

void VectorInsert(vector *v, const void *elemAddr, int position){
    assert(position >= 0 && position <= v->sizeNow);
    assert(elemAddr != NULL);
    if(v->vecSize == v->sizeNow) grow(v);
    for(int i = v->sizeNow-1; i >= position; i--){
        memmove((char*)v->vec + (i+1)*(v->elemSize), 
                (char*)v->vec + i*(v->elemSize), v->elemSize);
    }
    memcpy((char*)v->vec + position*(v->elemSize), elemAddr, v->elemSize);
    v->sizeNow++;
}

void VectorAppend(vector *v, const void *elemAddr){
    VectorInsert(v, elemAddr, v->sizeNow);
}

void VectorDelete(vector *v, int position){
    assert(position >= 0 && position <= v->sizeNow-1);
    if(v->free != NULL){
        v->free((char*)v->vec + v->elemSize*position);
    }
    for(int i=position+1; i<v->sizeNow; i++){
        memmove((char*)v->vec + (i-1)*v->elemSize, (char*)v->vec + i*v->elemSize, v->elemSize);
    }
    v->sizeNow--;
}
    
void VectorSort(vector *v, VectorCompareFunction compare){
    assert(compare != NULL);
    qsort(v->vec, v->sizeNow, v->elemSize, compare);
}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData){
    assert(mapFn != NULL);
    for(int i=0; i<v->sizeNow; i++){
        mapFn((char*)v->vec + v->elemSize*i, auxData);
    }
}


static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted){
    assert(startIndex >= 0 && startIndex <= v->sizeNow);
    assert(searchFn != NULL);
    assert(key != NULL);
    void* searched = NULL;
    if(isSorted){
        searched = bsearch(key, (char*)v->vec + v->elemSize*startIndex, v->sizeNow-startIndex, v->elemSize, searchFn);
    }else{
        size_t s = v->sizeNow - startIndex;
        searched = lfind(key, (char*)v->vec + v->elemSize*startIndex, &s, v->elemSize, searchFn);
    }
    if(searched == NULL) return kNotFound;
    return ((char*)searched - (char*)v->vec)/v->elemSize; 
}


 
