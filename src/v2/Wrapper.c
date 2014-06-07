#include <Wrapper.h>
#include <Basic.h>

#include <MPair.h>
#include <MSet.h>
#include <MArray.h>

void* DacWrapperCopy(void* self)
{
  DacWrapper* from = self;
  return DacWrapperNew(from->type, from->data);
}

void DacWrapperFree(void* self)
{
  DacWrapper* old = self;
  old->type->Free(old->data);
  free(old);
}

int DacWrapperVs(void* self, void* that)
{
  DacWrapper* lhs = self;
  DacWrapper* rhs = that;
  if (lhs->type != rhs->type)
    return DacAddressVs(lhs->type, rhs->type);
  return lhs->type->Vs(lhs->data, rhs->data);
}

uint32_t DacWrapperHash(void* self)
{
  DacWrapper* old = self;
  return old->type->Hash(old->data);
}

char* DacWrapperPush(void* self)
{
  DacWrapper* old = self;
  return old->type->Push(old->data);
}

char* DacWrapperPull(const char* flow, void* self)
{
  char* i = DacFirstGraph(flow);
  DacCheck(i == NULL, NULL);
  DacWrapper* bud = malloc(sizeof(DacWrapper));
  DacCheck(bud == NULL, NULL);
  char* ret = NULL;
  if (*i == '"') {
    bud->type = DacStringType;
    ret = DacStringPull(i, &bud->data);
  }
  else if (*i == '{') {
    bud->type = DacMSetType;
    ret = DacMSetPull(i, &bud->data);
  }
  else if (*i == '[') {
    bud->type = DacMArrayType;
    ret = DacMArrayPull(i, &bud->data);
  }
  else if (*i == '(') {
    bud->type = DacMPairType;
    ret = DacMPairPull(i, &bud->data);
  }
  else if (*i == 'd') {
    bud->type = DacIntType;
    ret = DacIntPull(i, &bud->data);
  }
  else if (*i == 'p') {
    bud->type = DacAddressType;
    ret = DacAddressPull(i, &bud->data);
  }
  else
    DacErr(-1, "expect '\"', '[', '{', '(', 'd', 'p' not %c", *i);
  if (ret == NULL) {
    free(bud);
    return NULL;
  }
  *(DacWrapper**)self = bud;
  return ret;
}

static DacType __DacWrapperType = {
  DacWrapperCopy,
  DacWrapperFree,
  DacWrapperVs,
  DacWrapperHash,
  DacWrapperPush,
  DacWrapperPull
};
DacType* DacWrapperType = &__DacWrapperType;

DacWrapper* DacWrapperNew(DacType* type, void* data)
{
  DacWrapper* bud = malloc(sizeof(DacWrapper));
  DacCheck(bud == NULL, NULL);
  void* copy_data = type->Copy(data);
  DacCheckAndFree(copy_data == NULL, bud, NULL);
  bud->type = type;
  bud->data = copy_data;
  return bud;
}

void* DacWrapperGet(DacWrapper* self)
{
  return self->data;
}

int DacWrapperSet(DacWrapper* self, DacType* type, void* data)
{
  void* copy_data = type->Copy(data);
  DacCheck(copy_data == NULL, -1);
  self->type->Free(self->data);
  self->type = type;
  self->data = copy_data;
  return 0;
}

void* DacWrapperExport(DacWrapper* self)
{
  void* ret = self->data;
  free(self);
  return ret;
}
