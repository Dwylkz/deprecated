#ifndef MAP_H_
#define MAP_H_

#include "dac.h"

#define MAP_KEY 0
#define MAP_DATA 1

typedef struct MapNode {
  struct MapNode *to_[2];
  dac_int size_;
  void *key_,
       *data_;
} MapNode;
typedef struct Map {
  Type *keyt_,
       *datat_;
  MapNode *root_;
} Map;
extern Type *MapT;

Map *MapNew(Type *i_keyt_, Type *i_datat_);

void MapPush(Map *self, void *i_key, void *i_data);

void MapPop(Map *self, void *i_key);

void *MapGet(Map *self, void *i_key);

dac_int MapRank(Map *self, void *i_key);

void *MapPick(Map *self, dac_int i_idx, dac_int i_kd);

dac_int MapSize(Map *self);

void MapClear(Map *self);

void *MapRemove(void *self);

#endif // MAP_H_
