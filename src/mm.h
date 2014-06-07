#ifndef DPA_MM_H_
#define DPA_MM_H_

#include "dpa.h"
// #include "mbs.h" // this will lead to circular dependency

#include <dac/Map.h>

typedef Map mbs_map;              // Map<String, meta_body_set>

#define mbs_map_new()             MapNew(StringT, meta_body_set_t)
#define mbs_map_remove(x)         MapRemove(x)

#define mbs_map_push(x, y, z)     MapPush((x), (y), (z))
#define mbs_map_get(x, y)         ((meta_body_set*)MapGet((x), (y)))
#define mbs_map_size(x)           MapSize(x)

#define mbs_map_show(x) \
  for (int i = 0; i < mbs_map_size(x); i++) {\
    char *meta = MapPick((x), i + 1, MAP_KEY);\
    meta_body_set *mbs = MapPick((x), i + 1, MAP_DATA);\
    printf("%4s::=", meta); mbs_show(mbs); puts("");\
  }

#endif // mm.h
