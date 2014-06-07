#ifndef BSTNODE_H_
#define BSTNODE_H_

#include "Info.h"
#include "Node.i"
#include "BSTNode.i"

#include "ListNode.h"

Define(BSTNodeD) {
  Info _;
  NodeI Node_;
  BSTNodeI BSTNode_;
};
Define(BSTNode) {
  struct ListNode _;
};
extern Type BSTNode;
/* OK */  Func(Obj, BSTNodeConstruct, va_list* _ptr_ap);
/* OK */  Func(void, BSTNodeSet_parent, Obj _parent);
/* OK */  Func(Obj, BSTNodeGet_parent);
/* OK */  Func(void, BSTNodeSet_lchild, Obj _lchild);
/* OK */  Func(Obj, BSTNodeGet_lchild);
/* OK */  Func(void, BSTNodeSet_rchild, Obj _rchild);
/* OK */  Func(Obj, BSTNodeGet_rchild);

#endif // BSTNODE_H_
