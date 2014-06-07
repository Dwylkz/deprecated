#include "Map.h"

MapNode _MapNil = {
  { &_MapNil, &_MapNil },
  0, 0, 0
}, 
  *MapNil = &_MapNil;

MapNode *MapNodeNew(CRI i_cp_key, CRI i_cp_data,
    void* i_key, void* i_data)
{
  MapNode *bud = malloc(sizeof(MapNode));
  assert(bud);
  bud->size_ = 1;
  bud->to_[0] = bud->to_[1] = MapNil;
  bud->key_ = i_cp_key(i_key);
  bud->data_ = i_cp_data(i_data);
  return bud;
}

void MapNodeRoate(MapNode **x, dac_int i_lr)
{
  MapNode *y = (*x)->to_[!i_lr];
  if (y != MapNil) {
    (*x)->to_[!i_lr] = y->to_[i_lr];
    (*x)->size_ = 1 + (*x)->to_[0]->size_ + (*x)->to_[1]->size_;
    y->to_[i_lr] = (*x);
    y->size_ = 1 + y->to_[0]->size_ + y->to_[1]->size_;
    (*x) = y;
  }
}

void MapNodeMadac_intain(MapNode **x, dac_int i_lr)
{
  if ((*x)->to_[i_lr]->to_[i_lr]->size_
      > (*x)->to_[!i_lr]->size_) {
    MapNodeRoate(x, !i_lr);
    MapNodeMadac_intain(&(*x)->to_[!i_lr], i_lr);
    MapNodeMadac_intain(x, !i_lr);
  } else if ((*x)->to_[i_lr]->to_[!i_lr]->size_
      > (*x)->to_[!i_lr]->size_) {
    MapNodeRoate(&(*x)->to_[i_lr], i_lr);
    MapNodeRoate(x, !i_lr);
    MapNodeMadac_intain(&(*x)->to_[i_lr], !i_lr);
    MapNodeMadac_intain(&(*x)->to_[!i_lr], i_lr);
    MapNodeMadac_intain(x, !i_lr);
    MapNodeMadac_intain(x, i_lr);
  }
}

void MapNodeClear(MapNode **x, CRI i_rm_key, CRI i_rm_data)
{
  if ((*x) != MapNil) {
    if ((*x)->to_[0] != MapNil) {
      MapNodeClear(&(*x)->to_[0], i_rm_key, i_rm_data);
    }
    if ((*x)->to_[1] != MapNil) {
      MapNodeClear(&(*x)->to_[1], i_rm_key, i_rm_data);
    }
    i_rm_key((*x)->key_);
    i_rm_data((*x)->data_);
    free(*x);
    (*x) = MapNil;
  }
}

Map *MapNew(Type *i_keyt, Type *i_datat)
{
  Map *bud = malloc(sizeof(Map));
  assert(bud);
  bud->keyt_ = i_keyt;
  bud->datat_ = i_datat;
  bud->root_ = MapNil;
  return bud;
}

void MapPush(Map *self, void *i_key, void *i_data)
{
  MapNode **x = &self->root_;
  for ( ; *x != MapNil; ) {
    (*x)->size_++;
    x = &(*x)->to_[self->keyt_->gt_(i_key, (*x)->key_)];
  }
  *x = MapNodeNew(self->keyt_->cp_, self->datat_->cp_, i_key, i_data);
  MapNodeMadac_intain(&self->root_, 0);
  MapNodeMadac_intain(&self->root_, 1);
}

void MapPop(Map *self, void *i_key)
{
  MapNode **x = &self->root_;
  for ( ; *x != MapNil && !self->keyt_->eq_(i_key, (*x)->key_); ) {
    (*x)->size_--;
    x = &(*x)->to_[self->keyt_->gt_(i_key, (*x)->key_)];
  }
  if (*x != MapNil) {
    for ( ; (*x)->to_[0] != MapNil && (*x)->to_[1] != MapNil; ) {
      MapNodeRoate(x, 0);
      (*x)->size_--;
      x = &(*x)->to_[0];
    }
    MapNode *y = *x;
    *x = (MapNode*)((dac_int)(*x)->to_[0] + (dac_int)(*x)->to_[1] - (dac_int)MapNil);
    y->to_[0] = y->to_[1] = MapNil;
    MapNodeClear(&y, self->keyt_->rm_, self->datat_->rm_);
  }
}

void *MapGet(Map *self, void *i_key)
{
  MapNode *x = self->root_;
  for ( ; x != MapNil && !self->keyt_->eq_(i_key, x->key_); ) {
    x = x->to_[self->keyt_->gt_(i_key, x->key_)];
  }
  return x != MapNil? x->data_: 0;
}

dac_int MapRank(Map *self, void *i_key)
{
  dac_int rank = 1;
  MapNode *x = self->root_;
  for ( ; x != MapNil && !self->keyt_->eq_(i_key, x->key_); ) {
    rank += (x->to_[0]->size_ + 1) * self->keyt_->gt_(i_key, x->key_);
    x = x->to_[self->keyt_->gt_(i_key, x->key_)];
  }
  return x != MapNil? rank + x->to_[0]->size_: 0;
}

void *MapPick(Map *self, dac_int i_idx, dac_int i_kd)
{
  MapNode *x = self->root_;
  for ( ; x != MapNil; ) {
    dac_int lsz = 1 + x->to_[0]->size_,
        lr = i_idx > lsz;
    if (lsz == i_idx) {
      return i_kd? x->data_: x->key_;
    }
    i_idx -= lr * lsz;
    x = x->to_[lr];
  }
  return 0;
}

dac_int MapSize(Map *self)
{
  return self->root_->size_;
}

void MapClear(Map *self)
{
  MapNodeClear(&self->root_, self->keyt_->rm_, self->datat_->rm_);
}

void *MapRemove(void *self)
{
  MapClear(self);
  free(self);
  return self;
}

Type _MapT = {
  0,
  0,
  0,
  MapRemove
},
  *MapT = &_MapT;
