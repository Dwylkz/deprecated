#ifndef VECTOR_H_
#define VECTOR_H_

#include "Info.h"
#include "Container.i"
#include "Object.h"

Define(VectorD) {
  Info _;
  ContainerI Container_;
};
Define(Vector) {
 struct Object _;
 dif_size size_,
        current_size_;
 Obj* array_;
};
extern Type Vector;

/* OK */  Func(Obj, VectorConstruct, va_list* _ptr_ap);
/* OK */  Func(Obj, VectorDestruct);
/* OK */  Func(dif_int, VectorIsEqual, Obj _that);
Func(dif_int, VectorIsGreater, Obj _that);
/* OK */  Func(void, VectorCopy, Obj _that);
/* OK */  Func(void, VectorClear);
/* OK */  Func(void, VectorInsert, ...);
/* OK */  Func(Obj, VectorSearch, ...);
/* OK */  Func(dif_size, VectorRank, ...);
/* OK */  Func(Obj, VectorSelect, ...);
/* OK */  Func(void, VectorDelete, ...);
/* OK */  Func(dif_size, VectorSize);
Func(Obj, VectorBegin);
Func(Obj, VectorEnd);
Func(Obj, VectorReverseBegin);
Func(Obj, VectorReverseEnd);
Func(Obj, VectorNext, Obj _Iterator);
Func(Obj, VectorReverseNext, Obj _Iterator);

#endif // VECTOR_H_
