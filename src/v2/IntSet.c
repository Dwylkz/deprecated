#include <IntSet.h>
#include <Basic.h>

void* DacIntSetCopy(void* self)
{
  return DacSetCopy(self);
}

void DacIntSetFree(void* self)
{
  DacSetFree(self);
}

int DacIntSetVs(void* self, void* that)
{
  return DacSetVs(self, that);
}

uint32_t DacIntSetHash(void* self)
{
  return DacSetHash(self);
}

char* DacIntSetPush(void* self)
{
  return DacSetPush(self);
}

char* DacIntSetPull(const char* flow, void* self)
{
  DacIntSet* bud;
  char* i = DacSetPull(flow, &bud);
  if (i == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  bud->type = DacIntType;
  *(DacIntSet**)self = bud;
  return i;
err_0:
  return NULL;
}

static DacType __DacIntSetType = {
  DacIntSetCopy,
  DacIntSetFree,
  DacIntSetVs,
  DacIntSetHash,
  DacIntSetPush,
  DacIntSetPull
};
DacType* DacIntSetType = &__DacIntSetType;

DacIntSet* DacIntSetNew()
{
  return DacSetNew(DacIntType);
}

int* DacIntSetSearch(DacIntSet* self, int data)
{
  return DacSetSearch(self, &data);
}

int* DacIntSetFind(DacIntSet* self, int data)
{
  return DacSetFind(self, &data);
}

int DacIntSetRemove(DacIntSet* self, int data)
{
  return DacSetRemove(self, &data);
}

void DacIntSetClear(DacIntSet* self)
{
  DacSetClear(self);
}

int* DacIntSetForward(DacIntSet* self, int* i)
{
  return DacSetForward(self, i);
}

int* DacIntSetBackward(DacIntSet* self, int* i)
{
  return DacSetBackward(self, i);
}
