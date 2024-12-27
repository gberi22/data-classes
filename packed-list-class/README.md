
    Your task is to implement the generic PackedList structure described above, which will allow us to store information of 
various sizes in it. The structure is heterogeneous, it can simultaneously store different types of data, for example, an 
integer, a real number, a string, or any other variable type.


Elements are added to it by calling the PackedListAppend function, which is passed a pointer to the data along with the 
size of the data itself in bytes.

PackedList.base should be used to store the elements added to the list in order, and PackedList.elem_offsets should 
    be used to remember which element starts at how many bytes from the PackedList.base pointer.

PackedListGet should return the starting address in memory of the element with the passed index.

PackedListSort should sort the elements stored in the list using the passed comparison function.

PackedListInit is used to initialize the list, and PackedListDispose is used to free the memory used by it. Note the free_fn 
    helper function passed to PackedListInit, which should be called for each element address stored in the list when freeing it.

Using the PackedList structure, you should also implement the IPList structure, which will allow us to store IPv4 and IPv6 
    data in the list. The definition of the fourth version of the IP address consists of four integers each in the range 0 .. 255, 
    while the sixth version address is a string.
