#include <MSet.h>
#include <Basic.h>
#include <MArray.h>

typedef struct Node {
  DacWrapper* data;
  uint32_t code;
  int next;
} Node;

static void NodeFree(int self, DacMSet* parent)
{
  if (parent->data[self].data != NULL)
    DacWrapperFree(parent->data[self].data);
  parent->data[self].data = NULL;
  parent->data[self].code = 0;
  parent->data[self].next = parent->free;
  parent->free = self;
}

static int ReHash(DacMSet* self)
{
  int volume = (self->volume + 1) * 2- 1;
  int* head = calloc(volume, sizeof(int));
  if (head == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  Node* data = realloc(self->data, volume * sizeof(Node));
  if (data == NULL)
    DacGoto(err_1, DAC_ERR_ALLOC);
  self->data = data;

  free(self->head);
  self->head = head;
  for (int i = 0; i < volume; i++)
    self->head[i] = -1;

  for (int i = 0; i < self->volume; i++) {
    int at = data[i].code % volume;
    self->data[i].next = self->head[at];
    self->head[at] = i;
  }

  for (int i = self->volume; i < volume; i++) {
    self->data[i].data = NULL;
    self->data[i].code = 0;
    if (i == volume - 1)
      self->data[i].next = -1; 
    else
      self->data[i].next = i + 1;
  }
  self->free = self->volume;

  self->volume = volume;
  return 0;
err_1:
  free(head);
err_0:
  return -1;
}

static int NodeNew(DacMSet* parent,
                   DacWrapper* data,
                   uint32_t code)
{
  DacWrapper* copy_data = DacWrapperCopy(data);
  if (copy_data == NULL)
    DacGoto(err_0, DAC_ERR_COPY);

  if (parent->free == -1 && ReHash(parent) != 0)
    DacGoto(err_1, DAC_ERR_REHASH);

  int slot = parent->free;
  parent->free = parent->data[parent->free].next;

  parent->data[slot].data = copy_data;
  parent->data[slot].code = code;

  int at = code % parent->volume;
  parent->data[slot].next = parent->head[at];
  parent->head[at] = slot;
  return 0;
err_1:
  DacWrapperFree(copy_data);
err_0:
  return -1;
}

static DacWrapper** Serialize(DacMSet* self)
{
  DacWrapper** bud = calloc(self->size, sizeof(DacWrapper*));
  if (bud == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  int idx = 0;
  for (int i = 0; i < self->volume; i++)
    if (self->data[i].data != NULL)
      bud[idx++] = self->data[i].data;
  return bud;
err_0:
  return NULL;
}

void* DacMSetCopy(void* self)
{
  DacMSet* from = self;
  DacMSet* bud = DacMSetNew();
  if (bud == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);
  
  for (int i = 0; i < from->volume; i++)
    if (from->data[i].data != NULL)
      if (DacMSetSearch(bud, from->data[i].data) == NULL)
        DacGoto(err_1, DAC_ERR_INSERT);
  return bud;
err_1:
  DacMSetFree(bud);
err_0:
  return NULL;
}

void DacMSetFree(void* self)
{
  DacMSetClear(self);
  free(self);
}

int DacMSetVs(void* self, void* that)
{
  DacMSet* lhs = self;
  DacMSet* rhs = that;
  int volume = DacMin(lhs->volume, rhs->volume);
  for (int i = 0; i < volume; i++) {
    int vane = DacIntVs(&lhs->data[i].code, &rhs->data[i].code);
    if (vane != 0)
      return vane;
  }
  return DacIntVs(&lhs->size, &rhs->size);
}

uint32_t DacMSetHash(void* self)
{
  uint32_t code = 0;
  DacMSet* old = self;
  for (int i = 0; i < old->volume; i++)
    code = code * 131 * old->data[i].code;
  return code;
}

char* DacRangePush(void* lower, void* upper,
                   const char ogc[3],
                   DacPush dac_push);

char* DacMSetPush(void* self)
{
  DacMSet* old = self;
  DacWrapper** data = Serialize(old);
  if (data == NULL)
    DacGoto(err_0, DAC_ERR_ALLOC);

  char* ret = DacRangePush(data, data + old->size,
                           "{,}", DacWrapperPush);
  if (ret == NULL)
    DacGoto(err_1, DAC_ERR_PUSH);

  free(data);
  return ret;
err_1:
  free(data);
err_0:
  return NULL;
}

char* DacRangePull(const char* flow,
                   const char ogc[3],
                   DacMArray** self);

char* DacMSetPull(const char* flow, void* self)
{
  DacMArray* from;
  char* i = DacRangePull(flow, "{,}", &from);
  if (i == NULL)
    DacGoto(err_0, DAC_ERR_PULL);

  DacMSet* bud = DacMSetNew();
  if (bud == NULL)
    DacGoto(err_1, DAC_ERR_ALLOC);

  for (int i = 0; i < from->size; i++)
    if (DacMSetSearch(bud, DacMArrayGet(from, i)) == NULL)
      DacGoto(err_2, DAC_ERR_INSERT);

  DacMArrayFree(from);
  *(DacMSet**)self = bud;
  return i;
err_2:
  DacMSetFree(bud);
err_1:
  DacMArrayFree(from);
err_0:
  return NULL;
}

static DacType __DacMSetType = {
  DacMSetCopy,
  DacMSetFree,
  DacMSetVs,
  DacMSetHash,
  DacMSetPush,
  DacMSetPull
};
DacType* DacMSetType = &__DacMSetType;

DacMSet* DacMSetNew()
{
  DacMSet* bud = calloc(1, sizeof(DacMSet));
  DacCheck(bud == NULL, NULL);
  bud->free = -1;
  return bud;
}

static int Hash(DacMSet* self, DacWrapper* data, int do_insert)
{
  if (self->volume == 0) {
    if (do_insert == 0)
      return -1;
    if (ReHash(self) != 0)
      DacGoto(err_0, DAC_ERR_REHASH);
  }

  uint32_t code = DacWrapperHash(data);
  int at = code % self->volume;
  for (int i = self->head[at]; i != -1; i = self->data[i].next)
    if (DacWrapperVs(self->data[i].data, data) == 0)
      return i;

  if (do_insert == 0)
    return -1;

  int slot = NodeNew(self, data, code);
  if (slot == -1)
    DacGoto(err_0, DAC_ERR_INSERT);

  self->size++;
  return slot;
err_0:
  return -1;
}

DacWrapper* DacMSetSearch(DacMSet* self, DacWrapper* data)
{
  int at = Hash(self, data, 1);
  if (at == -1)
    DacGoto(err_0, DAC_ERR_INSERT);
  return self->data[at].data;
err_0:
  return NULL;
}

DacWrapper* DacMSetFind(DacMSet* self, DacWrapper* data)
{
  int at = Hash(self, data, 0);
  if (at == -1)
    return NULL;
  return self->data[at].data;
}

int DacMSetRemove(DacMSet* self, DacWrapper* data)
{
  int slot = Hash(self, data, 0);
  if (slot == -1)
    return 0;

  int idx = self->data[slot].code % self->volume;
  int at = self->head[idx];
  while (self->data[at].next != -1
         && self->data[at].next != slot)
    at = self->data[at].next;

  if (self->data[at].next == -1)
    self->head[idx] = -1;
  else
    self->data[at].next = self->data[slot].next;
  NodeFree(slot, self);
  self->size--;
  return 0;
}

void DacMSetClear(DacMSet* self)
{
  for (int i = 0; i < self->volume; i++)
    if (self->data[i].data != NULL)
      DacWrapperFree(self->data[i].data);
  DacFree(&self->head, NULL);
  DacFree(&self->data, NULL);
  self->free = -1;
  self->volume = 0;
  self->size = 0;
}

static DacWrapper* Move(DacMSet* self, int* i, int vane)
{
  *i += vane;
  while (0 <= *i && *i < self->volume
         && self->data[*i].data == NULL)
    *i += vane;
  if (0 > *i || *i >= self->volume)
    return NULL;
  return self->data[*i].data;
}

DacWrapper* DacMSetForward(DacMSet* self, int* i)
{
  return Move(self, i, 1);
}

DacWrapper* DacMSetBackward(DacMSet* self, int* i)
{
  return Move(self, i, -1);
}
