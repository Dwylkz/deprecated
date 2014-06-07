#ifndef DPA_L1P_H_
#define DPA_L1P_H_

#include "l1t.h"
#include "tl.h"
#include "pstack.h"

#define __uni_start_state     0
#define __uni_ac_action       -1
#define __PLOG                0

// Auxiliary function interface
typedef void (*initfp)(void *istream);
typedef int (*lookfp)(void *istream);
typedef void *(*shiftfp)(void *istream);
typedef struct istream_i {
  initfp init;
  lookfp look;
  shiftfp shift;
} istream_i;

typedef void (*actionfp)(
    int id,
    pstack *stack,
    void *istream,
    istream_i *ii);

// LALR(1) Parser
int parser(
    void *istream,
    istream_i *ii,
    lalr_1_table *table,
    actionfp action);

#endif // l1p.h
