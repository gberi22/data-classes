Array2D - ჯენერიკები

The task is divided into two parts. In the first part, you need to implement a two-dimensional array.
In the second part you need to implement a two dimensional array StrArray2D, which is specialized for strings.


Array2D:

void Array2DInit(Array2D* arr, int n, int m, int elem_size, FreeFn free_fn) - n denotes the number of rows, m the number of columns, 
    elem_size the size in bytes of each array element, and a pointer to the free_fn function that should be called if necessary to 
    free the memory used by the array elements.

void Array2DDestroy(Array2D* arr) - must free memory used by array.

int Array2DN(Array2D* arr) - must return quantity of rows in array.

int Array2DM(Array2D* arr) - must return quantity of columns in array.

void Array2DSet(Array2D* arr, int i, int j, void* value) - he element (i, j) of the array must contain the element whose value starts 
    at the address value. The array takes ownership of the value of the passed element.

const void* Array2DGet(Array2D* arr, int i, int j) - Should return the address of the element at position (i, j) in the array.

void Array2DRemove(Array2D* arr, int i, int j) - The element at position (i, j) should be "deleted" from the array only if an element 
    was already written at that position. Deletion means that the array should remember that nothing is written at that position anymore.

void Array2DIterate(Array2D* arr, int x, int y, int w, int z, IterFn iter_fn, void* aux) - For each element in the array from position (x, y) to 
    position (w, z) inclusive, the iter_fn function must be called. Each time iter_fn is called, the following arguments must be passed to the function: aux , the additional information provided, a pointer to the current element in the array, and its coordinates. 
    ** Note the word written in the previous sentence.**


void Array2DGrow(Array2D* arr, int n, int m) - Must increase the array. The new size of the passed array will always be greater than or
    equal to the old size, i.e. n >= arr->n && m >= arr->m


StrArray2D:

void StrArray2DInit(StrArray2D* arr, int n, int m) - Must initialize the passed string array.

void StrArray2DDestroy(StrArray2D* arr) - Must free the memory used by the string array.

void StrArray2DSet(StrArray2D* arr, int i, int j, char* str) - It should write the passed string at position (i, j) of the array,
which it takes ownership of.

const char* StrArray2DGet(StrArray2D* arr, int i, int j) - Should return the string at position (i, j) in the array.
    bool StrArray2DRemove(StrArray2D* arr, const char* str) - It should find and delete the given string in the array, if it exists. The search should be done in ascending order of the lines, from left to right. That is, first, all elements should be checked from left to right on the first line, then on the second line, and so on. It should return true if such an element was found and deleted, and false otherwise. In the implementation of this function, you can only declare variables, call only the Array2DIterate function and return a response. You are not allowed to use if/else, for/while constructs.