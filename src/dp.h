#ifndef DPA_DP_H_
#define DPA_DP_H_

#include "dpa.h"
#include "parser.h"
#include "gb.h"

lalr_1_table *hand_make_table();

// syntatic-directed translation
void sdt_init();
void sdt_preprocess(int id, pstack *stack, void *istream, istream_i *ii);
void sdt_action(int id, pstack *stack, void *istream, istream_i *ii);
grammar_buffer *sdt_end();

extern istream_i *tokens_ii;

#endif // dp.h
