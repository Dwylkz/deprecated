#ifndef DPA_PSTACK_H_
#define DPA_PSTACK_H_

#include <dac/List.h>

typedef Array pstack; // Array<AddrT>

#define pstack_new()            ArrayNew(AddrT)
#define pstack_remove(x)        ArrayRemove(x)

// lookat the last yth elements in pstack
#define pstack_lookat(x, y)     ArrayGet((x), ArraySize(x) - (y) - 1)
// put an elements above pstack's top
#define pstack_push(x, y)       ArrayPush((x), (y))
// pop the toppest element
#define pstack_pop(x)           ArrayPop(x)
// pop the toppest y elements
#define pstack_npop(x, y)       { for (int i = 0; i < (y); i++) { ArrayPop(x); } }
// get size
#define pstack_size(x)          ArraySize(x)

#endif // pstack.h
