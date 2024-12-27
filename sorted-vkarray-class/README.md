void SortedKVArrayInit(SortedKVArray* a, int key_size, int value_size, CompareFn key_cmp_fn, FreeFn key_free_fn, FreeFn value_free_fn); -- The passed array must be initialized.

void SortedKVArrayDestroy(SortedKVArray* a); -- It should free up the dynamic memory used by the array.

void SortedKVArrayAdd(SortedKVArray* a, void *key, void *value); -- Should add the given (key, value) pair to an array. If
    the given key already exists in the array, then the current value associated with it should be deleted and the new value should be written in its place. Takes ownership of both the key and value addresses.


bool SortedKVArrayRemove(SortedKVArray* a, void *key); -- It should extract the given key and its associated value from the array. 
    It should return true if the key is found, false otherwise. It does not take ownership of key addresses.

int SortedKVArraySize(SortedKVArray* a); -- must return size of array

void* SortedKVArrayGetKey(SortedKVArray* a, int index); -- Should return the key stored at the given index.
    Does not transfer ownership to the caller.

void* SortedKVArrayGetValue(SortedKVArray* a, void *key); -- Should return a pointer to the value associated with the given key. NULL if 
    no such key is found. Does not take ownership of key addresses. Ownership of the returned address remains with the used SortedKVArray object.