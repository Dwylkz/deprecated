#include <Set.h>
#include <Basic.h>

void* DacSetCopy(void* self)
{
  DacSet* from = self;
  DacSet* bud = calloc(1, sizeof(DacSet));
  if (bud == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  bud->data = DacMSetCopy(from->data);
  if (bud->data == NULL)
    DacGoto(err_1, DAC_ERR_COPY);

  bud->type = from->type;
  return bud;
err_1:
  free(bud);
err_0:
  return NULL;
}

void DacSetFree(void* self)
{
  DacSet* old = self;
  DacMSetFree(old->data);
  free(old);
}

int DacSetVs(void* self, void* that)
{
  DacSet* lhs = self;
  DacSet* rhs = that;
  if (lhs->type != rhs->type)
    return DacAddressVs(lhs->type, rhs->type);
  return DacMSetVs(lhs->data, rhs->data);
}

uint32_t DacSetHash(void* self)
{
  DacSet* old = self;
  return DacMSetHash(old->data);
}

char* DacSetPush(void* self)
{
  DacSet* old = self;
  return DacMSetPush(old->data);
}

char* DacSetPull(const char* flow, void* self)
{
  DacSet* bud = calloc(1, sizeof(DacSet));
  if (bud == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  char* i = DacMSetPull(flow, &bud->data);
  if (i == NULL)
    DacGoto(err_1, DAC_ERR_PULL);

  bud->type = NULL;
  *(DacSet**)self = bud;
  return i;
err_1:
  free(bud);
err_0:
  return NULL;
}

static DacType __DacSetType = {
  DacSetCopy,
  DacSetFree,
  DacSetVs,
  DacSetHash,
  DacSetPush,
  DacSetPull
};
DacType* DacSetType = &__DacSetType;

DacSet* DacSetNew(DacType* type)
{
  DacSet* bud = calloc(1, sizeof(DacSet));
  DacCheck(bud == NULL, NULL);
  bud->data = DacMSetNew();
  DacCheckAndFree(bud->data == NULL, bud, NULL);
  bud->type = type;
  return bud;
}

void* DacSetSearch(DacSet* self, void* data)
{
  DacWrapper* w = DacWrapperNew(self->type, data);
  if (w == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  DacWrapper* found = DacMSetSearch(self->data, w);
  DacWrapperFree(w);
  if (found == NULL)
    DacGoto(err_0, DAC_ERR_INSERT);

  return DacWrapperGet(found);
err_0:
  return NULL;
}

void* DacSetFind(DacSet* self, void* data)
{
  DacWrapper* w = DacWrapperNew(self->type, data);
  if (w == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  DacWrapper* found = DacMSetFind(self->data, w);
  DacWrapperFree(w);
  if (found == NULL)
    return NULL;

  return DacWrapperGet(found);
err_0:
  return NULL;
}

int DacSetRemove(DacSet* self, void* data)
{
  DacWrapper* w = DacWrapperNew(self->type, data);
  if (w == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  DacMSetRemove(self->data, w);
  DacWrapperFree(w);
  return 0;
err_0:
  return -1;
}

void DacSetClear(DacSet* self)
{
  DacMSetClear(self->data);
}

void* DacSetForward(DacSet* self, int* i)
{
  DacWrapper* w = DacMSetForward(self->data, i);
  return w != NULL? DacWrapperGet(w): NULL;
}

void* DacSetBackward(DacSet* self, int* i)
{
  DacWrapper* w = DacMSetBackward(self->data, i);
  return w != NULL? DacWrapperGet(w): NULL;
}
