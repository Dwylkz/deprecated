#ifndef DPA_LR1A_H_
#define DPA_LR1A_H_

#include "dpa.h"
#include "grammar.h"
#include "gs.h"

typedef struct lr1_automaton {
  grammar *ag;      // augment grammar
  Map *is;          // LR(1) item sets Map<BitSet, IntT>
  Array *lh,        // lookaheads Array<Array<grammar_symbol>>
        *base,      // base index of production Array<IntT>
        *check;     // check specific index's lord(production) Array<IntT>
} lr1_automaton;

/* lr1_automaton is a structure like this
 *
 * ag = {                      is = {
 *   ...,                        ...,
 *   ag[j] = { meta, body },     { {.., iteam_id, ...}, iteam_set_id },
 *   ...                           +-----------------+
 * }                               | A bitset which  |
 *                                 | as keyword,     |
 *                                 | stores kernal   |
 *                                 | iteams' id.     |
 *                                 +----------+------+
 *                               ...
 *                             }
 * 
 * lh = {
 *   ...,
 *   { .., lh[i] = { ..., terminal_gs, ... }, ...},
 *   ...
 * }
 *
 * check = {
 *   ...,
 *   check[i] = j,
 *   ...
 * }
 *
 * base = {
 *   ...,
 *   base[j],
 *   ...
 * }
 *
 * */

#endif // lr1a.h
