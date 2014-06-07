
#ifndef DAC_V2_ADDRESSSET_H_
# define DAC_V2_ADDRESSSET_H_

#include <Comm.h>
#include <Set.h>

typedef DacSet DacAddressSet;

void* DacAddressSetCopy(void* self);
void DacAddressSetFree(void* self);
int DacAddressSetVs(void* self, void* that);
uint32_t DacAddressSetHash(void* self);
char* DacAddressSetPush(void* self);
char* DacAddressSetPull(const char* flow, void* self);
extern DacType* DacAddressSetType;

DacAddressSet* DacAddressSetNew();

void* DacAddressSetSearch(DacAddressSet* self, void* data);

void* DacAddressSetFind(DacAddressSet* self, void* data);

int DacAddressSetRemove(DacAddressSet* self, void* data);

void DacAddressSetClear(DacAddressSet* self);

void* DacAddressSetForward(DacAddressSet* self, int* i);

void* DacAddressSetBackward(DacAddressSet* self, int* i);

#endif // DAC_V2_ADDRESSSET_H_
