#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LAST_ELEM_START(s) ((char*)(s)->elems + (s)->last_elem_offset)
#define LAST_ELEM_SIZE(s) (*((int*)LAST_ELEM_START((s)-1))) // -1 imitoro wina elementshi am elementis zoma gvaq damaxsovrebuli
#define LAST_ELEM_END(s) ((char*)LAST_ELEM_START((s)) + LAST_ELEM_SIZE((s)))

void StackInit(Stack* s){
    s->last_elem_offset = -1;
    s->alloc_bytes = 100;
    s->elems = malloc(s->alloc_bytes);
    assert(s->elems != NULL);
}

void StackDispose(Stack* s){
    free(s->elems);
}

void StackPush(Stack* s, void* elem, int elem_size){
    while(true){
        int remaining_bytes = s->alloc_bytes;
        if(s->last_elem_offset != -1){
            remaining_bytes -= (char*)LAST_ELEM_END(s) - (char*)s->elems;
        }
        if(remaining_bytes >= elem_size + 2*sizeof(int)){ //2*sizeof(int) imitoro elemis ukan vinaxavt intad ramxela zomisaa da magis ukan mimtitebels wina elementis
            break;
        }
        s->alloc_bytes *= 2;
        s->elems = realloc(s->elems, s->alloc_bytes);
        assert(s->elems != NULL);
    }
    // exla vitvlit tu sad unda chavwerot axali elementi. 
    void* last_elem_end = s->elems;
    if(s->last_elem_offset != -1){
        last_elem_end = LAST_ELEM_END(s);
    }
    *(int*)last_elem_end = s->last_elem_offset; // aq vwert mimtitebels bolo elementis.
    *((int*)last_elem_end + 1) = elem_size; // bolo elemebtis mimtiteblis mere vwert ra zomis elementia
    s->last_elem_offset = (char*)last_elem_end + 2*sizeof(int) - (char*)s->elems;
    memcpy(LAST_ELEM_START(s), elem, elem_size);
}



void* StackPop(Stack* s){
    assert(s->last_elem_offset != -1);
    void* ret = malloc(LAST_ELEM_SIZE(s));
    assert(ret != NULL);
    memcpy(ret, LAST_ELEM_START(s), LAST_ELEM_SIZE(s));
    s->last_elem_offset = *((int*)LAST_ELEM_START(s) - 2); //offsetis ganaxleba -2 it gadavdivart misamartze wina elementis
    return ret;
}