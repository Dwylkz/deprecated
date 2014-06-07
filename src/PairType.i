#ifndef PAIRTYPE_I_
#define PAIRTYPE_I_

Interface {
  Method
    SetM(Set_first),
    SetM(Get_first),
    SetM(Set_second),
    SetM(Get_second);
} PairTypeI;
SetT(void, Set_first, Obj _first);
SetT(Obj, Get_first);
SetT(void, Set_second, Obj _second);
SetT(Obj, Get_second);

#endif // PAIRTYPE_I_
