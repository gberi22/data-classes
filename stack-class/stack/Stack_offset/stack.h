#ifndef HETEROGENEOUS_STACK_STACK_H_
#define HETEROGENEOUS_STACK_STACK_H_

// its a stack where every elem has diff elem_size 

typedef struct{
    void* elems;
    int alloc_bytes; // how many bytes we have
    int last_elem_offset; // sxvaobas inaxavs pirvel da bolo elements shoris
}Stack;

void StackInit(Stack* s);
void StackDispose(Stack* s);
void StackPush(Stack* s, void* elem, int elem_size);
void* StackPop(Stack* s);

#endif