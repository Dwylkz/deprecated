#ifndef PAIR_H_
#define PAIR_H_

#include "Info.h"
#include "PairType.i"

#include "Object.h"

Define(PairD) {
  Info _;
  PairTypeI PairType_;
};
Define(Pair) {
  struct Object _;
  Obj first_,
      second_;
};
extern Type Pair;

/* OK */  Func(Obj, PairConstruct, va_list* _ptr_ap);
/* OK */  Func(Obj, PairDestruct);
/* OK */  Func(dif_int, PairIsEqual, Obj _that);
/* OK */  Func(dif_int, PairIsGreater, Obj _that);
/* OK */  Func(void, PairCopy, Obj _that);
/* OK */  
/* OK */  Func(void, PairSet_first, Obj _first);
/* OK */  Func(Obj, PairGet_first);
/* OK */  Func(void, PairSet_second, Obj _second);
/* OK */  Func(Obj, PairGet_second);

#endif // PAIR_H_
