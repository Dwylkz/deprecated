#ifndef DPA_PS_H_
#define DPA_PS_H_

#include "dpa.h"
#include "production.h"

typedef Array production_set;

#define ps_new()        ArrayNew(production_t)
#define ps_remove(x)    ArrayRemove(x)

#define ps_push(x, y)   ArrayPush((x), (y))
#define ps_get(x, y)    ((production*)ArrayGet((x), (y)))
#define ps_size(x)      ArraySize(x)

#endif // ps.h
