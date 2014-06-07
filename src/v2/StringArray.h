
#ifndef DAC_V2_STRINGARRAY_H_
# define DAC_V2_STRINGARRAY_H_

#include <Comm.h>
#include <Array.h>

typedef DacArray DacStringArray;

void* DacStringArrayCopy(void* self);
void DacStringArrayFree(void* self);
int DacStringArrayVs(void* self, void* that);
uint32_t DacStringArrayHash(void* self);
char* DacStringArrayPush(void* self);
char* DacStringArrayPull(const char* flow, void* self);
extern DacType* DacStringArrayType;

DacStringArray* DacStringArrayNew();

int DacStringArrayPushBack(DacStringArray* self, const char* data, int times);

void DacStringArrayPopBack(DacStringArray* self, int times);

char* DacStringArrayGet(DacStringArray* self, int vane);

int DacStringArraySet(DacStringArray* self, int vane, const char* data);

void DacStringArrayClear(DacStringArray* self);

#endif // DAC_V2_STRINGARRAY_H_
