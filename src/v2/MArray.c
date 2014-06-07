#include <MArray.h>
#include <Basic.h>

static int Resize(DacMArray* self, int size)
{
  int volume = DacMax(1, self->volume);
  while (volume < size) volume *= 2;
  if (volume > self->volume) {
    DacWrapper** copy_data = realloc(self->data, volume * sizeof(DacWrapper*));
    DacCheck(copy_data == NULL, -1);
    self->data = copy_data;
    self->volume = volume;
  }
  for (int i = size; i < self->size; i++)
    DacWrapperFree(self->data[i]);
  self->size = size;
  return 0;
}

void* DacMArrayCopy(void* self)
{
  DacMArray* from = self;
  DacMArray* bud = DacMArrayNew();
  DacCheckAndFree(Resize(bud, from->size) != 0, bud, NULL);
  for (int i = 0; i < from->size; i++) {
    bud->data[i] = DacWrapperCopy(from->data[i]);
    if (bud->data[i] == NULL) {
      bud->size = i;
      DacMArrayFree(bud);
      return NULL;
    }
  }
  return bud;
}

void DacMArrayFree(void* self)
{
  DacMArray* old = self;
  Resize(old, 0);
  free(old->data);
  free(old);
}

int DacMArrayVs(void* self, void* that)
{
  DacMArray* lhs = self;
  DacMArray* rhs = that;
  int size = DacMin(lhs->size, rhs->size);
  for (int i = 0; i < size; i++) {
    int vane = DacWrapperVs(lhs->data[i], rhs->data[i]);
    if (vane != 0) return vane;
  }
  return DacIntVs(&lhs->size, &rhs->size);
}

uint32_t DacMArrayHash(void* self)
{
  DacMArray* old = self;
  uint32_t ret = 0;
  for (int i = 0; i < old->size; i++)
    ret = ret * 131 + DacWrapperHash(old->data[i]); 
  return ret;
}

char* DacRangePush(void* lower, void* upper,
                   const char ogc[3],
                   DacPush dac_push);

char* DacMArrayPush(void* self)
{
  DacMArray* old = self;
  return DacRangePush(old->data, old->data + old->size,
                      "[,]", DacWrapperPush);
}

char* DacRangePull(const char* flow,
                   const char ogc[3],
                   DacMArray** self);

char* DacMArrayPull(const char* flow, void* self)
{
  return DacRangePull(flow, "[,]", self);
}

static DacType __DacMArrayType = {
 DacMArrayCopy,
 DacMArrayFree,
 DacMArrayVs,
 DacMArrayHash,
 DacMArrayPush,
 DacMArrayPull
};
DacType* DacMArrayType = &__DacMArrayType;

DacMArray* DacMArrayNew()
{
  DacMArray* bud = calloc(1, sizeof(DacMArray));
  DacCheck(bud == NULL, NULL);
  return bud;
}

static int PushBackAux(DacWrapper** lower, DacWrapper** upper)
{
  DacWrapper** start = lower;
  DacRangeFree(lower, upper, DacWrapperFree);
  free(start);
  return -1;
}

int DacMArrayPushBack(DacMArray* self, DacWrapper* data, int times)
{
  DacWrapper** copy_data = calloc(times, sizeof(DacWrapper*));
  DacCheck(copy_data == NULL, -1);
  for (int i = 0; i < times; i++) {
    copy_data[i] = DacWrapperCopy(data);
    if (copy_data[i] == NULL)
      return PushBackAux(copy_data, copy_data + i);
  }
  int pre_size = self->size;
  if (Resize(self, self->size + times) != 0)
    return PushBackAux(copy_data, copy_data + times);
  for (int i = 0; i < times; i++)
    self->data[i + pre_size] = copy_data[i];
  free(copy_data);
  return 0;
}

void DacMArrayPopBack(DacMArray* self, int times)
{
  Resize(self, self->size - times);
}

DacWrapper* DacMArrayGet(DacMArray* self, int vane)
{
  return self->data[vane];
}

int DacMArraySet(DacMArray* self, int vane, DacWrapper* data)
{
  DacWrapper* copy_data = DacWrapperCopy(data);
  DacCheck(copy_data == NULL, -1);
  DacWrapperFree(self->data[vane]);
  self->data[vane] = copy_data;
  return 0;
}

void DacMArrayClear(DacMArray* self)
{
  Resize(self, 0);
}
