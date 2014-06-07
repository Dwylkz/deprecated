#ifndef CONTAINER_I_
#define CONTAINER_I_

#include "Basic.i"

Interface {
  Method
    SetM(Clear),
    SetM(Insert),
    SetM(Search),
    SetM(Rank),
    SetM(Select),
    SetM(Delete),
    SetM(Size),
    SetM(Begin),
    SetM(End),
    SetM(ReverseBegin),
    SetM(ReverseEnd),
    SetM(Next),
    SetM(ReverseNext);
} ContainerI;
SetT(void, Clear);
SetT(void, Insert, ...);
SetT(Obj, Search, ...);
SetT(dif_size, Rank, ...);
SetT(Obj, Select, ...);
SetT(void, Delete, ...);
SetT(dif_size, Size);
SetT(Obj, Begin);
SetT(Obj, End);
SetT(Obj, ReverseBegin);
SetT(Obj, ReverseEnd);
SetT(Obj, Next, Obj _iterator);
SetT(Obj, ReverseNext, Obj _iterator);

#endif // CONTAINER_I_
