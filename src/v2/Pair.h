#ifndef DAC_V2_PAIR_H_
# define DAC_V2_PAIR_H_

#include <Comm.h>
#include <MPair.h>

typedef DacMPair DacPair;

void* DacPairCopy(void* self);
void DacPairFree(void* self);
int DacPairVs(void* self, void* that);
uint32_t DacPairHash(void* self);
char* DacPairPush(void* self);
char* DacPairPull(const char* flow, void* self);
extern DacType* DacPairType;

DacPair* DacPairNew(DacType* ltype,
                    void* ldata,
                    DacType* rtype,
                    void* rdata);

void* DacPairGet(DacPair* self, int vane);

int DacPairSet(DacPair* self, int vane, void* data);

#endif // DAC_V2_PAIR_H_
