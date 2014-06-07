#ifndef LISTNDOE_H_
#define LISTNDOE_H_

#include "Info.h"
#include "Node.i"
#include "Object.h"

Define(ListNodeD) {
  Info _;
  NodeI Node_;
};
Define(ListNode) {
  struct Object _;
  Obj *to_,
      data_;
};

extern Type ListNode;
/* OK */  Func(Obj, ListNodeConstruct, va_list* _ptr_ap);
/* OK */  Func(Obj, ListNodeDestruct);
/* OK */  Func(dif_int, ListNodeIsEqual, Obj _that);
/* OK */  Func(dif_int, ListNodeIsGreater, Obj _that);
/* OK */  Func(void, ListNodeCopy, Obj _that);
/* OK */  Func(void, ListNodeSet_next, Obj _next, dif_size _index);
/* OK */  Func(Obj, ListNodeGet_next, dif_size _index);
/* OK */  Func(void, ListNodeSet_data, Obj _data);
/* OK */  Func(Obj, ListNodeGet_data);

#endif // LISTNDOE_H_
