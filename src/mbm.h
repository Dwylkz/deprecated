#ifndef DPA_MBM_H_
#define DPA_MBM_H_

#include "dpa.h"

typedef Map mb_map;

#define mb_map_new()          MapNew(meta_body_t, IntT)
#define mb_map_remove(x)      MapRemove(x)

#define mb_map_push(x, y)     { int id = 1; MapPush((x), (y), &id); }
#define mb_map_get(x, y)      (*(int*)MapGet((x), (y)))
#define mb_map_show(x) \
  for (int i = 0; i < MapSize(x); i++) {\
    meta_body *mb = MapPick((x), i + 1, MAP_KEY);\
    meta_body_show(mb); puts("");\
  } 

#endif // mbm.h
