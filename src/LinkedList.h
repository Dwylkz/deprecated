#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Info.h"
#include "Container.i"

#include "Object.h"
#include "ListNode.h"

#define LL_HEAD 1
#define LL_TAIL 0

Define(LinkedListD) {
  Info _;
  ContainerI Container_;
};
Define(LinkedList) {
  struct Object _;
  Obj root_;
};
extern Type LinkedList;

/* OK */  Func(Obj, LinkedListConstruct, va_list* _ptr_ap);
/* OK */  Func(Obj, LinkedListDestruct);
Func(dif_int, LinkedListIsEqual, Obj _that);
Func(dif_int, LinkedListIsGreater, Obj _that);
Func(void, LinkedListCopy, Obj _that);
/* OK */  Func(void, LinkedListClear);
/* OK */  Func(void, LinkedListInsert, ...);
Func(Obj, LinkedListSearch, ...);
Func(dif_size, LinkedListRank, ...);
/* OK */  Func(Obj, LinkedListSelect, ...);
/* OK */  Func(void, LinkedListDelete, ...);
/* OK */  Func(dif_size, LinkedListSize);
Func(Obj, LinkedListBegin);
Func(Obj, LinkedListEnd);
Func(Obj, LinkedListReverseBegin);
Func(Obj, LinkedListReverseEnd);
Func(Obj, LinkedListNext);
Func(Obj, LinkedListReverseNext);

#endif // LINKEDLIST_H_
