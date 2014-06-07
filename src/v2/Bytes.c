#include <Bytes.h>
#include <Basic.h>

static int Resize(DacBytes* self, int size)
{
  int volume = DacMax(1, self->volume);
  while (volume < size + 2) volume *= 2;
  if (volume > self->volume) {
    char* copy_data = realloc(self->data, volume * sizeof(char));
    DacCheck(copy_data == NULL, -1);
    for (int i = self->volume; i < volume; i++)
      copy_data[i] = '\0';
    self->data = copy_data;
    self->volume = volume;
  }
  for (int i = size; i < self->size; i++)
    self->data[i] = '\0';
  self->size = size;
  return 0;
}

void* DacBytesCopy(void* self)
{
  DacBytes* old = self;
  return DacBytesNew(old->data);
}

void DacBytesFree(void* self)
{
  DacBytes* old = self;
  free(old->data);
  free(old);
}

int DacBytesVs(void* self, void* that)
{
  DacBytes* lhs = self;
  DacBytes* rhs = that;
  return strcmp(lhs->data, rhs->data);
}

uint32_t DacBytesHash(void* self)
{
  DacBytes* old = self;
  return DacStringHash(old->data);
}

char* DacBytesPush(void* self)
{
  DacBytes* old = self;
  return DacStringPush(old->data);
}

char* DacBytesPull(const char* flow, void* self)
{
  char* data;
  char* i = DacStringPull(flow, &data);
  DacCheck(i == NULL, NULL);
  DacBytes* bud = DacBytesNew(data);
  DacCheckAndFree(bud == NULL, data, NULL);
  free(data);
  *(DacBytes**)self = bud;
  return i;
}

static DacType __DacBytesType = {
  DacBytesCopy,
  DacBytesFree,
  DacBytesVs,
  DacBytesHash,
  DacBytesPush,
  DacBytesPull
};
DacType* DacBytesType = &__DacBytesType;

DacBytes* DacBytesNew(const char* data)
{
  DacBytes* bud = calloc(1, sizeof(DacBytes));
  DacCheck(bud == NULL, NULL);
  DacCheckAndFree(DacBytesCatString(bud, data) != 0, bud, NULL);
  return bud;
}

int DacBytesCat(DacBytes* self, DacBytes* data)
{
  return DacBytesCatString(self, data->data);
}

int DacBytesCatString(DacBytes* self, const char* data)
{
  char* copy_data = strdup(data);
  DacCheck(copy_data == NULL, -1);
  if (Resize(self, self->size + strlen(copy_data)+ 10) != 0) {
    free(copy_data);
    return -1;
  }
  strcat(self->data, copy_data);
  free(copy_data);
  return 0;
}

int DacBytesEatString(DacBytes* self, char* data)
{
  DacCheck(DacBytesCatString(self, data) != 0, -1);
  free(data);
  return 0;
}

char* DacBytesGet(DacBytes* self)
{
  return self->data;
}

int DacBytesSet(DacBytes* self, const char* data)
{
  char* copy_data = strdup(data);
  DacCheck(copy_data == NULL, -1);
  DacCheckAndFree(Resize(self, strlen(data)) != 0, copy_data, -1);
  DacFree(&self->data, copy_data);
  return 0;
}

int DacBytesSetFree(DacBytes* self, char* data)
{
  DacCheck(DacBytesSet(self, data) != 0, -1);
  free(data);
  return 0;
}

void DacBytesHalfFree(DacBytes* self)
{
  free(self);
}
