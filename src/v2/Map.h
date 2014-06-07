#ifndef DAC_V2_MAP_H_
# define DAC_V2_MAP_H_

#include <Comm.h>
#include <Set.h>
#include <Pair.h>

typedef struct DacMap {
  DacType* type[2];
  DacSet* data;
} DacMap;

void* DacMapCopy(void* self);
void DacMapFree(void* self);
int DacMapVs(void* self, void* that);
uint32_t DacMapHash(void* self);
char* DacMapPush(void* self);
char* DacMapPull(const char* flow, void* self);
extern DacType* DacMapType;

DacMap* DacMapNew(DacType* ltype, DacType* rtype);

int DacMapInsert(DacMap* self, void* key, void* value);

void* DacMapFind(DacMap* self, void* key);

int DacMapRemove(DacMap* self, void* key);

void DacMapClear(DacMap* self);

DacPair* DacMapForward(DacMap* self, int* i);

DacPair* DacMapBackward(DacMap* self, int* i);

#endif // DAC_V2_MAP_H_
