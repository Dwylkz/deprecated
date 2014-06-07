#ifndef TREE_H_
#define TREE_H_

#include "Comm.h"

#define TREE_ROOT 1
#define TREE_LEAF 0

typedef struct Tree {
  int nullable_;
  BitSet *firstpos_,
         *lastpos_;
  Array *followpos_,
        *map_;
} Tree;

Tree *TreeNew(int c);

void TreeRemove(Tree *self);

Tree *TreeConcatenate(Tree *L, Tree *R);

Tree *TreeSeperate(Tree *L, Tree *R);

Tree *TreeRepition(Tree *L);

int TreeSize(Tree *self);

void TreeShow(Tree *self);

#endif // TREE_H_
