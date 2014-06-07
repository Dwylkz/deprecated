#ifndef DAC_V2_INTARRAY_H_
# define DAC_V2_INTARRAY_H_

#include <Comm.h>
#include <Array.h>

typedef DacArray DacIntArray;

void* DacIntArrayCopy(void* self);
void DacIntArrayFree(void* self);
int DacIntArrayVs(void* self, void* that);
uint32_t DacIntArrayHash(void* self);
char* DacIntArrayPush(void* self);
char* DacIntArrayPull(const char* flow, void* self);
extern DacType* DacIntArrayType;

DacIntArray* DacIntArrayNew();

int DacIntArrayPushBack(DacIntArray* self, int data, int times);

void DacIntArrayPopBack(DacIntArray* self, int times);

int* DacIntArrayGet(DacIntArray* self, int vane);

int DacIntArraySet(DacIntArray* self, int vane, int data);

void DacIntArrayClear(DacIntArray* self);

#endif // DAC_V2_INTARRAY_H_
