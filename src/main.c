#include "dpa.h"
#include "la.h"
#include "tl.h"
#include "parser.h"
#include "dp.h"
#include "gs.h"

#define hputs(x)    printf("%s%-30s%s", "\n-----------------[ ", x, " ]-----------------\n")

#if NDEBUG

#include "mb.h"
#include "mbs.h"
#include "production.h"
#include "mn.h"
#include "mm.h"
#include "gb.h"
#include "grammar.h"

int p[][20] = {
  // <S>::=<P>
  {2, __gs_nonterminal + 0, __gs_nonterminal + 1},
  // <P>::=<P><E>
  {3, __gs_nonterminal + 1, __gs_nonterminal + 1, __gs_nonterminal + 2},
  // <P>::=
  {1, __gs_nonterminal + 1},
  // <E>::="m""="<T>";"
  {5, __gs_nonterminal + 2, __gs_terminal + 'm',
    __gs_terminal + '=', __gs_nonterminal + 3, __gs_terminal + ';'},
  // <T>::=<T>"|"<C>
  {4, __gs_nonterminal + 3, __gs_nonterminal + 3,
    __gs_terminal + '|', __gs_nonterminal + 4},
  // <T>::=<C>
  {2, __gs_nonterminal + 3, __gs_nonterminal + 4},
  // <C>::=<C>","<X>
  {4, __gs_nonterminal + 4, __gs_nonterminal + 5,
    __gs_terminal + ',', __gs_nonterminal + 6},
  // <C>::=<X>
  {2, __gs_nonterminal + 5, __gs_nonterminal + 6},
  // <X>::=<X>"-"<F>
  {4, __gs_nonterminal + 4, __gs_nonterminal + 5,
    __gs_terminal + '-', __gs_nonterminal + 6},
  // <X>::=<F>
  {2, __gs_nonterminal + 6, __gs_nonterminal + 6},
  // <F>::='m'
  {2, __gs_nonterminal + 6, __gs_terminal + 'm'},
  // <F>::="s"
  {2, __gs_nonterminal + 6, __gs_terminal + 's'},
  // <F>::=
  {1, __gs_nonterminal + 6}
},
  lp = sizeof(p) / sizeof(p[0]);
char name[][20] = {
  "S", "P", "E", "T", "C", "X", "F"
};
int lname = sizeof(name) / sizeof(name[0]);
#define mb_install(x, y) \
  for (int i = 2; i <= p[y][0]; i++) {\
    meta_body_push((x), p[y][i]);\
  }
#define mbs_install(x, y, z) {\
  mbs_clear(x);\
  for (int j = (y); j < (z); j++) {\
    meta_body *mb = meta_body_new();\
    mb_install(mb, j);\
    mbs_push((x), mb);\
    meta_body_remove(mb);\
  }\
}
#define prod_install(x, w, y, z) {\
  meta_body_set *mbs = mbs_new();\
  mbs_install(mbs, (y), (z));\
  (x) = prod_new((w), mbs);\
  mbs_remove(mbs);\
}
#define mn_install(x) \
  for (int i = 0; i < lname; i++) {\
    meta_name_push((x), name[i]);\
  }


void mb_test()
{
  meta_body *mb1 = meta_body_new(),
            *mb2;

  hputs("mb_test");

  mb_install(mb1, 4);
  meta_body_show(mb1), puts("");

  mb2 = meta_body_copy(mb1);
  meta_body_show(mb2), puts("");

  meta_body_cat(mb1, mb2);
  meta_body_show(mb1), puts("");

  meta_body_remove(mb1);
  meta_body_remove(mb2);
}

void mbs_test()
{
  meta_body *mb = meta_body_new();
  meta_body_set *mbs1 = mbs_new(),
                *mbs2 = mbs_new();
  hputs("mbs_test");

  mb_install(mb, 0);
  mbs_push(mbs1, mb);
  mbs_push(mbs2, mb);
  meta_body_clear(mb);

  mb_install(mb, 0);
  mbs_push(mbs1, mb);
  mbs_push(mbs2, mb);
  meta_body_clear(mb);

  meta_body_remove(mb);
  mbs_show(mbs1);
  mbs_show(mbs2);

  mbs_uni(mbs1, mbs2);
  mbs_show(mbs1);

  mbs_remove(mbs1);
  mbs_remove(mbs2);
}

void prod_test()
{
  meta_body *mb = meta_body_new();
  production *prod;

  hputs("produciton test");
  mb_install(mb, 0);
  prod = prod_new("S", mb);
  prod_show(prod);

  prod_remove(prod);
  meta_body_remove(mb);
}

void mn_test()
{
  meta_name *mn = meta_name_new();

  hputs("meta_name test");

  meta_name_push(mn, "S");
  meta_name_push(mn, "P");
  meta_name_push(mn, "E");
  meta_name_push(mn, "T");
  meta_name_push(mn, "C");
  meta_name_push(mn, "X");
  meta_name_push(mn, "F");
  meta_name_show(mn);

  meta_name_remove(mn);
}

