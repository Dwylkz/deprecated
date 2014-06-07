#ifndef DAC_H_
#define DAC_H_

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include "assert.h"

#define dac_int int
#define dac_char char

#define Max(x, y) ((x) > (y)? (x): (y))
#define Min(x, y) ((x) < (y)? (x): (y))

typedef void *(*CRI)(void*);
typedef dac_int (*CompareI)(void*, void*);
typedef dac_int (*HashFunctionI)(void*);

typedef struct Type {
  CompareI eq_,
           gt_;
  CRI   cp_,
        rm_;
  HashFunctionI hf_;
} Type;

dac_int IntEqual(void *self, void *that);

dac_int IntGreater(void *self, void *that);

void *IntCopy(void *self);

void *IntRemove(void *self);

extern Type *IntT;

dac_int StringEqual(void *self, void *that);

dac_int StringGreater(void *self, void *that);

void *StringCopy(void *self);

void *StringRemove(void *self);

extern Type *StringT;

dac_int AddrEqual(void *self, void *that);

dac_int AddrGreater(void *self, void *that);

void *AddrCopy(void *self);

void *AddrRemove(void *self);

extern Type *AddrT;

#endif // DAC_H_
