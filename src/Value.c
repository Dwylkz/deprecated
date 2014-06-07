#include "Value.h"

Func(Obj, ValueConstruct, va_list* _ptr_ap)
{
  CastGo(Object, _this, Construct, _ptr_ap);
  PtrValue this = _this;
  this->val_ = va_arg(*_ptr_ap, dif_int);
  return this;
}

Func(Obj, ValueDestruct)
{
  CastGo(Object, _this, Destruct);
  return _this;
}

Func(dif_int, ValueIsEqual, Obj _that)
{
  LockedPtrValue this = _this,
                  that = _that;
  return this->val_ == that->val_;
}

Func(dif_int, ValueIsGreater, Obj _that)
{
  LockedPtrValue this = _this,
                  that = _that;
  return this->val_ > that->val_;
}

Func(void, ValueCopy, Obj _that)
{
  CastGo(Object, _this, Copy, _that);
  LockedPtrValue this = _this;
  PtrValue that = _that;
  that->val_ = this->val_;
}

Func(void, ValueSet_val, dif_int _val)
{
  PtrValue this = _this;
  this->val_ = _val;
}

Func(dif_int, ValueGet_val)
{
  LockedPtrValue this = _this;
  return this->val_;
}

Func(void, ValueInc_val, dif_int _val)
{
  PtrValue this = _this;
  this->val_ += _val;
}

Func(void, ValueDec_val, dif_int _val)
{
  PtrValue this = _this;
  this->val_ -= _val;
}

Func(void, ValueAssign, Obj _that)
{
  dif_int val = ValueGet_val(_that);
  ValueSet_val(_this, val);
}

struct ValueD _Value = {
  // Info
  {
    "Value",
    sizeof(struct Value),
    sizeof(struct ValueD),
    // Basic
    {
      PutM(Value, Construct),
      PutM(Value, Destruct),
      PutM(Value, IsEqual),
      PutM(Value, IsGreater),
      PutM(Value, Copy)
    }
  },
  // BasicType
  {
    PutM(Value, Set_val),
    PutM(Value, Get_val),
    PutM(Value, Inc_val),
    PutM(Value, Dec_val),
    PutM(Value, Assign)
  }
};
Type Value = &_Value;

struct Value _Nil = {
  // Obejct
  {
    MAGIC,
    &_Value
  },
  0
};
const Obj Nil = &_Nil;
