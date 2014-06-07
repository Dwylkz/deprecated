#ifndef DAC_V2_WRAPPER_H_
# define DAC_V2_WRAPPER_H_

#include <Comm.h>

typedef struct DacWrapper {
  DacType* type;
  void* data;
} DacWrapper;

void* DacWrapperCopy(void* self);
void DacWrapperFree(void* self);
int DacWrapperVs(void* self, void* that);
uint32_t DacWrapperHash(void* self);
char* DacWrapperPush(void* self);
char* DacWrapperPull(const char* flow, void* self);
extern DacType* DacWrapperType;

DacWrapper* DacWrapperNew(DacType* type, void* data);

void* DacWrapperGet(DacWrapper* self);

int DacWrapperSet(DacWrapper* self, DacType* type, void* data);

void* DacWrapperExport(DacWrapper* self);

#endif // DAC_V2_WRAPPER_H_
