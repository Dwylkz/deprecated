null
//--
#ifndef ${GUARD}
# define ${GUARD}

#include <Comm.h>
#include <Array.h>

typedef DacArray Dac${TYPE};

void* Dac${TYPE}Copy(void* self);
void Dac${TYPE}Free(void* self);
int Dac${TYPE}Vs(void* self, void* that);
uint32_t Dac${TYPE}Hash(void* self);
char* Dac${TYPE}Push(void* self);
char* Dac${TYPE}Pull(const char* flow, void* self);
extern DacType* Dac${TYPE}Type;

Dac${TYPE}* Dac${TYPE}New();

int Dac${TYPE}PushBack(Dac${TYPE}* self, int data, int times);

void Dac${TYPE}PopBack(Dac${TYPE}* self, int times);

int Dac${TYPE}Get(Dac${TYPE}* self, int vane);

int Dac${TYPE}Set(Dac${TYPE}* self, int vane, int data);

void Dac${TYPE}Clear(Dac${TYPE}* self);

#endif // ${GUARD}
//--
#include <${TYPE}.h>
#include <Basic.h>

void* Dac${TYPE}Copy(void* self)
{
  return DacArrayCopy(self);
}

void Dac${TYPE}Free(void* self)
{
  return DacArrayFree(self);
}

int Dac${TYPE}Vs(void* self, void* that)
{
  return DacArrayVs(self, that);
}

uint32_t Dac${TYPE}Hash(void* self)
{
  return DacArrayHash(self);
}

char* Dac${TYPE}Push(void* self)
{
  return DacArrayPush(self);
}

char* Dac${TYPE}Pull(const char* flow, void* self)
{
  Dac${TYPE}* bud;
  char* i = DacArrayPull(flow, &bud);
  DacCheck(i == NULL, NULL);
  bud->type = DacIntType;
  *(Dac${TYPE}**)self = bud;
  return i;
}

static DacType __Dac${TYPE}Type = {
  Dac${TYPE}Copy,
  Dac${TYPE}Free,
  Dac${TYPE}Vs,
  Dac${TYPE}Hash,
  Dac${TYPE}Push,
  Dac${TYPE}Pull
};
DacType* Dac${TYPE}Type = &__Dac${TYPE}Type;

Dac${TYPE}* Dac${TYPE}New()
{
  return DacArrayNew(DacIntType);
}

int Dac${TYPE}PushBack(Dac${TYPE}* self, int data, int times)
{
  return DacArrayPushBack(self, &data, times);
}

void Dac${TYPE}PopBack(Dac${TYPE}* self, int times)
{
  DacArrayPopBack(self, times);
}

int Dac${TYPE}Get(Dac${TYPE}* self, int vane)
{
  return *(int*)DacArrayGet(self, vane);
}

int Dac${TYPE}Set(Dac${TYPE}* self, int vane, int data)
{
  return DacArraySet(self, vane, &data);
}

void Dac${TYPE}Clear(Dac${TYPE}* self)
{
  DacArrayClear(self);
}
