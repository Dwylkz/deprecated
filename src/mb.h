#ifndef DPA_MB_H_
#define DPA_MB_H_

#include "dpa.h"
#include "gs.h"
#include "gb.h"

#include <dac/Array.h>

typedef Array meta_body;        // Array<grammar_symbol>

#define meta_body_new()         ArrayNew(grammar_symbol_t)
#define meta_body_remove(x)     ArrayRemove(x)

#define meta_body_push(x, y)    { int id = (y); ArrayPush((x), &id); }
#define meta_body_get(x, y)     (*(int*)ArrayGet((x), (y)))
#define meta_body_cat(x, y)     ArrayCat((x), (y))
#define meta_body_size(x)       ArraySize(x)
#define meta_body_copy(x)       ArrayCopy(x)
#define meta_body_clear(x)      ArrayClear(x)

meta_body *meta_body_sub(meta_body *x, meta_body *y, grammar_buffer *z);
void meta_body_show(meta_body *x);

#define meta_body_t             ArrayT

#endif // mb.h
