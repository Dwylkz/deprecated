
#ifndef DAC_V2_STRINGSET_H_
# define DAC_V2_STRINGSET_H_

#include <Comm.h>
#include <Set.h>

typedef DacSet DacStringSet;

void* DacStringSetCopy(void* self);
void DacStringSetFree(void* self);
int DacStringSetVs(void* self, void* that);
uint32_t DacStringSetHash(void* self);
char* DacStringSetPush(void* self);
char* DacStringSetPull(const char* flow, void* self);
extern DacType* DacStringSetType;

DacStringSet* DacStringSetNew();

char* DacStringSetSearch(DacStringSet* self, char* data);

char* DacStringSetFind(DacStringSet* self, char* data);

int DacStringSetRemove(DacStringSet* self, char* data);

void DacStringSetClear(DacStringSet* self);

char* DacStringSetForward(DacStringSet* self, int* i);

char* DacStringSetBackward(DacStringSet* self, int* i);

#endif // DAC_V2_STRINGSET_H_
