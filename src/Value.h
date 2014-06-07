#ifndef VALUE_H_
#define VALUE_H_

#include "Info.h"
#include "Object.h"

Define(ValueD) {
  Info _;
  BasicI Basic_;
  BasicTypeI BasicType_;
};
Define(Value) {
  struct Object _;
  dif_int val_;
};
extern Type Value;

/* OK */  Func(Obj, ValueConstruct, va_list* _ptr_ap);
/* OK */  Func(Obj, ValueDestruct);
/* OK */  Func(dif_int, ValueIsEqual, Obj _that);
/* OK */  Func(dif_int, ValueIsGreater, Obj _that);
/* OK */  Func(void, ValueCopy, Obj _that);
/* OK */  Func(void, ValueSet_val, dif_int _val);
/* OK */  Func(dif_int, ValueGet_val);
/* OK */  Func(void, ValueInc_val, dif_int _val);
/* OK */  Func(void, ValueDec_val, dif_int _val);
/* OK */  Func(void, ValueAssign, Obj _that);

extern const Obj Nil;

// Global Temp Value;
Obj temp_value;

#endif // VALUE_H_
