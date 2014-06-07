#ifndef DAC_V2_MSET_H_
# define DAC_V2_MSET_H_

#include <Comm.h>
#include <Wrapper.h>

typedef struct DacMSet {
  int* head;
  struct Node* data;
  int free;
  int volume;
  int size;
} DacMSet;

void* DacMSetCopy(void* self);
void DacMSetFree(void* self);
int DacMSetVs(void* self, void* that);
uint32_t DacMSetHash(void* self);
char* DacMSetPush(void* self);
char* DacMSetPull(const char* flow, void* self);
extern DacType* DacMSetType;

DacMSet* DacMSetNew();

DacWrapper* DacMSetSearch(DacMSet* self, DacWrapper* data);

DacWrapper* DacMSetFind(DacMSet* self, DacWrapper* data);

int DacMSetRemove(DacMSet* self, DacWrapper* data);

void DacMSetClear(DacMSet* self);

DacWrapper* DacMSetForward(DacMSet* self, int* i);

DacWrapper* DacMSetBackward(DacMSet* self, int* i);

#endif // DAC_V2_MSET_H_
