#include <MPair.h>
#include <MArray.h>

void* DacMPairCopy(void* self)
{
  DacMPair* old = self;
  return DacMPairNew(old->data[0], old->data[1]);
}

void DacMPairFree(void* self)
{
  DacMPair* old = self;
  DacWrapperFree(old->data[0]);
  DacWrapperFree(old->data[1]);
  free(old);
}

int DacMPairVs(void* self, void* that)
{
  DacMPair* lhs = self;
  DacMPair* rhs = that;
  return DacWrapperVs(lhs->data[0], rhs->data[0]);
}

uint32_t DacMPairHash(void* self)
{
  DacMPair* old = self;
  return DacWrapperHash(old->data[0]);
}

char* DacRangePush(void* lower, void* upper,
                   const char ogc[3],
                   DacPush dac_push);

char* DacMPairPush(void* self)
{
  DacMPair* old = self;
  return DacRangePush(old->data, old->data + 2,
                      "(,)", DacWrapperPush);
}

char* DacRangePull(const char* flow,
                   const char ogc[3],
                   DacMArray** self);

char* DacMPairPull(const char* flow, void* self)
{
  DacMArray* data;
  char *i = DacRangePull(flow, "(,)", &data);
  DacCheck(i == NULL, NULL);
  DacMPair* bud = DacMPairNew(DacMArrayGet(data, 0),
                              DacMArrayGet(data, 1));
  if (bud == NULL) {
    DacMArrayFree(data);
    return NULL;
  }
  DacMArrayFree(data);
  *(DacMPair**)self = bud;
  return i;
}

static DacType __DacMPairType = {
  DacMPairCopy,
  DacMPairFree,
  DacMPairVs,
  DacMPairHash,
  DacMPairPush,
  DacMPairPull
};
DacType* DacMPairType = &__DacMPairType;

DacMPair* DacMPairNew(DacWrapper* left, DacWrapper* right)
{
  DacMPair* bud = calloc(1, sizeof(DacMPair));
  DacCheck(bud == NULL, NULL);
  bud->data[0] = DacWrapperCopy(left);
  DacCheckAndFree(bud->data[0] == NULL, bud, NULL);
  bud->data[1] = DacWrapperCopy(right);
  if (bud->data[1] == NULL) {
    DacWrapperFree(bud->data[0]);
    free(bud);
    return NULL;
  }
  return bud;
}

DacWrapper* DacMPairGet(DacMPair* self, int vane)
{
  return self->data[vane];
}

int DacMPairSet(DacMPair* self, int vane, DacWrapper* data)
{
  DacWrapper* copy_data = DacWrapperCopy(data);
  DacCheck(copy_data == NULL, -1);
  DacWrapperFree(self->data[vane]);
  self->data[vane] = copy_data;
  return 0;
}
