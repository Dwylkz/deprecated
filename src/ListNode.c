#include "ListNode.h"
#include "Vector.h"
#include "Value.h"

Func(Obj, ListNodeConstruct, va_list* _ptr_ap)
{
  CastGo(Object, _this, Construct, _ptr_ap);
  PtrListNode this = _this;
  this->to_ = New(Vector, va_arg(*_ptr_ap, dif_size));
  this->data_ = Clone(va_arg(*_ptr_ap, Obj));
  return this;
}

Func(Obj, ListNodeDestruct)
{
  PtrListNode this = _this;
  Drop(this->to_, this->data_, 0);
  CastGo(Object, this, Destruct);
  return this;
}

Func(dif_int, ListNodeIsEqual, Obj _that)
{
  PtrListNode this = _this,
              that = _that;
  return Equal(this->data_, that->data_);
}

Func(dif_int, ListNodeIsGreater, Obj _that)
{
  PtrListNode this = _this,
              that = _that;
  return Greater(this->data_, that->data_);
}

Func(void, ListNodeCopy, Obj _that)
{
  CastGo(Object, _this, Copy, _that);
  LockedPtrListNode this = _this;
  PtrListNode       that = _that;
  that->to_ = Clone(this->to_);
  that->data_ = Clone(this->data_);
}

Func(void, ListNodeSet_next, Obj _next, dif_size _index)
{
  PtrListNode this = _this;
  Obj next = New(Value, _next);
  Go(this->to_, Insert, next, _index);
  Drop(next, 0);
}

Func(Obj, ListNodeGet_next, dif_size _index)
{
  LockedPtrListNode this = _this;
  PtrValue val = Go(this->to_, Select, _index);
  return (Obj)Go(val, Get_val);
}

Func(void, ListNodeSet_data, Obj _data)
{
  PtrListNode this = _this;
  Drop(this->data_, 0);
  this->data_ = Clone(_data);
}

Func(Obj, ListNodeGet_data)
{
  LockedPtrListNode this = _this;
  return this->data_;
}

struct ListNodeD _ListNode = {
  // Info
  {
    "ListNode",
    sizeof(struct ListNode),
    sizeof(struct ListNodeD),
    // Basic
    {
      PutM(ListNode, Construct),
      PutM(ListNode, Destruct),
      PutM(ListNode, IsEqual),
      PutM(ListNode, IsGreater),
      PutM(ListNode, Copy)
    }
  },
  // Node
  {
    PutM(ListNode, Set_next),
    PutM(ListNode, Get_next),
    PutM(ListNode, Set_data),
    PutM(ListNode, Get_data)
  }
};
Type ListNode = &_ListNode;
