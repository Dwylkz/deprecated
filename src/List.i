#ifndef LIST_I_
#define LIST_I_

#include "Basic.i"

typedef Interface {
  Method
    SetM(Clear),
    SetM(Push),
    SetM(Pop),
    SetM(Top),
    SetM(Size);
} ListI;

SetT(void, Clear);
SetT(void, Push, Obj element_);
SetT(void, Pop);
SetT(Obj, Top);
SetT(dif_size, Size);

#endif // LIST_I_
