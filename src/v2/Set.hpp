null
//--
#ifndef ${GUARD}
# define ${GUARD}

#include <Comm.h>
#include <Set.h>

typedef DacSet Dac${TYPE};

void* Dac${TYPE}Copy(void* self);
void Dac${TYPE}Free(void* self);
int Dac${TYPE}Vs(void* self, void* that);
uint32_t Dac${TYPE}Hash(void* self);
char* Dac${TYPE}Push(void* self);
char* Dac${TYPE}Pull(const char* flow, void* self);
extern DacType* Dac${TYPE}Type;

Dac${TYPE}* Dac${TYPE}New();

int* Dac${TYPE}Search(Dac${TYPE}* self, int data);

int* Dac${TYPE}Find(Dac${TYPE}* self, int data);

int Dac${TYPE}Remove(Dac${TYPE}* self, int data);

void Dac${TYPE}Clear(Dac${TYPE}* self);

int* Dac${TYPE}Forward(Dac${TYPE}* self, int* i);

int* Dac${TYPE}Backward(Dac${TYPE}* self, int* i);

#endif // ${GUARD}
//--
#include <${TYPE}.h>
#include <Basic.h>

void* Dac${TYPE}Copy(void* self)
{
  return DacSetCopy(self);
}

void Dac${TYPE}Free(void* self)
{
  DacSetFree(self);
}

int Dac${TYPE}Vs(void* self, void* that)
{
  return DacSetVs(self, that);
}

uint32_t Dac${TYPE}Hash(void* self)
{
  return DacSetHash(self);
}

char* Dac${TYPE}Push(void* self)
{
  return DacSetPush(self);
}

char* Dac${TYPE}Pull(const char* flow, void* self)
{
  Dac${TYPE}* bud;
  char* i = DacSetPull(flow, &bud);
  if (i == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  bud->type = DacIntType;
  *(Dac${TYPE}**)self = bud;
  return i;
err_0:
  return NULL;
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
  return DacSetNew(DacIntType);
}

int* Dac${TYPE}Search(Dac${TYPE}* self, int data)
{
  return DacSetSearch(self, &data);
}

int* Dac${TYPE}Find(Dac${TYPE}* self, int data)
{
  return DacSetFind(self, &data);
}

int Dac${TYPE}Remove(Dac${TYPE}* self, int data)
{
  return DacSetRemove(self, &data);
}

void Dac${TYPE}Clear(Dac${TYPE}* self)
{
  DacSetClear(self);
}

int* Dac${TYPE}Forward(Dac${TYPE}* self, int* i)
{
  return DacSetForward(self, i);
}

int* Dac${TYPE}Backward(Dac${TYPE}* self, int* i)
{
  return DacSetBackward(self, i);
}
