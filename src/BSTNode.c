#include "BSTNode.h"
#include "Vector.h"
#include "Value.h"

Func(Obj, BSTNodeConstruct, va_list* _ptr_ap)
{
  CastGo(Object, _this, Construct, _ptr_ap);
  PtrListNode this = _this;
  this->to_ = New(Vector, 3);
  this->data_ = Clone(va_arg(*_ptr_ap, Obj));
  return this;
}

Func(void, BSTNodeSet_parent, Obj _parent)
{
  ListNodeSet_next(_this, _parent, 0);
}

Func(Obj, BSTNodeGet_parent)
{
  return ListNodeGet_next(_this, 0);
}

Func(void, BSTNodeSet_lchild, Obj _lchild)
{
  ListNodeSet_next(_this, _lchild, 1);
}

Func(Obj, BSTNodeGet_lchild)
{
  return ListNodeGet_next(_this, 1);
}

Func(void, BSTNodeSet_rchild, Obj _rchild)
{
  ListNodeSet_next(_this, _rchild, 2);
}

Func(Obj, BSTNodeGet_rchild)
{
  return ListNodeGet_next(_this, 2);
}

struct BSTNodeD _BSTNode = {
  // Info
  {
    "BSTNode",
    sizeof(struct BSTNode),
    sizeof(struct BSTNodeD),
    // Basic
    {
      PutM(BSTNode, Construct),
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
  },
  // BSTNode
  {
    PutM(BSTNode, Set_parent),
    PutM(BSTNode, Get_parent),
    PutM(BSTNode, Set_lchild),
    PutM(BSTNode, Get_lchild),
    PutM(BSTNode, Set_rchild),
    PutM(BSTNode, Get_rchild)
  }
};
Type BSTNode = &_BSTNode;
