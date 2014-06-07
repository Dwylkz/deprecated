#include "dif.h"
#include "Info.h"
#include "Object.h"

/* Static Link Selector */

dif_int IsObj(LockedObj _this)
{
  return _this && ((LockedPtrObject)_this)->magic_ == MAGIC;
}

LockedObj TypeOf(LockedObj _this)
{
  LockedPtrObject this = _this;
  assert(IsObj(this) && this->type_);
  return this->type_;
}

dif_int TypeCheck(LockedObj _this, LockedObj _that )
{
  return TypeOf(_this) == TypeOf(_that);
}

Method Has(LockedObj _this, Method _method)
{
  LockedPtrInfo type = TypeOf(_this);
  Method *p = (Method*)(&type->offset_ + 1);
  Method *offset = (Method*)((dif_size)type + type->offset_);

  for ( ; p < offset && *p != _method; p++) {}
  assert(*p == _method);

  return *(p + 1);
}

Obj New(Type _type, ...)
{
  LockedPtrInfo type = _type;
  assert(type && type->size_);

  PtrObject this = malloc(type->size_);
  assert(this);

  this->magic_ = MAGIC;
  this->type_ = type;

  va_list ap;

  va_start(ap, _type);
  Go(this, Construct, &ap);
  va_end(ap);

  return this;
}

Obj Clone(Obj _this)
{
  Obj that = 0;
  CopyArray(that, _this, SizeOf(_this));
  Go(_this, Copy, that);
  return that;
}

void Drop(Obj _this, ...)
{
  va_list ap;
  va_start(ap, _this);
  for (Go(_this, Destruct); (_this = va_arg(ap, Obj)); ) {
    Go(_this, Destruct);
  }
  va_end(ap);
}

dif_size SizeOf(LockedObj _this)
{
  LockedPtrInfo type = TypeOf(_this);
  assert(type && type->size_);
  return type->size_;
}

const dif_char* WhatIs(LockedObj _this)
{
  LockedPtrInfo type = TypeOf(_this);
  assert(type->name_);
  return type->name_;
}

dif_int Equal(LockedObj _this, LockedObj _that)
{
  if (TypeCheck(_this, _that)) {
    return Go((Obj)_this, IsEqual, (Obj)_that);
  }
  return 0;
}

dif_int Greater(LockedObj _this, LockedObj _that)
{
  if (TypeCheck(_this, _that)) {
    return Go((Obj)_this, IsGreater, (Obj)_that);
  }
  return 0;
}
