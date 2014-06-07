#ifndef GS_H_
#define GS_H_

#include "dpa.h"

// Grammar Symbol
typedef int grammar_symbol;

#define __gs_tmask            0x80000000
#define __gs_terminal         0x00000000
#define __gs_nonterminal      0x80000000

#define __gs_nmask            0x40000000

#define __gs_dmask            0x3fffffff

#define gs_set_ttype(x, y)    (((x) & ~__gs_tmask) | (y))
#define gs_get_ttype(x)       ((x) & __gs_tmask)

#define gs_set_data(x, y)     (((x) & ~__gs_dmask) | (y))
#define gs_get_data(x)        ((x) & __gs_dmask)

#define grammar_symbol_t      IntT

#define __uni_endless_story   128

#endif // gs.h
