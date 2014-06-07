#include "Vector.h"
#include "Value.h"

Func(Obj, VectorConstruct, va_list* _ptr_ap)
{
  CastGo(Object, _this, Construct, _ptr_ap);
  PtrVector this = _this;
  this->current_size_ = this->size_
    = va_arg(*_ptr_ap, dif_size);
  this->array_ = calloc(this->size_, sizeof(Obj));
  assert(this->array_);
  dif_size i;
  for (i = 0; i < this->size_; i++) {
    this->array_[i] = Clone(Nil);
  }
  return this;
}

Func(Obj, VectorDestruct)
{
  VectorClear(_this);
  return _this;
}

Func(dif_int, VectorIsEqual, Obj _that)
{
  LockedPtrVector this = _this,
                  that = _that;
  dif_size size = this->current_size_;
  if (that->current_size_ == size) {
    dif_size i = 0;
    for ( ; i < size; i++) {
      if (!Equal(this->array_[i], that->array_[i])) {
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

Func(dif_int, VectorIsGreater, Obj _that)
{
  return 0;
}

Func(void, VectorCopy, Obj _that)
{
  CastGo(Object, _this, Copy, _that);
  LockedPtrVector this = _this;
  PtrVector that = _that;
  CopyArray(that->array_, this->array_, this->size_ * sizeof(Obj));
  dif_size i = 0;
  for ( ; i  < this->size_; i++) {
    that->array_[i] = Clone(this->array_[i]);
  }
}

Func(void, VectorClear)
{
  PtrVector this = _this;
  dif_size i = 0;
  for ( ; i < this->size_; i++) {
    Drop(this->array_[i], 0);
  }
  if (this->array_) {
    free(this->array_);
    this->array_ = 0;
  } 
  this->size_ = this->current_size_ = 0;
}

Func(dif_size, VectorCheck, dif_size _rank)
{
  PtrVector this = _this;
  assert(0 <= _rank);
  if (!(_rank < this->current_size_)) {
    this->current_size_ = _rank + 1;
    if (!(this->current_size_ < this->size_)) {
      dif_size tmp_size = this->current_size_
        + this->current_size_ + 1;
      this->array_ = realloc(this->array_, tmp_size * sizeof(Obj));

      dif_size i = 0;
      for (i = this->size_; i < tmp_size; i++) {
        this->array_[i] = Clone(Nil);
      }
      this->size_ = tmp_size;
    }
  }
  return _rank;
}

Func(void, VectorInsert, ...)
{
  va_list ap;
  va_start(ap, _this);
  Obj _element = va_arg(ap, Obj);
  dif_size _rank = va_arg(ap, dif_size);
  va_end(ap);

  PtrVector this = _this;
  VectorCheck(this, _rank);
  Drop(this->array_[_rank], 0);
  this->array_[_rank] = Clone(_element);
}

Func(Obj, VectorSearch, ...)
{
  va_list ap;
  va_start(ap, _this);
  Obj _element = va_arg(ap, Obj);
  va_end(ap);

  LockedPtrVector this = _this;
  dif_size i = 0;
  for ( ; i < this->current_size_; i++) {
    if (Equal(this->array_[i], _element)) {
      return this->array_[i];
    }
  }
  return 0;
}

Func(dif_size, VectorRank, ...)
{
  va_list ap;
  va_start(ap, _this);
  Obj _element = va_arg(ap, Obj);
  va_end(ap);

  LockedPtrVector this = _this;
  dif_size i = 0;
  for ( ; i < this->current_size_; i++) {
    if (Equal(this->array_[i], _element)) {
      return i;
    }
  }
  return -1;
}

Func(Obj, VectorSelect, ...)
{
  va_list ap;
  va_start(ap, _this);
  dif_size _rank = va_arg(ap, dif_size);
  va_end(ap);

  VectorCheck(_this, _rank);
  LockedPtrVector this = _this;
  return this->array_[_rank];
}

Func(void, VectorDelete, ...)
{
  va_list ap;
  va_start(ap, _this);
  dif_size _rank = va_arg(ap, dif_size);
  va_end(ap);

  VectorCheck(_this, _rank);
  LockedPtrVector this = _this;
  Drop(this->array_[_rank], 0);
  this->array_[_rank] = Clone(Nil);
}

Func(dif_size, VectorSize)
{
  LockedPtrVector this = _this;
  return this->current_size_;
}

Func(Obj, VectorBegin)
{
  return 0;
}

Func(Obj, VectorEnd)
{
  return 0;
}

Func(Obj, VectorReverseBegin)
{
  return 0;
}

Func(Obj, VectorReverseEnd)
{
  return 0;
}

Func(Obj, VectorNext, Obj _Iterator)
{
  return 0;
}

Func(Obj, VectorReverseNext, Obj _Iterator)
{
  return 0;
}

struct VectorD _Vector = {
  //Info
  {
    "Vector",
    sizeof(struct Vector),
    sizeof(struct VectorD),
    // Basic
    {
      PutM(Vector, Construct),
      PutM(Vector, Destruct),
      PutM(Vector, IsEqual),
      PutM(Vector, IsGreater),
      PutM(Vector, Copy)
    }
  },
  //Container
  {
    PutM(Vector, Clear),
    PutM(Vector, Insert),
    PutM(Vector, Search),
    PutM(Vector, Rank),
    PutM(Vector, Select),
    PutM(Vector, Delete),
    PutM(Vector, Size),
    PutM(Vector, Begin),
    PutM(Vector, End),
    PutM(Vector, ReverseBegin),
    PutM(Vector, ReverseEnd),
    PutM(Vector, Next),
    PutM(Vector, ReverseNext)
  }
};
Type Vector = &_Vector;
