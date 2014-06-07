#ifndef PAIR_H_
#define PAIR_H_

#include "dac.h"

#define PAIR_L 0
#define PAIR_R 1

typedef struct Pair {
  Type *lrt_[2];
  void *lr_[2];
} Pair;
extern Type *PairT;

Pair *PairNew(Type *i_lt, void *i_l, Type *i_rt, void *i_r);

void PairSet(Pair *self, void *i_data, dac_int i_lr);

void *PairGet(Pair *self, dac_int i_lr);

void *PairRemove(void *self);
  
#endif // PAIR_H_ 
