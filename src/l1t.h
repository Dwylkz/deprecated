#ifndef DPA_L1T_H_
#define DPA_L1T_H_

#include <dac/Array.h>
#include <dac/Map.h>
#include "grammar.h"
#include "lr1a.h"

#define L1T_MAGIC 0xdadadada

typedef struct lalr_1_table {
  int term_num,
      term_map[SIGMA_SIZE], // map term to column index
      nonterm_num,
      prod_num,
      state_num,
      eai;                  // extend action number
  Array *table,             // LALR(1) parse table
        *reducing_index,    // production's reducing index
        *reducing_length;   // production's reducing length
  lr1_automaton *la;        // LALR(1) automaton
} lalr_1_table;

/* lalr_1_table is a structure like this:
 *   
 *            +-             -+
 *            |  ...  mi, ... |
 *            |     .         |
 *            |      .        |
 *   table =  |       ri------+-------+
 *            |        .      |       |
 *            |         .     |       |
 *            |          ...  |       |
 *            +-             -+       |
 *                                    |
 *                                    |
 *                            +-------+--------------------+
 *                            |                            |
 *                            |                            |
 *                            V                            |
 *   reducing_length = { ..., production_i's length, ...}  |
 *                                                         |
 *                        +--------------------------------+
 *                        |
 *                        V
 *   meta_index = { ..., production_i's meta-index, ... }
 *   
 *   The reason for reducing_length's existence, is when a parser call
 *   reducing action, the state stack need to pop specific number states
 *   which equal to corresponding production's length.
 *
 * lalr_1_table file format:
 * 
 *   +-------------+-------------+------------------------+-------------+------------->
 *   | sizeof(int) | sizeof(int) | sizeof(int)*SIGMA_SIZE | sizeof(int) | sizeof(int) 
 *   +-------------+-------------+------------------------+-------------+------------->
 *   | L1T_MAGIC   | term_num    | term_map               | nonterm_num | prod_num    
 *   +-------------+-------------+------------------------+-------------+------------->
 *
 *   >+-------------+-------------------------------------------+-------------+---------------------->
 *      sizeof(int) | sizeof(int)  table_size * 3 * sizeof(int) | sizeof(int) | rl_size * sizeof(int) 
 *   >+-------------+-------------------------------------------+-------------+---------------------->
 *      eai         | table_size       goto(s, i) = m           | rl_size     |   reducing_lengths    
 *   >+-------------+-------------------------------------------+-------------+----------------------> 
 *
 *   >------------------------------------+
 *     lr1a_to_file(la)                   |
 *   >------------------------------------+
 *                                        |
 *   >------------------------------------+ 
 *
 * */

#define __motion_mask              0xC0000000
#define __motion_goto              0x00000000
#define __motion_shift             0x40000000
#define __motion_reduce            0x80000000
#define __motion_error             0xC0000000
#define __motion_accept            (~__motion_mask)

#define motion_get_index(x)        ((x) & ~__motion_mask)
#define motion_get_type(x)         ((x) & __motion_mask)
#define motion_set_type(x, y)      (((x) & ~__motion_mask) | (y))
#define motion_show(head, x,...) \
  printf(head "%3d%c" __VA_ARGS__,\
      (motion_get_index(x) == __motion_accept? -1:\
       motion_get_index(x)),\
      (motion_get_type(x) == __motion_shift? 's':\
       motion_get_type(x) == __motion_reduce? 'r': ' '))

lalr_1_table *l1t_new();
void *l1t_remove(void *x);

// create a table from grammar
lalr_1_table *l1t_from_grammar(grammar *x);
// create a table from ifile
lalr_1_table *l1t_from_file(FILE *ifile);
// put table to ofile
void l1t_to_file(lalr_1_table *x, FILE *ofile);
// return goto[s, i]
int l1t_goto(lalr_1_table *x, int s, int i);
// return meta index which reduce number i represent
int l1t_get_mi(lalr_1_table *x, int i);
// get producetion i's body length
int l1t_get_rl(lalr_1_table *x, int i);
// set goto[s][i] = m;
void l1t_push(lalr_1_table *x, int s, int i, int m);
// Print table x to a matrix attaching basic info
void l1t_show(lalr_1_table *x);

#endif // l1t.h