void mm_teat()
{
  meta_body *mb = meta_body_new();
  meta_body_set *mbs = mbs_new();
  mbs_map *mm = mbs_map_new();

  hputs("mm_test");

  mb_install(mb, 0);
  mbs_push(mbs, mb);
  meta_body_clear(mb);
  mbs_map_push(mm, "S", mbs);
  meta_body_clear(mb);
  mbs_clear(mbs);

  mb_install(mb, 1);
  mbs_push(mbs, mb);
  meta_body_clear(mb);
  mb_install(mb, 2);
  mbs_push(mbs, mb);
  meta_body_clear(mb);
  mbs_map_push(mm, "P", mbs);
  mbs_clear(mbs);

  mbs_map_show(mm);

  meta_body_remove(mb);
  mbs_remove(mbs);
  mbs_map_remove(mm);
}

void gb_test()
{
  grammar_buffer *gb;
  meta_body *mb = meta_body_new();
  meta_body_set *mbs = mbs_new();
  mbs_map *mm = mbs_map_new();
  meta_name *mn = meta_name_new();

  hputs("gb_test");

  mb_install(mb, 0);
  mbs_push(mbs, mb);
  meta_body_clear(mb);
  mbs_map_push(mm, "S", mbs);
  meta_body_clear(mb);
  mbs_clear(mbs);

  mb_install(mb, 1);
  mbs_push(mbs, mb);
  meta_body_clear(mb);
  mb_install(mb, 2);
  mbs_push(mbs, mb);
  meta_body_clear(mb);
  mbs_map_push(mm, "P", mbs);
  mbs_clear(mbs);

  meta_name_push(mn, "S");
  meta_name_push(mn, "P");

  gb = gb_new(mm, mn);
  gb_show(gb);
  puts(gb_ac_new(gb));
  puts(gb_ac_new(gb));

  meta_body_remove(mb);
  mbs_remove(mbs);
  gb_remove(gb);
//   mbs_map_remove(mm);
//   meta_name_remove(mn);
}

void grammar_test()
{
  hputs("grammar_test");

  meta_name *mn = meta_name_new();
  mbs_map *mm = mbs_map_new();
  meta_body_set *mbs = mbs_new();
  grammar_buffer *gb;
  grammar *g;

  mbs_install(mbs, 0, 1);
  mbs_map_push(mm, "S", mbs);
  mbs_install(mbs, 1, 3);
  mbs_map_push(mm, "P", mbs);
  mbs_install(mbs, 3, 4);
  mbs_map_push(mm, "E", mbs);
  mbs_install(mbs, 4, 6);
  mbs_map_push(mm, "T", mbs);
  mbs_install(mbs, 6, 8);
  mbs_map_push(mm, "C", mbs);
  mbs_install(mbs, 8, 10);
  mbs_map_push(mm, "X", mbs);
  mbs_install(mbs, 10, 13);
  mbs_map_push(mm, "F", mbs);

  mbs_remove(mbs);

  mn_install(mn);

  gb = gb_new(mm, mn);

  g = grammar_from_gb(gb);
  grammar_show(g);

  gb_remove(gb);
  grammar_remove(g);
}

#endif // DTEST

int main(int argc, char* argv[])
{
#if 0 & NDEBUG
//   mb_test();
//   mbs_test();
//   prod_test();
//   mn_test();
//   mm_teat();
//   gb_test();
//   grammar_test();
  return 0;
#endif // test

  FILE *dfa_file = fopen("../dlx2/dpa.dfa", "r"), // DPA's lexical definition
       *ifile,  // input file
       *ofile;  // output file
  dfa = DFAFromFile(dfa_file);
#if 1 & NDEBUG
  ifile = fopen("../debug/test.in", "r");
  ofile = fopen("../debug/test.out", "w");
#else
#endif
  if (!dfa_file || !ifile || !dfa) {
    fprintf(stderr, "DPA: Invaild dfa file or input file\n");
    DFARemove(dfa);
    return 1;
  }
  error = ExceptionNew();
  int rv = 0; // return value

  token_list *tokens = 0;
  ExceptionTry(error) {
    // get token list
    tokens = lexer(ifile);
//     token_list_show(tokens);
    tokens = token_list_format(tokens);
//     token_list_show(tokens);

    // parse phase
    lalr_1_table *table = hand_make_table();
//     l1t_show(table);
    sdt_init();
    // preprocess
    if (!parser(tokens, tokens_ii, table, sdt_preprocess)) {
      // parse
      parser(tokens, tokens_ii, table, sdt_action);
    } else {
      fprintf(stderr, "Parser: syntax error.\n");
      rv = 1;
    }
    l1t_remove(table);
    token_list_remove(tokens);
    grammar_buffer  *gb = sdt_end();
    gb_show(gb);
    grammar *g = grammar_from_gb(gb);
    grammar_show(g);
    gb_remove(gb);

  } ExceptionEnd(error);

  DFARemove(dfa);
  ExceptionRemove(error);
  return rv;
}
