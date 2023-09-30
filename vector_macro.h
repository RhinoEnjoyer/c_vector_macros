#ifndef VECTOR_MACROS_DEF
#define VECTOR_MACROS_DEF

#include <malloc.h>
#include <memory.h>
#include <sys/types.h>

#define vec(T) vec_##T
#define vALLOC(T,v,s) vec_##T##_alloc(v,s)
#define vREALLOC(T,v,s) vec_##T##_realloc(v,s)
#define vDEALLOC(T,v) vec_##T##_dealloc(v)
#define vINIT(T,v,s) vec_##T##_init(v,s)
#define vCOPY(T,this,other) vec_##T##_copy(this,other)
#define vPUSH(T,v,va) vec_##T##_push(v,va)


#define __VECTOR_DEF(T)\
typedef struct _vec_##T\
{\
 T* ptr;\
 size_t count;\
 size_t capacity;\
} vec_##T;\
\
\
\
\
static void vec_##T##_alloc(vec_##T* v ,size_t s)\
{ v->ptr = (T*)malloc(s*sizeof(T)); v->capacity = s; }\
\
static void vec_##T##_dealloc(vec_##T* v)\
{\
    if(v->ptr)\
    {\
        free(v->ptr);\
        v->ptr = NULL;\
        v->count = 0;\
        v->capacity = 0;\
    }\
}\
\
static void vec_##T##_realloc(vec_##T* v , size_t s)\
{\
    if( v->ptr && v->capacity != s && v->capacity != 0) v->ptr = (T*)realloc(v->ptr,s*sizeof(T));\
    else vALLOC(T,v,s);\
    v->capacity = s;\
}\
\
static void vec_##T##_copy(vec_##T* t,vec_##T* o)\
{\
   t->count     = o->count;\
   t->capacity  = o->capacity;\
   vREALLOC(T ,t ,o->count);\
   memcpy(t->ptr ,o->ptr ,sizeof(T)*o->count);\
}\
\
static void vec_##T##_move(vec_##T* t,vec_##T* o)\
{\
   t->count     = o->count;\
   t->capacity  = o->capacity;\
   vREALLOC(T ,t ,o->count);\
   t->ptr = o->ptr;\
   o->ptr = NULL;\
}\
\
static void vec_##T##_init(vec_##T* v ,size_t s)\
{\
    vALLOC(T,v,s);\
    v->count = 0;\
}\
\
static void vec_##T##_empty(vec_##T* v)\
{\
    v->ptr = NULL;\
    v->count = 0;\
    v->capacity = 0;\
}\
\
static void vec_##T##_push(vec_##T* v,T value)\
{\
    if(v->count == v->capacity) {vREALLOC(T,v,v->capacity*2);}\
    \
    v->ptr[v->count] = value;\
    v->count++;\
}\
\

#define VECTOR_DEF_PRIMITIVES()\
__VECTOR_DEF(float);\
__VECTOR_DEF(int);\
__VECTOR_DEF(u_int);\
__VECTOR_DEF(size_t);\




VECTOR_DEF_PRIMITIVES();


#endif
