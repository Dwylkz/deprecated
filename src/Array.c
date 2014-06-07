#include "Array.h"

void ArrayResize(Array *self, dac_int i_size)
{
  assert(0 <= i_size);
  dac_int i;
  if (i_size < self->size_) {
    if (i_size < self->datan_) {
      for (i = i_size; i < self->size_; i++) {
        if (self->data_[i]) {
          self->datat_->rm_(self->data_[i]);
          self->data_[i] = 0;
        }
      }
    }
  } else if (self->size_ < i_size) {
    dac_int tmp_size = self->size_ + self->size_ + 1;
    if (tmp_size < i_size) {
      tmp_size = i_size;
    }
    self->data_ = realloc(self->data_, sizeof(void*) * tmp_size);
    assert(self->data_);
    for (i = self->size_; i < tmp_size; i++) {
      self->data_[i] = 0;
    }
    self->size_ = tmp_size;
  }
  self->datan_ = i_size;
}

Array *ArrayNew(Type *i_datat)
{
  Array *bud = malloc(sizeof(Array));
  assert(bud);
  bud->datat_ = i_datat;
  bud->size_ = bud->datan_ = 0;
  bud->data_ = 0;
  return bud;
}

dac_int ArrayEqual(void *_this, void *_that)
{
  Array *self = _this,
        *that = _that;
  assert(self->datat_ == that->datat_);
  if (self->datan_ != that->datan_) {
    return 0;
  }
  dac_int i;
  for (i = 0; i < self->datan_; i++) {
    if (!self->datat_->eq_(self->data_[i], that->data_[i])) {
      return 0;
    }
  }
  return 1;
}

dac_int ArrayGreater(void *_this, void *_that)
{
  Array *self = _this,
        *that = _that;
  assert(self->datat_ == that->datat_);
  dac_int i, size = Min(self->datan_, that->datan_);
  for (i = 0; i < size; i++) {
    if (!self->datat_->eq_(self->data_[i], that->data_[i])) {
      return self->datat_->gt_(self->data_[i], that->data_[i]);
    }
  }
  return self->datan_ > that->datan_;
}

void *ArrayCopy(void *self)
{
  Array *old = self,
        *bud = ArrayNew(old->datat_);
  ArrayResize(bud, ArraySize(old));
  int i;
  for (i = 0 ; i < ArraySize(old); i++) {
    if (old->data_[i]) {
      bud->data_[i] = old->datat_->cp_(old->data_[i]);
    }
  }
  return bud;
}

void *ArrayRemove(void *self)
{
  ArrayClear(self);
  free(self);
  return self;
}

void ArrayClear(Array *self)
{
  ArrayResize(self, 0);
  free(self->data_);
  self->data_ = 0;
  self->size_ = self->datan_ = 0;
}

void ArrayPush(Array *self, void *i_data)
{
  ArrayResize(self, self->datan_ + 1);
  self->data_[self->datan_ - 1] = self->datat_->cp_(i_data);
}

void ArrayPop(Array *self)
{
  ArrayResize(self, self->datan_ - 1);
}

void* ArrayGet(Array *self, dac_int i_idx)
{
  return self->data_[i_idx];
}

void ArraySet(Array *self, dac_int i_idx, void* i_data)
{
  if (self->data_[i_idx]) {
    self->datat_->rm_(self->data_[i_idx]);
  }
  self->data_[i_idx] = self->datat_->cp_(i_data);
}

dac_int ArraySize(Array *self)
{
  return self->datan_;
}

void ArrayCat(Array *self, Array *that)
{
  that = ArrayCopy(that);
  dac_int s = ArraySize(self),
          n = ArraySize(that);
  ArrayResize(self, s + n);
  memcpy(self->data_ + s, that->data_, n * sizeof(void*));
}

Type _ArrayT = {
  ArrayEqual,
  ArrayGreater,
  ArrayCopy,
  ArrayRemove
},
  *ArrayT = &_ArrayT;
