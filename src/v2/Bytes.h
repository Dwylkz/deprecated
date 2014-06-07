#ifndef DAC_V2_BYTES_H_
# define DAC_V2_BYTES_H_

#include <Comm.h>

typedef struct DacBytes {
  char* data;
  int size;
  int volume;
} DacBytes;

void* DacBytesCopy(void* self);
void DacBytesFree(void* self);
int DacBytesVs(void* self, void* that);
uint32_t DacBytesHash(void* self);
char* DacBytesPush(void* self);
char* DacBytesPull(const char* flow, void* self);
extern DacType* DacBytesType;

DacBytes* DacBytesNew(const char* data);

int DacBytesCat(DacBytes* self, DacBytes* data);

int DacBytesCatString(DacBytes* self, const char* data);

int DacBytesEatString(DacBytes* self, char* data);

char* DacBytesGet(DacBytes* self);

int DacBytesSet(DacBytes* self, const char* data);

void DacBytesHalfFree(DacBytes* self);

#endif // DAC_V2_BYTES_H_
