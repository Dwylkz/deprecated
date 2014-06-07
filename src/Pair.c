#include "Pair.h"

Pair *PairNew(Type *i_lt, void *i_l, Type *i_rt, void *i_r)
{
  Pair *bud = malloc(sizeof(Pair));
  bud->lrt_[0] = i_lt;
  bud->lr_[0] = i_lt->cp_(i_l);
  bud->lrt_[1] = i_rt;
  bud->lr_[1] = i_rt->cp_(i_r);
  return bud;
}

void PairSet(Pair *self, void *i_data, dac_int i_lr)
{
  self->lrt_[i_lr]->cp_(i_data);
}

void *PairGet(Pair *self, dac_int i_lr)
{
  return self->lr_[i_lr];
}

dac_int PairEqual(void *_this, void *_that)
{
  Pair *self = _this,
       *that = _that;
  return self->lrt_[0]->eq_(self->lr_[0], that->lr_[0]);
}

dac_int PairGreater(void *_this, void *_that)
{
  Pair *self = _this,
       *that = _that;
  return self->lrt_[0]->gt_(self->lr_[0], that->lr_[0]);
}

void *PairCopy(void *_this)
{
  Pair *bud = malloc(sizeof(Pair)),
       *self = _this;
  *bud = *self;
  bud->lr_[0] = bud->lrt_[0]->cp_(self->lr_[0]);
  bud->lr_[1] = bud->lrt_[1]->cp_(self->lr_[1]);
  return bud;
}

void *PairRemove(void *self)
{
  Pair *old = self;
  old->lrt_[0]->rm_(old->lr_[0]);
  old->lrt_[1]->rm_(old->lr_[1]);
  free(old);
  return old;
}

Type _PairT = {
  PairEqual,
  PairGreater,
  PairCopy,
  PairRemove
},
  *PairT = &_PairT;
