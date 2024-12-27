#include "student_buffer.h"

#include <stdlib.h>
#include <string.h>

#include "circular_buffer.h"

void FreeStudent(void* ptr) {
  Student* tmp = ptr;
  free(tmp->name);
}

int CmpStudent(void* a, void* b) {
  Student* s1 = (Student*)a;
  Student* s2 = (Student*)b;
  if(strcmp(s1->name, s2->name) == 0){
    return s1->gpa - s2->gpa;
  }
  return strcmp(s1->name, s2->name);
}

// ამ ხაზის ქვემოთ ცვლილებების უფლება არ გაქვთ

void StudentBufferInit(StudentBuffer* sb, int capacity) {
  CircularBufferInit(sb, sizeof(Student), capacity, FreeStudent, CmpStudent);
}

void StudentBufferDestroy(StudentBuffer* sb) {
  CircularBufferDestroy(sb);
}

void StudentBufferPush(StudentBuffer* sb, Student* student) {
  CircularBufferPush(sb, student);
}

void StudentBufferPop(StudentBuffer* sb, Student* student) {
  CircularBufferPush(sb, student);
}

int StudentBufferCount(StudentBuffer* sb, Student* student) {
  return CircularBufferCount(sb, student);
}

