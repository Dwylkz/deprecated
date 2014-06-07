#ifndef ARRAY_H_
#define ARRAY_H_

#include "dac.h"

typedef struct Array {
  Type *datat_;
  dac_int size_,
          datan_;
  void **data_;
} Array;
extern Type *ArrayT;

Array *ArrayNew(Type *i_datat);

dac_int ArrayEqual(void *_this, void *_that);

dac_int ArrayGreater(void *_this, void *_that);

void *ArrayCopy(void *self);

void *ArrayRemove(void *self);

// void ArrayResize(Array *self, dac_int i_size);

void ArrayClear(Array *self);

void ArrayPush(Array *self, void *i_data);

void ArrayPop(Array *self);

void *ArrayGet(Array *self, dac_int i_idx);

void ArraySet(Array *self, dac_int i_idx, void* i_data);

dac_int ArraySize(Array *self);

void ArrayCat(Array *self, Array *that);

#endif // ARRAY_H_
