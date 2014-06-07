#ifndef BSTNODE_I_
#define BSTNODE_I_

Interface {
  Method
    SetM(Set_parent),
    SetM(Get_parent),
    SetM(Set_lchild),
    SetM(Get_lchild),
    SetM(Set_rchild),
    SetM(Get_rchild);
} BSTNodeI;
SetT(void, Set_parent, Obj _parent);
SetT(Obj, Get_parent);
SetT(void, Set_lchild, Obj _lchild);
SetT(Obj, Get_lchild);
SetT(void, Set_rchild, Obj _rchild);
SetT(Obj, Get_rchild);

#endif // BSTNODE_I_
