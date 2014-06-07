#include "Object.h"

Func(Obj, ObjectConstruct, va_list *_ptr_ap)
{
  return _this;
}

Func(Obj, ObjectDestruct)
{
  return _this;
}

Func(dif_int, ObjectIsEqual, Obj _that)
{
  dif_size size = SizeOf(_this);
  if (SizeOf(_that) < size) {
    size = SizeOf(_that);
  }
  return !strncmp(_this, _that, size);
}

Func(dif_int, ObjectIsGreater, Obj _that)
{
  dif_size size = SizeOf(_this);
  if (SizeOf(_that) < size) {
    size = SizeOf(_that);
  }
  return 0 < strncmp(_this, _that, size);
}

Func(void, ObjectCopy, Obj _that)
{
}

struct ObjectD _Object = {
  //Info
  {
    "Object",
    sizeof(struct Object),
    sizeof(struct ObjectD),
    {
      PutM(Object, Construct),
      PutM(Object, Destruct),
      PutM(Object, IsEqual),
      PutM(Object, IsGreater),
      PutM(Object, Copy)
    }
  }
};
Type Object = &_Object;
