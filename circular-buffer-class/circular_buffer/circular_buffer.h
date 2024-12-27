#ifndef PARADIGMS_PROBLEMS_CIRCULAR_BUFFER_CIRCULAR_BUFFER_H_
#define PARADIGMS_PROBLEMS_CIRCULAR_BUFFER_CIRCULAR_BUFFER_H_

typedef void(*FreeFn)(void*);
typedef int(*CmpFn)(void*, void*);

typedef struct {
  // აქ დაამატეთ საჭირო ცვლადები
  int elem_size;
  int capacity;
  FreeFn free;
  CmpFn cmp;
  void* data;
  int log_len;
} CircularBuffer;

// ამ ხაზის ქვემოთ ცვლილების უფლება არ გაქვთ

void CircularBufferInit(CircularBuffer* cb, int elem_size, int capacity, FreeFn free_fn, CmpFn cmp_fn);
void CircularBufferDestroy(CircularBuffer* cb);
void CircularBufferPush(CircularBuffer* cb, void* value);
void CircularBufferPop(CircularBuffer* cb, void* value);
int CircularBufferCount(CircularBuffer* cb, void* value);

#endif // PARADIGMS_PROBLEMS_CIRCULAR_BUFFER_CIRCULAR_BUFFER_H_
