#include <Pair.h>

void* DacPairCopy(void* self)
{
  return DacMPairCopy(self);
}

void DacPairFree(void* self)
{
  DacMPairFree(self);
}

int DacPairVs(void* self, void* that)
{
  return DacMPairVs(self, that);
}

uint32_t DacPairHash(void* self)
{
  return DacMPairHash(self);
}

char* DacPairPush(void* self)
{
  return DacMPairPush(self);
}

char* DacPairPull(const char* flow, void* self)
{
  return DacMPairPull(flow, self);
}

static DacType __DacPairType = {
  DacPairCopy,
  DacPairFree,
  DacPairVs,
  DacPairHash,
  DacPairPush,
  DacPairPull
};
DacType* DacPairType = &__DacPairType;

DacPair* DacPairNew(DacType* ltype,
                    void* ldata,
                    DacType* rtype,
                    void* rdata)
{
  DacPair* bud = calloc(1, sizeof(DacPair));
  if (bud == 0)
    DacGoto(err_0, DAC_ERR_ALLOC);

  bud->data[0] = DacWrapperNew(ltype, ldata);
  if (bud->data[0] == NULL)
    DacGoto(err_1, DAC_ERR_ALLOC);

  bud->data[1] = DacWrapperNew(rtype, rdata);
  if (bud->data[1] == NULL)
    DacGoto(err_1, DAC_ERR_ALLOC);

  return bud;
err_2:
  DacWrapperFree(bud->data[0]);
err_1:
  free(bud);
err_0:
  return NULL;
}

void* DacPairGet(DacPair* self, int vane)
{
  return self->data[vane]->data;
}

int DacPairSet(DacPair* self, int vane, void* data)
{
  DacWrapper* copy_data = DacWrapperNew(self->data[vane]->type, data);
  DacCheck(copy_data == NULL, -1);
  DacWrapperFree(self->data[vane]);
  self->data[vane] = copy_data;
  return 0;
}
