#ifndef DAC_V2_MARRAY_H_
# define DAC_V2_MARRAY_H_

#include <Comm.h>
#include <Wrapper.h>

typedef struct DacMArray {
  DacWrapper** data;
  int volume;
  int size;
} DacMArray;
void* DacMArrayCopy(void* self);
void DacMArrayFree(void* self);
int DacMArrayVs(void* self, void* that);
uint32_t DacMArrayHash(void* self);
char* DacMArrayPush(void* self);
char* DacMArrayPull(const char* flow, void* self);
extern DacType* DacMArrayType;

DacMArray* DacMArrayNew();

void DacMArrayHalfFree(DacMArray* self);

int DacMArrayPushBack(DacMArray* self, DacWrapper* data, int times);

void DacMArrayPopBack(DacMArray* self, int times);

DacWrapper* DacMArrayGet(DacMArray* self, int vane);

int DacMArraySet(DacMArray* self, int vane, DacWrapper* data);

void DacMArrayClear(DacMArray* self);

#endif
