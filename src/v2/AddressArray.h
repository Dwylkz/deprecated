
#ifndef DAC_V2_ADDRESSARRAY_H_
# define DAC_V2_ADDRESSARRAY_H_

#include <Comm.h>
#include <Array.h>

typedef DacArray DacAddressArray;

void* DacAddressArrayCopy(void* self);
void DacAddressArrayFree(void* self);
int DacAddressArrayVs(void* self, void* that);
uint32_t DacAddressArrayHash(void* self);
char* DacAddressArrayPush(void* self);
char* DacAddressArrayPull(const char* flow, void* self);
extern DacType* DacAddressArrayType;

DacAddressArray* DacAddressArrayNew();

int DacAddressArrayPushBack(DacAddressArray* self, void* data, int times);

void DacAddressArrayPopBack(DacAddressArray* self, int times);

void* DacAddressArrayGet(DacAddressArray* self, int vane);

int DacAddressArraySet(DacAddressArray* self, int vane, void* data);

void DacAddressArrayClear(DacAddressArray* self);

#endif // DAC_V2_ADDRESSARRAY_H_
