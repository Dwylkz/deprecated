#ifndef OBJECT_H_
#define OBJECT_H_

#include "Info.h"

#define MAGIC 0xdddccbbb

Define(ObjectD) {
  Info _;
};
Define(Object) {
  dif_int magic_;
  Type type_;
};
extern Type Object;

Func(Obj, ObjectConstruct, va_list *_ptr_ap);
Func(Obj, ObjectDestruct);
Func(dif_int, ObjectIsEqual, Obj _that);
Func(dif_int, ObjectIsGreater, Obj _that);
Func(void, ObjectCopy, Obj _that);

#endif // OBJECT_H_
