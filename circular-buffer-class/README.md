CircularBuffer

void CircularBufferInit(CircularBuffer* cb, int elem_size, int capacity, FreeFn free_fn, CmpFn cmp_fn); - Initialization
    should be performed on the passed CircularBuffer object. It takes as arguments the size of the elements,
    the capacity (i.e. how many elements it can hold), and the functions for freeing and comparing the elements.

void CircularBufferDestroy(CircularBuffer* cb); - Must free the memory used by the passed buffer.

void CircularBufferPush(CircularBuffer* cb, void* value); - A new element should be added to the buffer from the end.
    The buffer should take ownership of the added element. If the buffer is already full, then the new element
    should overwrite the first element in the buffer. See the detailed explanation below.

void CircularBufferPop(CircularBuffer* cb, void* value); - It should remove the first element from the buffer and copy its value to 
    the passed value address. It transfers ownership of the removed value to the client.

int CircularBufferCount(CircularBuffer* cb, void* value); - It is necessary to count how many times the element with the given 
    value appears in the buffer.

When adding a new element to a buffer, if the buffer is already full, then the first element of the buffer is replaced by the new value, and the second element should be considered the first element of the buffer. For example, if a 3-element buffer is full and starting from the first position it contains 1, 2, 3, then by adding another element (push) to it, the buffer should store 4, 2, 3. And after that, if we perform the Pop operation, we should return 2 and in the case of another Pop, 3.
StudentBuffer

StudentBuffer has similar functions to CircularBuffer, tailored to handle objects of type Student. You only need to 
    implement the following two functions:

void FreeStudent(void* ptr); - Must free the memory used by the student stored at the given address.

int CmpStudent(void* a, void* b); - Should compare the Student objects at the two given addresses. When comparing, you 
    should consider both the student's name and his/her GPA. If the two Student objects are equal, you should return 0,
    a negative number if the first is less than the second, and a positive number otherwise.
