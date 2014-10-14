#include <tdsl_tree.h>

#define TDSL_EMKNODE "make node failed"
#define TDSL_EINSERT "insert node failed"

typedef struct node_t {
  void* data;
  struct node_t* to[2];
  int height;
  int size;
} node_t;

static node_t* make_node(void* data)
{
  node_t* bud = calloc(1, sizeof(node_t));
  if (bud == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);
  bud->data = data;
  bud->height = 1;
  bud->size = 1;
  return bud;
err_0:
  return NULL;
}

static int node_height(node_t* self)
{
  return self == NULL? 0: self->height;
}

static int node_size(node_t* self)
{
  return self == NULL? 0: self->size;
}

static int node_rank(node_t* self)
{
  return 1+node_size(self->to[0]);
}

static node_t* update_node(node_t* self)
{
  self->height = self->size = 1;
  for (int i = 0; i < 2; i++)
    if (self->to[i] != NULL) {
      self->size += self->to[i]->size;
      if (self->height < 1+self->to[i]->height)
        self->height = 1+self->to[i]->height;
    }
  return self;
}

tdsl_tree_t* tdsl_tnew(tdsl_compare_i compare)
{
  tdsl_tree_t* bud = calloc(1, sizeof(tdsl_tree_t));
  if (bud == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);

  bud->compare = compare;
  return bud;
err_0:
  return NULL;
}

void tdsl_tfree(tdsl_tree_t* self)
{
  tdsl_tclear(self);
  free(self);
}

static void tclear(node_t* self)
{
  if (self == NULL)
    return ;
  tclear(self->to[0]);
  tclear(self->to[1]);
  free(self);
}

void tdsl_tclear(tdsl_tree_t* self)
{
  tclear(self->root);
  self->root = NULL;
  self->size = 0;
}

static node_t* tspin(node_t* self, int vane)
{
  node_t* x = self->to[1-vane];
  self->to[1-vane] = x->to[vane];
  update_node(self);

  x->to[vane] = self;
  return update_node(x);
}

static node_t* tfine(node_t* self)
{
  int vane = node_height(self->to[1])-node_height(self->to[0]);
  if (-1 <= vane && vane <= 1)
    return update_node(self);

  vane = vane > 1;
  if (node_height(self->to[vane]->to[vane])
      < node_height(self->to[vane]->to[1-vane])) {
    self->to[vane] = tspin(self->to[vane], vane);
    update_node(self);
  }
  return tspin(self, 1-vane);
}

static node_t* tinsert(node_t* self, void* key, tdsl_compare_i compare)
{
  if (self == NULL) {
    node_t* bud = make_node(key);
    if (bud == NULL)
      TDSL_INFO(TDSL_EMKNODE);
    return bud;
  }

  int vane = compare(key, self->data) > 0;
  self->to[vane] = tinsert(self->to[vane], key, compare);
  return tfine(self);
}

void* tdsl_tsearch(tdsl_tree_t* self, void* key)
{
  void* ret = tdsl_tfind(self, key);
  if (ret == NULL) {
    int size = node_size(self->root);
    self->root = tinsert(self->root, key, self->compare);
    if (size == node_size(self->root))
      TDSL_GOTO(err_0, TDSL_EINSERT);

    self->size++;
    ret = key;
  }
  return ret;
err_0:
  return NULL;
}

static void* tfind(node_t* self, void* key, tdsl_compare_i compare)
{
  if (self == NULL)
    return NULL;

  int vane = compare(key, self->data);
  if (vane == 0)
    return self->data;

  return tfind(self->to[vane > 0], key, compare);
}

void* tdsl_tfind(tdsl_tree_t* self, void* key)
{
  return tfind(self->root, key, self->compare);
}

node_t* tremove(node_t* self, void* key, tdsl_compare_i compare)
{
  if (self == NULL)
    return NULL;

  int vane = compare(key, self->data);
  if (vane == 0) {
    vane = -1;
    if (self->to[0] != NULL)
      vane = 0;
    if (self->to[1] != NULL)
      vane = 1;

    if (vane == -1) {
      free(self);
      return NULL;
    }

    node_t* x = self->to[vane];
    while (x->to[1-vane] != NULL)
      x = x->to[1-vane];

    void* temp = x->data;
    x->data = self->data;
    self->data = temp;

    if (vane == 0)
      vane = -1;
  }

  vane = vane>0;
  self->to[vane] = tremove(self->to[vane], key, compare);
  return tfine(self);
}

void tdsl_tremove(tdsl_tree_t* self, void* key)
{
  self->root = tremove(self->root, key, self->compare);
  self->size = node_size(self->root);
}

static int tmap(node_t* self, tdsl_map_i map)
{
  int ret = 0;
  if (self == NULL)
    return 0;
  ret |= tmap(self->to[0], map);
  ret |= map(self->data);
  ret |= tmap(self->to[1], map);
  return ret;
}

int tdsl_tmap(tdsl_tree_t* self, tdsl_map_i map)
{
  int ret = tmap(self->root, map);
  if (ret == -1)
    TDSL_GOTO(err_0, TDSL_EMAP);
  return 0;
err_0:
  return -1;
}

static void* tselect(node_t* self, int rank) 
{
  if (self == NULL)
    return NULL;

  int lsize = node_rank(self);
  int vane = rank-lsize;
  if (vane == 0)
    return self->data;

  vane = vane>0;
  return tselect(self->to[vane], rank-vane*lsize);
}

void* tdsl_tselect(tdsl_tree_t* self, int rank)
{
  return tselect(self->root, rank+1);
}

#undef TDSL_EMKNODE
#undef TDSL_EINSERT
