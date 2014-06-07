#ifndef DAC_V2_ARRAY_H_
# define DAC_V2_ARRAY_H_

#include <Comm.h>
#include <MArray.h>

typedef struct DacArray {
  DacType* type;
  DacMArray* data;
} DacArray;

void* DacArrayCopy(void* self);
void DacArrayFree(void* self);
int DacArrayVs(void* self, void* that);
uint32_t DacArrayHash(void* self);
char* DacArrayPush(void* self);
char* DacArrayPull(const char* flow, void* self);
extern DacType* DacArrayType;

DacArray* DacArrayNew(DacType* type);

int DacArrayPushBack(DacArray* self, void* data, int times);

void DacArrayPopBack(DacArray* self, int times);

void* DacArrayGet(DacArray* self, int vane);
int DacArraySet(DacArray* self, int vane, void* data);

void DacArrayClear(DacArray* self);

#endif // DAC_V2_ARRAY_H_
