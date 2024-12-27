	Task is to implement the generic PackedHashSet structure described above, which will allow us to store information of different 
sizes in it. The structure is heterogeneous, it can store different types of data at the same time, for example, an integer, a real 
number, a string or any other variable type.
	The only requirement that the PackedHashSet structure has is that the hashing function passed to it returns different hash values
​​for different information. That is, it considers that if the hash values ​​of two data items match, then these data items are equal 
to each other.

	Adding elements to it is done by calling the PackedHashSetInsert function, which is passed a pointer to the data along with the 
size of the data itself in bytes. If information with the same hash value already exists in the set, then the PackedHashSetInsert 
function should return false, otherwise it should add a new element to the list and return true.

PackedHashSet.base should be used to store the elements added to the set in order, and PackedHashSet.elem_offsets to remember which 
	element starts at how many bytes from the PackedHashSet.base pointer. PackedHashSet.elem_hashes can be used to store the hash values 
	​​of the elements added to the set.

PackedHashSetGet should return the starting address in memory of the element with the passed index.

PackedHashSetFind should return the memory address of the passed element if it was found in the set, and NULL otherwise.

PackedHashSetSortByHash should sort the elements stored in the set in ascending order of their hashed values.

PackedHashSetInit is used to initialize the set, and PackedHashSetDispose is used to free the memory it uses. Note the free_fn 
	helper function passed to PackedHashSetInit, which must be called for the address of each element stored in the set when freeing it.


Using the PackedHashSet structure, you should also implement the TupleHashSet structure, which will allow us to store the CharPair 
	and CharTripple types described above in a tuple. Where CharPair allows us to store two single-byte data items, and CharTripple allows 
	us to store three single-byte information items.

