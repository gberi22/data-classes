# SortedMultiSet  

**SortedMultiSet** is a generic, dynamic data structure implemented in C, designed for managing elements in a sorted order. This structure allows duplicate elements and efficiently tracks their counts. It is built using the existing **Vector** data structure, providing flexibility and simplicity for memory management and dynamic resizing.  

---
## Implementation 
   There is two type of implementation.
1. **Generic Implementation**  
  - All functionality, such as sorting, resizing, and count management, is manually implemented.  

2. **Using Maps**  
  - This alternative solution uses an existing **map-like data structure** to manage the elements and their counts.  

## Features  

- **Sorted Storage**: Elements are maintained in ascending order based on the user-provided comparison function.  
- **Duplicate Elements Support**: Allows multiple instances of the same element.  
- **Count Tracking**: Tracks how many times each element is added to the multiset.  
- **Index-Based Access**: Provides efficient access to elements via index.  
- **Custom Cleanup Functions**: Supports user-defined cleanup logic for freeing memory used by elements.  

---

## API Documentation  

### Initialization and Cleanup  

- **`void SortedMultiSetInit(SortedMultiSet* set, int elem_size, CmpFn cmp_fn, FreeFn free_fn)`**  
  Initializes the **SortedMultiSet**.  
  - **`elem_size`**: Specifies the size of each element in bytes.  
  - **`cmp_fn`**: Function for comparing elements. Should return:  
    - `0` if elements are equal,  
    - Negative if the first element is smaller,  
    - Positive if the first element is larger.  
  - **`free_fn`**: Optional cleanup function for freeing the memory used by elements.  

- **`void SortedMultiSetDestroy(SortedMultiSet* set)`**  
  Frees all memory used by the multiset, including memory allocated for elements.  

---

### Core Operations  

- **`void SortedMultiSetInsert(SortedMultiSet* set, void* elem)`**  
  Inserts an element into the multiset. If the element already exists, its count is incremented. Ownership of the passed element is transferred to the multiset.  

- **`void* SortedMultiSetGet(SortedMultiSet* set, int index)`**  
  Retrieves the element at the specified index.  

- **`int SortedMultiSetGetCount(SortedMultiSet* set, void* elem)`**  
  Returns the count of the specified element in the multiset.  

---