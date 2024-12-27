#ifndef STACK_H_
#define STACK_H_

typedef struct {
  void *elems;
  int elem_size;
  int log_len;
  int alloc_len;
  void (*free_fn)(void *);
} Stack;

// Initializes given stack.
void StackInit(Stack *s, int elem_size, void (*free_fn)(void *));

// Frees up memory used by the given stack.
void StackDispose(Stack *s);

// Pushes new element into the stack.
// Takes ownerhip of given value pointer.
void StackPush(Stack *s, void *value_ptr);

// Pops most recently pushed element from the stack.
// Gives ownership back to the caller.
void StackPop(Stack *s, void *value_ptr);

#endif // STACK_H_