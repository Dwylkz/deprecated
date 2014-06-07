#ifndef DAC_V2_SET_H_
# define DAC_V2_SET_H_

#include <Comm.h>
#include <MSet.h>

typedef struct DacSet {
  DacType* type;
  DacMSet* data;
} DacSet;

void* DacSetCopy(void* self);
void DacSetFree(void* self);
int DacSetVs(void* self, void* that);
uint32_t DacSetHash(void* self);
char* DacSetPush(void* self);
char* DacSetPull(const char* flow, void* self);
extern DacType* DacSetType;

DacSet* DacSetNew(DacType* type);

void* DacSetSearch(DacSet* self, void* data);

void* DacSetFind(DacSet* self, void* data);

int DacSetRemove(DacSet* self, void* data);

void DacSetClear(DacSet* self);

void* DacSetForward(DacSet* self, int* i);

void* DacSetBackward(DacSet* self, int* i);

#endif // DAC_V2_SET_H_
