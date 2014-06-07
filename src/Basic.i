#ifndef BASIC_I_
#define BASIC_I_

#include "dif.h"
#include "BasicType.i"

Interface {
  Method
    SetM(Construct),
    SetM(Destruct),
    SetM(IsEqual),
    SetM(IsGreater),
    SetM(Copy);
} BasicI;
SetT(Obj, Construct, va_list* _ptr_ap);
SetT(Obj, Destruct);
SetT(dif_int, IsEqual, Obj _that);
SetT(dif_int, IsGreater, Obj _that);
SetT(void, Copy, Obj _that);

#endif // BASIC_I_
