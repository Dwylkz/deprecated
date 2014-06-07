#include <Array.h>
#include <Basic.h>

void* DacArrayCopy(void* self)
{
  DacArray* old = self;
  DacMArray* copy_data = DacMArrayCopy(old->data);
  DacCheck(copy_data == NULL, NULL);
  DacArray* bud = calloc(1, sizeof(DacArray));
  if (bud == NULL) {
    DacMArrayFree(copy_data);
    return NULL;
  }
  bud->type = old->type;
  bud->data = copy_data;
  return bud;
}

void DacArrayFree(void* self)
{
  DacArray* old = self;
  DacMArrayFree(old->data);
  free(old);
}

int DacArrayVs(void* self, void* that)
{
  DacArray* lhs= self;
  DacArray* rhs = that;
  if (lhs->type != rhs->type)
    return DacAddressVs(lhs->type, rhs->type);
  return DacMArrayVs(lhs->data, rhs->data);
}

uint32_t DacArrayHash(void* self)
{
  DacArray* old = self;
  return DacMArrayHash(old->data);
}

char* DacArrayPush(void* self)
{
  DacArray* old = self;
  return DacMArrayPush(old->data);
}

char* DacArrayPull(const char* flow, void* self)
{
  DacMArray* data;
  char* i = DacMArrayPull(flow, &data);
  DacCheck(i == NULL, NULL);
  DacArray* bud = calloc(1, sizeof(DacArray));
  if (bud == NULL) {
    DacMArrayFree(data);
    return DacErr(NULL, "%s", strerror(errno));
  }
  bud->type = NULL;
  bud->data = data;
  *(DacArray**)self = bud;
  return i;
}

static DacType __DacArrayType = {
  DacArrayCopy,
  DacArrayFree,
  DacArrayVs,
  DacArrayHash,
  DacArrayPush,
  DacArrayPull
};
DacType* DacArrayType = &__DacArrayType;

DacArray* DacArrayNew(DacType* type)
{
  DacArray* bud = calloc(1, sizeof(DacArray));
  DacCheck(bud == NULL, NULL);
  bud->type = type;
  bud->data = DacMArrayNew();
  DacCheckAndFree(bud->data == NULL, bud, NULL);
  return bud;
}

int DacArrayPushBack(DacArray* self, void* data, int times)
{
  DacWrapper* copy_data = DacWrapperNew(self->type, data);
  DacCheck(copy_data == NULL, NULL);
  int flag = DacMArrayPushBack(self->data, copy_data, times);
  DacWrapperFree(copy_data);
  return flag;
}

void DacArrayPopBack(DacArray* self, int times)
{
  DacMArrayPopBack(self->data, times);
}

void* DacArrayGet(DacArray* self, int vane)
{
  return DacWrapperGet(DacMArrayGet(self->data, vane));
}

int DacArraySet(DacArray* self, int vane, void* data)
{
  DacWrapper* copy_data = DacWrapperNew(self->type, data);
  DacCheck(copy_data == NULL, NULL);
  int flag = DacMArraySet(self->data, vane, copy_data);
  DacWrapperFree(copy_data);
  return flag;
}

void DacArrayClear(DacArray* self)
{
  DacMArrayClear(self->data);
}
