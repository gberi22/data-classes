#include "hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void HashSetNew(hashset *h, int elemSize, int numBuckets,
		HashSetHashFunction hashfn, HashSetCompareFunction comparefn, HashSetFreeFunction freefn){
	assert(elemSize > 0);
	assert(numBuckets > 0);
	assert(hashfn != NULL);
	assert(comparefn != NULL);
	h->comp = comparefn;
	h->elemSize = elemSize;
	h->freeFun = freefn;
	h->hashFun = hashfn;
	h->numBuck = numBuckets;
	h->data = (vector*)malloc(sizeof(*h->data)*numBuckets); // bucketebistvis sheqmnili mexsiereba
	assert(h->data != NULL);
	// each buckets is each vector and we need to create whats inside with vectorNew.
	for(int i=0; i<h->numBuck; i++){
		VectorNew(&h->data[i], h->elemSize, h->freeFun, sizeof(*h->data));
	}
}

void HashSetDispose(hashset *h){
	assert(h->data != NULL);
	for(int i=0; i<h->numBuck; i++){
		VectorDispose(&h->data[i]);
	}
	free(h->data);
}

int HashSetCount(const hashset *h){
	assert(h->data != NULL);
	int counter = 0;
	for(int i=0; i<h->numBuck; i++){
		counter += (&h->data[i])->sizeNow;
	}
	return counter;
}

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData){
	assert(h->data != NULL);
	assert(mapfn != NULL);
	for(int i=0; i<h->numBuck; i++){
		VectorMap((&h->data[i]), mapfn, auxData);
	}
}

//----------------------------------------------------
static const int startInd = 0;
static const bool isSorted = false;
//----------------------------------------------------

void HashSetEnter(hashset *h, const void *elemAddr){
	assert(h->data != NULL);
	assert(elemAddr != NULL);
	int whichBuck = h->hashFun(elemAddr, h->numBuck);
	assert(whichBuck >= 0 && whichBuck <= h->numBuck - 1);
	int findIndex = VectorSearch(&h->data[whichBuck], elemAddr, h->comp, startInd, isSorted);
	if(findIndex >= 0)
		VectorReplace(&h->data[whichBuck], elemAddr, findIndex);
	else
		VectorAppend(&h->data[whichBuck], elemAddr);
}

void *HashSetLookup(const hashset *h, const void *elemAddr){
	assert(h->data != NULL);
	assert(elemAddr != NULL);
	int whichBuck = h->hashFun(elemAddr, h->numBuck);
	assert(whichBuck >= 0 && whichBuck <= h->numBuck - 1);
	int findIndex = VectorSearch(&h->data[whichBuck], elemAddr, h->comp, startInd, isSorted);
	if(findIndex == -1) return NULL;
	return (char*)(&h->data[whichBuck])->vec + findIndex*(&h->data[whichBuck])->elemSize;
}
