#ifndef DPA_NB_H_
#define DPA_NB_H_

#include "dpa.h"

typedef Array nonterm_base;

#define nb_new()        ArrayNew(IntT)
#define nb_remove(x)    ArrayRemove(x)

#define nb_push(x, y)   { int t = y; ArrayPush((x), &t); }
#define nb_get(x, y)    (*(int*)ArrayGet((x), (y)))
#define nb_size(x)      ArraySize(x)

#endif // nb.h
