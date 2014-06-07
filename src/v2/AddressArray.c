
#include <AddressArray.h>
#include <Basic.h>

void* DacAddressArrayCopy(void* self)
{
  return DacArrayCopy(self);
}

void DacAddressArrayFree(void* self)
{
  return DacArrayFree(self);
}

int DacAddressArrayVs(void* self, void* that)
{
  return DacArrayVs(self, that);
}

uint32_t DacAddressArrayHash(void* self)
{
  return DacArrayHash(self);
}

char* DacAddressArrayPush(void* self)
{
  return DacArrayPush(self);
}

char* DacAddressArrayPull(const char* flow, void* self)
{
  DacAddressArray* bud;
  char* i = DacArrayPull(flow, &bud);
  DacCheck(i == NULL, NULL);
  bud->type = DacAddressType;
  *(DacAddressArray**)self = bud;
  return i;
}

static DacType __DacAddressArrayType = {
  DacAddressArrayCopy,
  DacAddressArrayFree,
  DacAddressArrayVs,
  DacAddressArrayHash,
  DacAddressArrayPush,
  DacAddressArrayPull
};
DacType* DacAddressArrayType = &__DacAddressArrayType;

DacAddressArray* DacAddressArrayNew()
{
  return DacArrayNew(DacAddressType);
}

int DacAddressArrayPushBack(DacAddressArray* self, void* data, int times)
{
  return DacArrayPushBack(self, data, times);
}

void DacAddressArrayPopBack(DacAddressArray* self, int times)
{
  DacArrayPopBack(self, times);
}

void* DacAddressArrayGet(DacAddressArray* self, int vane)
{
  return DacArrayGet(self, vane);
}

int DacAddressArraySet(DacAddressArray* self, int vane, void* data)
{
  return DacArraySet(self, vane, data);
}

void DacAddressArrayClear(DacAddressArray* self)
{
  DacArrayClear(self);
}
