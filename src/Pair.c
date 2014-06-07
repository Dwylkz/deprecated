#include "Pair.h"

Func(Obj, PairConstruct, va_list* _ptr_ap)
{
  PtrPair this = _this;
  this->first_ = Clone(va_arg(*_ptr_ap, Obj));
  this->second_= Clone(va_arg(*_ptr_ap, Obj));
  return this;
}

Func(Obj, PairDestruct)
{
  PtrPair this = _this;
  Drop(this->first_, this->second_, 0);
  return this;
}

Func(dif_int, PairIsEqual, Obj _that)
{
  LockedPtrPair this = _this,
                that = _that;
  return Equal(this->first_, that->first_);
}

Func(dif_int, PairIsGreater, Obj _that)
{
  LockedPtrPair this = _this,
                that = _that;
  return Greater(this->first_, that->first_);
}

Func(void, PairCopy, Obj _that)
{
  PtrPair this = _this,
                that = _that;
  that->first_ = Clone(this->first_);
  that->second_ = Clone(this->second_);
}


Func(void, PairSet_first, Obj _first)
{
  PtrPair this = _this;
  Drop(this->first_, 0);
  this->first_ = Clone(_first);
}

Func(Obj, PairGet_first)
{
  LockedPtrPair this = _this;
  return this->first_;
}

Func(void, PairSet_second, Obj _second)
{
  PtrPair this = _this;
  Drop(this->second_, 0);
  this->second_ = Clone(_second);
}

Func(Obj, PairGet_second)
{
  LockedPtrPair this = _this;
  return this->second_;
}

struct PairD _Pair = {
  // Info
  {
    "Pair",
    sizeof(struct Pair),
    sizeof(struct PairD),
    // Basic
    {
      PutM(Pair, Construct),
      PutM(Pair, Destruct),
      PutM(Pair, IsEqual),
      PutM(Pair, IsGreater),
      PutM(Pair, Copy)
    }
  },
  // PairType
  {
    PutM(Pair, Set_first),
    PutM(Pair, Get_first),
    PutM(Pair, Set_second),
    PutM(Pair, Get_second)
  }
};
Type Pair = &_Pair;
