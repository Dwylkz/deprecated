
#include <AddressSet.h>
#include <Basic.h>

void* DacAddressSetCopy(void* self)
{
  return DacSetCopy(self);
}

void DacAddressSetFree(void* self)
{
  DacSetFree(self);
}

int DacAddressSetVs(void* self, void* that)
{
  return DacSetVs(self, that);
}

uint32_t DacAddressSetHash(void* self)
{
  return DacSetHash(self);
}

char* DacAddressSetPush(void* self)
{
  return DacSetPush(self);
}

char* DacAddressSetPull(const char* flow, void* self)
{
  DacAddressSet* bud;
  char* i = DacSetPull(flow, &bud);
  if (i == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  bud->type = DacAddressType;
  *(DacAddressSet**)self = bud;
  return i;
err_0:
  return NULL;
}

static DacType __DacAddressSetType = {
  DacAddressSetCopy,
  DacAddressSetFree,
  DacAddressSetVs,
  DacAddressSetHash,
  DacAddressSetPush,
  DacAddressSetPull
};
DacType* DacAddressSetType = &__DacAddressSetType;

DacAddressSet* DacAddressSetNew()
{
  return DacSetNew(DacAddressType);
}

void* DacAddressSetSearch(DacAddressSet* self, void* data)
{
  return DacSetSearch(self, data);
}

void* DacAddressSetFind(DacAddressSet* self, void* data)
{
  return DacSetFind(self, data);
}

int DacAddressSetRemove(DacAddressSet* self, void* data)
{
  return DacSetRemove(self, data);
}

void DacAddressSetClear(DacAddressSet* self)
{
  DacSetClear(self);
}

void* DacAddressSetForward(DacAddressSet* self, int* i)
{
  return DacSetForward(self, i);
}

void* DacAddressSetBackward(DacAddressSet* self, int* i)
{
  return DacSetBackward(self, i);
}
