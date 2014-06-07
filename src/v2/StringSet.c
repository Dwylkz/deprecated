
#include <StringSet.h>
#include <Basic.h>

void* DacStringSetCopy(void* self)
{
  return DacSetCopy(self);
}

void DacStringSetFree(void* self)
{
  DacSetFree(self);
}

int DacStringSetVs(void* self, void* that)
{
  return DacSetVs(self, that);
}

uint32_t DacStringSetHash(void* self)
{
  return DacSetHash(self);
}

char* DacStringSetPush(void* self)
{
  return DacSetPush(self);
}

char* DacStringSetPull(const char* flow, void* self)
{
  DacStringSet* bud;
  char* i = DacSetPull(flow, &bud);
  if (i == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  bud->type = DacStringType;
  *(DacStringSet**)self = bud;
  return i;
err_0:
  return NULL;
}

static DacType __DacStringSetType = {
  DacStringSetCopy,
  DacStringSetFree,
  DacStringSetVs,
  DacStringSetHash,
  DacStringSetPush,
  DacStringSetPull
};
DacType* DacStringSetType = &__DacStringSetType;

DacStringSet* DacStringSetNew()
{
  return DacSetNew(DacStringType);
}

char* DacStringSetSearch(DacStringSet* self, char* data)
{
  return DacSetSearch(self, data);
}

char* DacStringSetFind(DacStringSet* self, char* data)
{
  return DacSetFind(self, data);
}

int DacStringSetRemove(DacStringSet* self, char* data)
{
  return DacSetRemove(self, data);
}

void DacStringSetClear(DacStringSet* self)
{
  DacSetClear(self);
}

char* DacStringSetForward(DacStringSet* self, int* i)
{
  return DacSetForward(self, i);
}

char* DacStringSetBackward(DacStringSet* self, int* i)
{
  return DacSetBackward(self, i);
}
