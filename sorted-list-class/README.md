# SortedList Implementation

This project implements a **SortedList** data structure in C, designed for efficiently managing key-value pairs. 
The list maintains its elements in sorted order based on the keys, allowing for fast insertion, retrieval, 
and deletion of elements. It is a highly flexible structure that supports custom key comparison and memory 
cleanup through user-defined function pointers.


## Description

### Initialization and Destruction
- **SortedListInit**: Initializes the sorted list with specified key and value sizes, a comparison function, and optional cleanup functions for keys and values.
- **SortedListDestroy**: Frees all memory allocated for the list, including keys and values.

### Core Operations
- **SortedListAdd**: Adds a new key-value pair to the list. If the key already exists, updates its associated value.
- **SortedListRemove**: Removes the key-value pair associated with a given key. Returns `true` if the element was found and removed, otherwise `false`.
- **SortedListGet**: Retrieves the value associated with a given key. Returns `NULL` if the key does not exist.

### Helper Functions
- **findElem**: Internal helper function that searches for an element in the list by key and returns its index or `-1` if not found.
- **SortedListRealloc**: Resizes the list when its capacity is exceeded, doubling the allocated memory.
