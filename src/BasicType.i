#ifndef BASICTYPE_I_
#define BASICTYPE_I_

#include "Basic.i"

#define DIFInt udif_int32_t

Interface BasicType {
  Method
    SetM(Set_val),
    SetM(Get_val),
    SetM(Inc_val),
    SetM(Dec_val),
    SetM(Assign);
} BasicTypeI;

SetT(void, Set_val, dif_int _val);
SetT(dif_int, Get_val);
SetT(void, Inc_val, dif_int _val);
SetT(void, Dec_val, dif_int _val);
SetT(void, Assign, Obj _that);

#endif // BASICTYPE_I_
