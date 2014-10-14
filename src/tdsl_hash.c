#include <tdsl_hash.h>

#define TDSL_EREHASH "rehash failed"
#define TDSL_EMKNODE "make node failed"
#define TDSL_EINSERT "insert node failed"

typedef struct node_t {
  void* data;
  int to;
  uint32_t code;
} node_t;

tdsl_hash_t* tdsl_hnew(tdsl_hash_i hash, tdsl_compare_i compare)
{
  tdsl_hash_t* bud = calloc(1, sizeof(tdsl_hash_t));
  if (bud == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);

  bud->freed = -1;
  bud->hash = hash;
  bud->compare = compare;
  return bud;
err_0:
  return NULL;
}

void tdsl_hfree(tdsl_hash_t* self)
{
  tdsl_hclear(self);
  free(self);
}

static void free_node(tdsl_hash_t* self, int slot)
{
  self->data[slot].data = NULL;
  self->data[slot].code = 0;
  self->data[slot].to = self->freed;
  self->freed = slot;
}

static int rehash(tdsl_hash_t* self)
{
  int volume = (self->volume+1)*2-1;
  int* head = calloc(volume, sizeof(int));
  if (head == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);
  for (int i = 0; i < volume; i++)
    head[i] = -1;

  node_t* data = realloc(self->data, volume*sizeof(node_t));
  if (data == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);
  free(self->head);
  self->head = head;
  self->data = data;

  for (int i = self->volume; i < volume; i++)
    free_node(self, i);

  for (int i = 0; i < self->volume; i++) {
    int at = self->data[i].code%volume;
    self->data[i].to = self->head[at];
    self->head[at] = i;
  }
  self->volume = volume;
  return 0;
err_1:
  free(head);
err_0:
  return -1;
}

static int make_node(tdsl_hash_t* self, void* elem, uint32_t code)
{
  if (self->freed == -1 && rehash(self) == -1)
    TDSL_GOTO(err_0, TDSL_EREHASH);

  int slot = self->freed;
  self->freed = self->data[self->freed].to;
  self->data[slot].data = elem;
  self->data[slot].code = code;
  self->data[slot].to = -1;
  return slot;
err_0:
  return -1;
}

static int hash_in(tdsl_hash_t* self, void* elem, int do_insert)
{
  if (self->volume == 0) {
    if (do_insert == 0)
      return -1;
    if (rehash(self) == -1)
      TDSL_GOTO(err_0, TDSL_EREHASH);
  }

  uint32_t code = self->hash(elem);
  int at = code%self->volume;
  for (int p = self->head[at]; p != -1; p = self->data[p].to)
    if (self->compare(self->data[p].data, elem) == 0)
      return p;

  if (do_insert == 0)
    return -1;

  int slot = make_node(self, elem, code);
  if (slot == -1)
    TDSL_GOTO(err_0, TDSL_EMKNODE);

  at = code%self->volume;
  self->data[slot].to = self->head[at];
  self->head[at] = slot;
  return slot;
err_0:
  return -1;
}

void* tdsl_hsearch(tdsl_hash_t* self, void* elem)
{
  int slot = hash_in(self, elem, 1);
  if (slot == -1)
    TDSL_GOTO(err_0, TDSL_EINSERT);
  return self->data[slot].data;
err_0:
  return NULL;
}

void* tdsl_hfind(tdsl_hash_t* self, void* elem)
{
  int slot = hash_in(self, elem, 0);
  return slot == -1? NULL: self->data[slot].data;
}

void tdsl_hremove(tdsl_hash_t* self, void* elem)
{
  int slot = hash_in(self, elem, 0);
  if (slot == -1)
    return ;

  int* prev = self->head+self->data[slot].code%self->volume;
  while (*prev != slot)
    prev = &self->data[*prev].to;
  *prev = self->data[*prev].to;
  free_node(self, slot);
}

void tdsl_hclear(tdsl_hash_t* self)
{
  free(self->head);
  free(self->data);
  self->head = NULL;
  self->data = NULL;
  self->freed = -1;
  self->volume = 0;
}

int tdsl_hmap(tdsl_hash_t* self, tdsl_map_i map)
{
  for (int i = 0; i < self->volume; i++)
    if (self->data[i].data != NULL
        && map(self->data[i].data) == -1)
        TDSL_GOTO(err_0, TDSL_EMAP);
  return 0;
err_0:
  return -1;
}

#undef TDSL_EREHASH
#undef TDSL_EMKNODE
#undef TDSL_EINSERT
