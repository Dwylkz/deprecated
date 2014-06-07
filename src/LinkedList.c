#include "LinkedList.h"
#include "Value.h"

Func(Obj, LinkedListConstruct, va_list* _ptr_ap)
{
  CastGo(Object, _this, Construct, _ptr_ap);
  PtrLinkedList this = _this;
  this->root_ = New(ListNode, 2, Nil);
  Go(this->root_, Set_next, this->root_, 0);
  Go(this->root_, Set_next, this->root_, 1);
  return this;
}

Func(Obj, LinkedListDestruct)
{
  PtrLinkedList this = _this;
  CastGo(Object, _this, Destruct);
  LinkedListClear(this);
  Drop(this->root_, 0);
  return this;
}

Func(dif_int, LinkedListIsEqual, Obj _that)
{
  return 0;
}

Func(dif_int, LinkedListIsGreater, Obj _that)
{
  return 0;
}

Func(void, LinkedListCopy, Obj _that)
{
}

Func(void, LinkedListClear)
{
  PtrLinkedList this = _this;
  PtrListNode x = Go(this->root_, Get_next, 1);
  for ( ; x != this->root_; ) {
    PtrListNode s = Go(x, Get_next, 1);
    Drop(x, 0);
    x = s;
  }
  Go(this->root_, Set_next, this->root_, 0);
  Go(this->root_, Set_next, this->root_, 1);

  PtrValue size = Go(this->root_, Get_data);
  Go(size, Set_val, 0);
}

Func(void, LinkedListInsert, ...)
{
  va_list ap;
  va_start(ap, _this);
  Obj _element = va_arg(ap, Obj);
  dif_int _rank = va_arg(ap, dif_size),
          _ht = va_arg(ap, dif_size);
  va_end(ap);

  PtrLinkedList this = _this;
  PtrListNode x = this->root_;
  for ( ; 0 < _rank; _rank--) {
    x = Go(x, Get_next, _ht);
  }

  PtrListNode y = New(ListNode, 2, _element),
              s = Go(x, Get_next, _ht);
  Go(x, Set_next, y, _ht);
  Go(y, Set_next, x, !_ht);
  Go(y, Set_next, s, _ht);
  Go(s, Set_next, y, !_ht);

  PtrValue size = Go(this->root_, Get_data);
  Go(size, Inc_val, 1);
}

Func(Obj, LinkedListSearch, ...)
{
  return 0;
}

Func(dif_size, LinkedListRank, ...)
{
  return 0;
}

Func(Obj, LinkedListSelect, ...)
{
  va_list ap;
  va_start(ap, _this);
  dif_int _rank = va_arg(ap, dif_size),
          _ht = va_arg(ap, dif_size);
  va_end(ap);

  PtrLinkedList this = _this;
  PtrListNode x = Go(this->root_, Get_next, _ht);
  for ( ; x != this->root_ && _rank; x = Go(x, Get_next, _ht)) {
    _rank--;
  }
  return x != this->root_? Go(x, Get_data): 0;
}

Func(void, LinkedListDelete, ...)
{
  va_list ap;
  va_start(ap, _this);
  dif_int _rank = va_arg(ap, dif_size),
          _ht = va_arg(ap, dif_size);
  va_end(ap);

  PtrLinkedList this = _this;
  PtrListNode x = Go(this->root_, Get_next, _ht);
  for ( ; x != this->root_ && _rank; x = Go(x, Get_next, _ht)) {
    _rank--;
  }
  if (x != this->root_) {
    PtrListNode p = Go(x, Get_next, !_ht),
                s = Go(x, Get_next, _ht);
    Go(p, Set_next, s, _ht);
    Go(s, Set_next, p, !_ht);
    Drop(x, 0);
    PtrValue size = Go(this->root_, Get_data);
    Go(size, Dec_val, 1);
  }
}

Func(dif_size, LinkedListSize)
{
  LockedPtrLinkedList this = _this;
  PtrValue size = Go(this->root_, Get_data);
  return Go(size, Get_val);
}

Func(Obj, LinkedListBegin)
{
  return 0;
}

Func(Obj, LinkedListEnd)
{
  return 0;
}

Func(Obj, LinkedListReverseBegin)
{
  return 0;
}

Func(Obj, LinkedListReverseEnd)
{
  return 0;
}

Func(Obj, LinkedListNext)
{
  return 0;
}

Func(Obj, LinkedListReverseNext)
{
  return 0;
}

struct LinkedListD _LinkedList = {
  // Info
  {
    "LinkedList",
    sizeof(struct LinkedList),
    sizeof(struct LinkedListD),
    {
      PutM(LinkedList, Construct),
      PutM(LinkedList, Destruct),
      PutM(LinkedList, IsEqual),
      PutM(LinkedList, IsGreater),
      PutM(LinkedList, Copy)
    }
  },
  // Container
  {
    PutM(LinkedList, Clear),
    PutM(LinkedList, Insert),
    PutM(LinkedList, Search),
    PutM(LinkedList, Rank),
    PutM(LinkedList, Select),
    PutM(LinkedList, Delete),
    PutM(LinkedList, Size),
    PutM(LinkedList, Begin),
    PutM(LinkedList, End),
    PutM(LinkedList, ReverseBegin),
    PutM(LinkedList, ReverseEnd),
    PutM(LinkedList, Next),
    PutM(LinkedList, ReverseNext)
  }
};
Type LinkedList = &_LinkedList;
