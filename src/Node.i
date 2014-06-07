#ifndef NODE_I_
#define NODE_I_

#include "Basic.i"

Interface {
  Method
    SetM(Set_next),
    SetM(Get_next),
    SetM(Set_data),
    SetM(Get_data);
} NodeI;
SetT(void, Set_next, Obj _next, dif_size _index);
SetT(Obj, Get_next, dif_size _index);
SetT(void, Set_data, Obj _data);
SetT(Obj, Get_data);

#endif // NODE_I_
