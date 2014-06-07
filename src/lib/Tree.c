#include "Tree.h"

#define RShift() \
  BitSetShift(R->firstpos_, TreeSize(L));\
  BitSetShift(R->lastpos_, TreeSize(L));\
  int i;\
  for (i = 0; i < TreeSize(R); i++) {\
    BitSet *b = (BitSet*)(*(int*)ArrayGet(R->followpos_, i));\
    BitSetShift(b, ArraySize(L->followpos_));\
  }

#define ArrayUnion(x, y) \
  for (i = 0; i < ArraySize(x->y); i++) {\
    BitSet *b = BitSetCopy((BitSet*)*(int*)ArrayGet(x->y, i));\
    ArrayPush(new->y, &b);\
  }

#define MapUnion(x, y) \
  for (i = 0; i < ArraySize(x->y); i++) {\
    ArrayPush(new->y, ArrayGet(x->y, i));\
  }

#define NullUnion(op) \
  new->nullable_ = L->nullable_ op R->nullable_;

#define FXF(x, x_, y, y_) \
  for (i = 0; i < TreeSize(x); i++) {\
    if (BitSetGet(x->x_, i)) {\
      BitSet *b = (BitSet*)(*(int*)ArrayGet(new->followpos_, i));\
      BitSetUnion(b, y->y_);\
    }\
  }


Tree *TreeNew(int c)
{
  Tree *new = malloc(sizeof(Tree));
  new->nullable_ = 1;
  new->firstpos_ = BitSetNew();
  new->lastpos_ = BitSetNew();
  new->followpos_ = ArrayNew(IntT);
  new->map_= ArrayNew(IntT);
  if (c) {
    new->nullable_ = 0;
    BitSetSet(new->firstpos_, 0);
    BitSetSet(new->lastpos_, 0);
    BitSet *t_fp = BitSetNew();
    ArrayPush(new->followpos_, &t_fp);
    ArrayPush(new->map_, &c);
  }
  return new;
}

void TreeRemove(Tree *self)
{
  BitSetRemove(self->firstpos_);
  BitSetRemove(self->lastpos_);
  int i;
  for (i = 0; i < TreeSize(self); i++) {
    BitSet *b = (BitSet*)(*(int*)ArrayGet(self->followpos_, i));
    BitSetRemove(b);
  }
  ArrayRemove(self->followpos_);
  ArrayRemove(self->map_);
  free(self);
}

Tree *TreeConcatenate(Tree *L, Tree *R)
{
  Tree *new = TreeNew(0);
  RShift();
  // firstpos_
  BitSetUnion(new->firstpos_, L->firstpos_);
  if (L->nullable_) {
    BitSetUnion(new->firstpos_, R->firstpos_);
  }
  // lastpos_
  BitSetUnion(new->lastpos_, R->lastpos_);
  if (R->nullable_) {
    BitSetUnion(new->lastpos_, L->lastpos_);
  }
  // followpos_
  ArrayUnion(L, followpos_);
  ArrayUnion(R, followpos_);
  FXF(L, lastpos_, R, firstpos_);
  // nullable_
  NullUnion(&);
  // map_
  MapUnion(L, map_);
  MapUnion(R, map_);
  return new;
}

Tree *TreeSeperate(Tree *L, Tree *R)
{
  Tree *new = TreeNew(0);
  RShift();
  // first
  BitSetUnion(new->firstpos_, L->firstpos_);
  BitSetUnion(new->firstpos_, R->firstpos_);
  // lastpos_
  BitSetUnion(new->lastpos_, R->lastpos_);
  BitSetUnion(new->lastpos_, L->lastpos_);
  // followpos_
  ArrayUnion(L, followpos_);
  ArrayUnion(R, followpos_);
  // nullable_
  NullUnion(|);
  // map_
  MapUnion(L, map_);
  MapUnion(R, map_);
  return new;
}

Tree *TreeRepition(Tree *L)
{
  Tree *new = TreeNew(0);
  int i;
  // first
  BitSetUnion(new->firstpos_, L->firstpos_);
  // lastpos_
  BitSetUnion(new->lastpos_, L->lastpos_);
  // followpos_
  ArrayUnion(L, followpos_);
  FXF(L, lastpos_, L, firstpos_);
  // nullable_
  new->nullable_ = 1;
  // map_
  MapUnion(L, map_);
  return new;
}

int TreeSize(Tree *self)
{
  return ArraySize(self->map_);
}

void TreeShow(Tree *self)
{
#define Show(x, y) \
  printf("%10s = { ", #y);\
  for (i = 0; i < BitSetSize(x); i++) {\
    if (BitSetGet(x, i)) {\
      printf(" %3d", i);\
    }\
  }\
  puts(" }")
  int i, j;
  printf("\nTree size = %d\n", TreeSize(self));
  puts("map_");
  for (i = 0; i < TreeSize(self); i++) {
    int t_char = *(int*)ArrayGet(self->map_, i);
    if (t_char < 128) {
      printf("%3d->%c\n", i, t_char);
    } else {
      printf("%3d->%d detected\n", i, t_char - 128);
    }
  }
  puts("");
  puts(self->nullable_? "nullable": "unnullable");
  Show(self->firstpos_, firstpos);
  Show(self->lastpos_, lastpos);
  puts("followpos");
  for (j = 0; j < TreeSize(self); j++) {
    BitSet *b = (BitSet*)(*(int*)ArrayGet(self->followpos_, j));
    printf("%d", j);
    Show(b,);
  }
  puts("");
#undef Show
}

#undef RShift

#undef ArrayUnion

#undef NullUnion

#undef FXF
