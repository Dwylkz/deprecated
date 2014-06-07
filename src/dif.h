#ifndef DIF_I_
#define DIF_I_

#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdarg.h"
#include "stdint.h"
#include "string.h"
#include "assert.h"

#define Interface typedef struct

// Protable Type
#define dif_int     int32_t
#define dif_size    uint32_t
#define dif_double  double
#define dif_char    char


// Handy macro

#define Go(this, method, ...) \
  (((method##Type*)Has((this), (Method)&method))((this),##__VA_ARGS__))

#define CastGo(type, this, method, ...) \
   temp_type = TypeOf((this));\
   ((PtrObject)(this))->type_ = type;\
   Go((this), method,##__VA_ARGS__);\
   ((PtrObject)(this))->type_ = temp_type

#define Define(type) \
  typedef struct type *Ptr##type;\
  typedef const struct type *LockedPtr##type;\
  struct type

#define SetM(method) method##ID_, method##_

#define SetID(method) method##Type method

#define PutM(type, method) (Method)&method, (Method)type##method

#define SetT(type, method, ...) \
  typedef type method##Type(Obj _this,##__VA_ARGS__);\
  const dif_int method

#define Func(type, method, ...) \
  type method(Obj _this,##__VA_ARGS__)

#define CopyArray(that, this, size) \
  (that) = malloc(size);\
  assert(that);\
  memcpy((that), (this), (size))

#define Lesser(this, that) \
  (!Equal(this, that) && !Greater(this, that))

#define LEqual(this, that) \
  (!Greater(this, that))

#define GEqual(this, that) \
  (!Lesser(this, that))

typedef void        *Obj,
                    *(*Method)();
typedef const void  *LockedObj,
                    *Type;

// Global temp variable
Type temp_type;
Obj temp_obj;

// Genric selector
dif_int IsObj(LockedObj _this);
LockedObj TypeOf(LockedObj _this);
dif_int TypeCheck(LockedObj _this, LockedObj _that);
Method Has(LockedObj _this, Method _method);
Obj New(Type _type, ...);
Obj Clone(Obj _this);
void Drop(Obj _this, ...);
dif_size SizeOf(LockedObj _this);
const dif_char* WhatIs(LockedObj _this);
dif_int Equal(LockedObj _this, LockedObj _that);
dif_int Greater(LockedObj _this, LockedObj _that);

#endif // DIF_H_
