#ifndef DPA_SSTACK_H_
#define DPA_SSTACK_H_

typedef List sstack;

#define sstack_new()          ListNew(IntT)
#define sstack_remove(x)      ListRemove(x);

// push a state
#define sstack_push(x, y)     StackPush((x), &(y))
// pop top state
#define sstack_pop(x)         StackPop(x);
// get top state
#define sstack_top(x)         (*(int*)StackTop(x))

#endif // sstack.h
