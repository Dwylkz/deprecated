#ifndef DAC_V2_MPAIR_H_
# define DAC_V2_MPAIR_H_

#include <Comm.h>
#include <Wrapper.h>

typedef struct DacMPair {
  DacWrapper* data[2];
} DacMPair;

void* DacMPairCopy(void* self);
void DacMPairFree(void* self);
int DacMPairVs(void* self, void* that);
uint32_t DacMPairHash(void* self);
char* DacMPairPush(void* self);
char* DacMPairPull(const char* flow, void* self);
extern DacType* DacMPairType;

DacMPair* DacMPairNew(DacWrapper* left, DacWrapper* right);

DacWrapper* DacMPairGet(DacMPair* self, int vane);

int DacMPairSet(DacMPair* self, int vane, DacWrapper* data);

#endif // DAC_V2_MPAIR_H_
