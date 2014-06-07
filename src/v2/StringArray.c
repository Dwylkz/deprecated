
#include <StringArray.h>
#include <Basic.h>

void* DacStringArrayCopy(void* self)
{
  return DacArrayCopy(self);
}

void DacStringArrayFree(void* self)
{
  return DacArrayFree(self);
}

int DacStringArrayVs(void* self, void* that)
{
  return DacArrayVs(self, that);
}

uint32_t DacStringArrayHash(void* self)
{
  return DacArrayHash(self);
}

char* DacStringArrayPush(void* self)
{
  return DacArrayPush(self);
}

char* DacStringArrayPull(const char* flow, void* self)
{
  DacStringArray* bud;
  char* i = DacArrayPull(flow, &bud);
  DacCheck(i == NULL, NULL);
  bud->type = DacStringType;
  *(DacStringArray**)self = bud;
  return i;
}

static DacType __DacStringArrayType = {
  DacStringArrayCopy,
  DacStringArrayFree,
  DacStringArrayVs,
  DacStringArrayHash,
  DacStringArrayPush,
  DacStringArrayPull
};
DacType* DacStringArrayType = &__DacStringArrayType;

DacStringArray* DacStringArrayNew()
{
  return DacArrayNew(DacStringType);
}

int DacStringArrayPushBack(DacStringArray* self, const char* data, int times)
{
  return DacArrayPushBack(self, (char*)data, times);
}

void DacStringArrayPopBack(DacStringArray* self, int times)
{
  DacArrayPopBack(self, times);
}

char* DacStringArrayGet(DacStringArray* self, int vane)
{
  return DacArrayGet(self, vane);
}

int DacStringArraySet(DacStringArray* self, int vane, const char* data)
{
  return DacArraySet(self, vane, (char*)data);
}

void DacStringArrayClear(DacStringArray* self)
{
  DacArrayClear(self);
}
