#ifndef DAC_V2_INTSET_H_
# define DAC_V2_INTSET_H_

#include <Comm.h>
#include <Set.h>

typedef DacSet DacIntSet;

void* DacIntSetCopy(void* self);
void DacIntSetFree(void* self);
int DacIntSetVs(void* self, void* that);
uint32_t DacIntSetHash(void* self);
char* DacIntSetPush(void* self);
char* DacIntSetPull(const char* flow, void* self);
extern DacType* DacIntSetType;

DacIntSet* DacIntSetNew();

int* DacIntSetSearch(DacIntSet* self, int data);

int* DacIntSetFind(DacIntSet* self, int data);

int DacIntSetRemove(DacIntSet* self, int data);

void DacIntSetClear(DacIntSet* self);

int* DacIntSetForward(DacIntSet* self, int* i);

int* DacIntSetBackward(DacIntSet* self, int* i);

#endif // DAC_V2_INTSET_H_
