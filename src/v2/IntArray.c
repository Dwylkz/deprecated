#include <IntArray.h>
#include <Basic.h>

void* DacIntArrayCopy(void* self)
{
  return DacArrayCopy(self);
}

void DacIntArrayFree(void* self)
{
  return DacArrayFree(self);
}

int DacIntArrayVs(void* self, void* that)
{
  return DacArrayVs(self, that);
}

uint32_t DacIntArrayHash(void* self)
{
  return DacArrayHash(self);
}

char* DacIntArrayPush(void* self)
{
  return DacArrayPush(self);
}

char* DacIntArrayPull(const char* flow, void* self)
{
  DacIntArray* bud;
  char* i = DacArrayPull(flow, &bud);
  DacCheck(i == NULL, NULL);
  bud->type = DacIntType;
  *(DacIntArray**)self = bud;
  return i;
}

static DacType __DacIntArrayType = {
  DacIntArrayCopy,
  DacIntArrayFree,
  DacIntArrayVs,
  DacIntArrayHash,
  DacIntArrayPush,
  DacIntArrayPull
};
DacType* DacIntArrayType = &__DacIntArrayType;

DacIntArray* DacIntArrayNew()
{
  return DacArrayNew(DacIntType);
}

int DacIntArrayPushBack(DacIntArray* self, int data, int times)
{
  return DacArrayPushBack(self, &data, times);
}

void DacIntArrayPopBack(DacIntArray* self, int times)
{
  DacArrayPopBack(self, times);
}

int* DacIntArrayGet(DacIntArray* self, int vane)
{
  return DacArrayGet(self, vane);
}

int DacIntArraySet(DacIntArray* self, int vane, int data)
{
  return DacArraySet(self, vane, &data);
}

void DacIntArrayClear(DacIntArray* self)
{
  DacArrayClear(self);
}
