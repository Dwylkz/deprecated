#include <Map.h>
#include <Basic.h>

void* DacMapCopy(void* self)
{
  DacMap* from = self;
  DacMap* bud = calloc(1, sizeof(DacMap));
  if (bud == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  bud->data = DacSetCopy(from->data);
  if (bud->data == NULL)
    DacGoto(err_1, DAC_ERR_COPY);

  bud->type[0] = from->type[0];
  bud->type[1] = from->type[1];
  return bud;
err_1:
  free(bud);
err_0:
  return NULL;
}

void DacMapFree(void* self)
{
  DacMap* old = self;
  DacSetFree(old->data);
  free(old);
}

int DacMapVs(void* self, void* that)
{
  DacMap* lhs = self;
  DacMap* rhs = that;
  return DacSetVs(lhs->data, rhs->data);
}

uint32_t DacMapHash(void* self)
{
  uint32_t code = 0;
  DacMap* old = self;
  return DacSetHash(old->data);
}

char* DacMapPush(void* self)
{
  DacMap* old = self;
  return DacSetPush(old->data);
}

char* DacMapPull(const char* flow, void* self)
{
  char* i;
  DacMap* bud = calloc(1, sizeof(DacMap));
  if (bud == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  i = DacSetPull(flow, &bud->data);
  if (bud->data == NULL)
    DacGoto(err_1, DAC_ERR_PULL);

  *(DacMap**)self = bud;
  return i;
err_1:
  free(bud);
err_0:
  return NULL;
}

static DacType __DacMapType = {
  DacMapCopy,
  DacMapFree,
  DacMapVs,
  DacMapHash,
  DacMapPush,
  DacMapPull
};
DacType* DacMapType = &__DacMapType;

DacMap* DacMapNew(DacType* ltype, DacType* rtype)
{
  DacMap* bud = calloc(1, sizeof(DacMap));
  if (bud == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  bud->data = DacSetNew(DacPairType);
  if (bud->data == NULL)
    DacGoto(err_1, DAC_ERR_ALLOC);

  bud->type[0] = ltype;
  bud->type[1] = rtype;
  return bud;
err_1:
  free(bud);
err_0:
  return NULL;
}

int DacMapInsert(DacMap* self, void* key, void* value)
{
  DacPair* p = DacPairNew(self->type[0], key,
                          self->type[1], value);
  if (p == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  if (DacSetSearch(self->data, p) == NULL)
    DacGoto(err_1, DAC_ERR_INSERT);
  
  return 0; 
err_1:
  DacPairFree(p);
err_0:
  return -1;
}

void* DacMapFind(DacMap* self, void* key)
{
  DacPair* p = DacPairNew(self->type[0], key,
                          DacAddressType, key);
  if (p == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  DacPair* ret = DacSetFind(self->data, p);
  DacPairFree(p);
  
  return ret == NULL? NULL: DacPairGet(ret, 1);
err_1:
  DacPairFree(p);
err_0:
  return NULL;
}

int DacMapRemove(DacMap* self, void* key)
{
  DacPair* p = DacPairNew(self->type[0], key,
                          DacAddressType, key);
  if (p == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  int ret = DacSetRemove(self->data, p);
  DacPairFree(p);
  
  return ret;
err_1:
  DacPairFree(p);
err_0:
  return -1;
}

void DacMapClear(DacMap* self)
{
  DacSetClear(self->data);
}

DacPair* DacMapForward(DacMap* self, int* i)
{
  return DacSetForward(self->data, i);
}

DacPair* DacMapBackward(DacMap* self, int* i)
{
  return DacSetBackward(self->data, i);
}
