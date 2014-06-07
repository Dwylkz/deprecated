#ifndef DPA_MN_H_
#define DPA_MN_H_

#include "dpa.h"
#include <dac/Array.h>

typedef Array meta_name;            // Array<String>

#define meta_name_new()             ArrayNew(StringT)
#define meta_name_remove(x)         ArrayRemove(x)

#define meta_name_push(x, y)        ArrayPush((x), (y))
#define meta_name_get(x, y)         ((char*)ArrayGet((x), (y)))
#define meta_name_size(x)           ArraySize(x)

#define meta_name_show(x) \
  for (int i = 0; i < meta_name_size(x); i++) {\
    printf("%4d->%-64s\n", i, meta_name_get((x), i));\
  }

#endif // mm.h
