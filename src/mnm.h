#ifndef DPA_MNM_H_
#define DPA_MNM_H_

#include "dpa.h"

typedef Map mn_map;

#define mn_map_new()          MapNew(StringT, IntT)
#define mn_map_remove(x)      MapRemove(x)

#define mn_map_push(x, y, z)  { int id = (z); MapPush((x), (y), &id); }
#define mn_map_get(x, y)      (*(int*)MapGet((x), (y)))
#define mn_map_show(x) \
  for (int i = 0; i < MapSize(x); i++) {\
    char *name = MapPick((x), i + 1, MAP_KEY);\
    int id = *(int*)MapPick((x), i + 1, MAP_DATA);\
    printf("\t%30s->%4d\n", name, id);\
  }

#endif // mnm.h
