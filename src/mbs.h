#ifndef DPA_MBS_H_
#define DPA_MBS_H_

#include "dpa.h"
#include "mb.h"

typedef Array meta_body_set;

#define mbs_new()       ArrayNew(meta_body_t)
#define mbs_remove(x)   ArrayRemove(x)

#define mbs_push(x, y)  ArrayPush((x), (y))
#define mbs_get(x, y)   ((meta_body*)ArrayGet((x), (y)))
#define mbs_uni(x, y)   ArrayCat((x), (y))
#define mbs_size(x)     ArraySize(x)
#define mbs_clear(x)    ArrayClear(x)

#define mbs_show(x) \
  for (int i = 0; i < mbs_size(x); i++) {\
    meta_body_show(mbs_get(x, i));\
    printf(i < mbs_size(x) - 1? " | ": "\n");\
  }

#define meta_body_set_t ArrayT

#endif // mbs.h
