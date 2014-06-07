#include "dp.h"
#include "gb.h"
#include "mbs.h"
#include "mnm.h"

static int line_no = 0;
static grammar_buffer *gb;
static mbs_map *mm;
static meta_name *mn;
static mn_map *mnm;

lalr_1_table *hand_make_table()
{
  lalr_1_table *x = l1t_new();
  // basic info
  x->term_num = 8;
  x->nonterm_num = 7;
  x->prod_num = 13;
  x->state_num = 17;
  x->eai = x->prod_num << 1;
  // table
  l1t_push(x, 0, 0, motion_set_type(2, __motion_reduce));
  l1t_push(x, 0, 7, motion_set_type(2, __motion_reduce));
  l1t_push(x, 0, 9, motion_set_type(1, __motion_goto));

  l1t_push(x, 1, 0, motion_set_type(2, __motion_shift));
  l1t_push(x, 1, 7, motion_set_type(__motion_accept, __motion_shift));
  l1t_push(x, 1, 10, motion_set_type(15, __motion_goto));

  l1t_push(x, 2, 2, motion_set_type(3, __motion_shift));

  l1t_push(x, 3, 0, motion_set_type(9, __motion_shift));
  l1t_push(x, 3, 1, motion_set_type(10, __motion_shift));
  l1t_push(x, 3, 3, motion_set_type(12, __motion_reduce));
  l1t_push(x, 3, 4, motion_set_type(12, __motion_reduce));
  l1t_push(x, 3, 5, motion_set_type(12, __motion_reduce));
  l1t_push(x, 3, 6, motion_set_type(12, __motion_reduce));
  l1t_push(x, 3, 11, motion_set_type(4, __motion_goto));
  l1t_push(x, 3, 12, motion_set_type(6, __motion_goto));
  l1t_push(x, 3, 13, motion_set_type(7, __motion_goto));
  l1t_push(x, 3, 14, motion_set_type(8, __motion_goto));

  l1t_push(x, 4, 3, motion_set_type(16, __motion_shift));
  l1t_push(x, 4, 6, motion_set_type(5, __motion_shift));

  l1t_push(x, 5, 0, motion_set_type(3, __motion_reduce));
  l1t_push(x, 5, 7, motion_set_type(3, __motion_reduce));

  l1t_push(x, 6, 3, motion_set_type(5, __motion_reduce));
  l1t_push(x, 6, 4, motion_set_type(11, __motion_shift));
  l1t_push(x, 6, 6, motion_set_type(5, __motion_reduce));

  l1t_push(x, 7, 3, motion_set_type(7, __motion_reduce));
  l1t_push(x, 7, 4, motion_set_type(7, __motion_reduce));
  l1t_push(x, 7, 5, motion_set_type(12, __motion_shift));
  l1t_push(x, 7, 6, motion_set_type(7, __motion_reduce));

  l1t_push(x, 8, 3, motion_set_type(9, __motion_reduce));
  l1t_push(x, 8, 4, motion_set_type(9, __motion_reduce));
  l1t_push(x, 8, 5, motion_set_type(9, __motion_reduce));
  l1t_push(x, 8, 6, motion_set_type(9, __motion_reduce));

  l1t_push(x, 9, 3, motion_set_type(10, __motion_reduce));
  l1t_push(x, 9, 4, motion_set_type(10, __motion_reduce));
  l1t_push(x, 9, 5, motion_set_type(10, __motion_reduce));
  l1t_push(x, 9, 6, motion_set_type(10, __motion_reduce));

  l1t_push(x, 10, 3, motion_set_type(11, __motion_reduce));
  l1t_push(x, 10, 4, motion_set_type(11, __motion_reduce));
  l1t_push(x, 10, 5, motion_set_type(11, __motion_reduce));
  l1t_push(x, 10, 6, motion_set_type(11, __motion_reduce));

  l1t_push(x, 11, 0, motion_set_type(9, __motion_shift));
  l1t_push(x, 11, 1, motion_set_type(10, __motion_shift));
  l1t_push(x, 11, 3, motion_set_type(12, __motion_reduce));
  l1t_push(x, 11, 4, motion_set_type(12, __motion_reduce));
  l1t_push(x, 11, 5, motion_set_type(12, __motion_reduce));
  l1t_push(x, 11, 6, motion_set_type(12, __motion_reduce));
  l1t_push(x, 11, 13, motion_set_type(14, __motion_goto));
  l1t_push(x, 11, 14, motion_set_type(8, __motion_goto));

  l1t_push(x, 12, 0, motion_set_type(9, __motion_shift));
  l1t_push(x, 12, 1, motion_set_type(10, __motion_shift));
  l1t_push(x, 12, 3, motion_set_type(12, __motion_reduce));
  l1t_push(x, 12, 4, motion_set_type(12, __motion_reduce));
  l1t_push(x, 12, 5, motion_set_type(12, __motion_reduce));
  l1t_push(x, 12, 6, motion_set_type(12, __motion_reduce));
  l1t_push(x, 12, 14, motion_set_type(17, __motion_goto));

  l1t_push(x, 13, 3, motion_set_type(4, __motion_reduce));
  l1t_push(x, 13, 4, motion_set_type(11, __motion_shift));
  l1t_push(x, 13, 6, motion_set_type(4, __motion_reduce));

  l1t_push(x, 14, 3, motion_set_type(6, __motion_reduce));
  l1t_push(x, 14, 4, motion_set_type(6, __motion_reduce));
  l1t_push(x, 14, 5, motion_set_type(12, __motion_shift));
  l1t_push(x, 14, 6, motion_set_type(6, __motion_reduce));

  l1t_push(x, 15, 0, motion_set_type(1, __motion_reduce));
  l1t_push(x, 15, 7, motion_set_type(1, __motion_reduce));

  l1t_push(x, 16, 0, motion_set_type(9, __motion_shift));
  l1t_push(x, 16, 1, motion_set_type(10, __motion_shift));
  l1t_push(x, 16, 3, motion_set_type(12, __motion_reduce));
  l1t_push(x, 16, 4, motion_set_type(12, __motion_reduce));
  l1t_push(x, 16, 5, motion_set_type(12, __motion_reduce));
  l1t_push(x, 16, 6, motion_set_type(12, __motion_reduce));
  l1t_push(x, 16, 12, motion_set_type(13, __motion_goto));
  l1t_push(x, 16, 13, motion_set_type(7, __motion_goto));
  l1t_push(x, 16, 14, motion_set_type(8, __motion_goto));

  l1t_push(x, 17, 3, motion_set_type(8, __motion_reduce));
  l1t_push(x, 17, 4, motion_set_type(8, __motion_reduce));
  l1t_push(x, 17, 5, motion_set_type(8, __motion_reduce));
  l1t_push(x, 17, 6, motion_set_type(8, __motion_reduce));
  // reducing_index
  int ri;
  // 0. S = P;
  ri = x->term_num + 0, ArrayPush(x->reducing_index, &ri);
  // 1. P = P, E;
  ri = x->term_num + 1, ArrayPush(x->reducing_index, &ri);
  // 2. P = ;
  ri = x->term_num + 1, ArrayPush(x->reducing_index, &ri);
  // 3. E = m, '=', T, ';';
  ri = x->term_num + 2, ArrayPush(x->reducing_index, &ri);
  // 4. T = T, '|', C;
  ri = x->term_num + 3, ArrayPush(x->reducing_index, &ri);
  // 5. T = C;
  ri = x->term_num + 3, ArrayPush(x->reducing_index, &ri);
  // 6. C = C, ',' X;
  ri = x->term_num + 4, ArrayPush(x->reducing_index, &ri);
  // 7. C = X;
  ri = x->term_num + 4, ArrayPush(x->reducing_index, &ri);
  // 8. X = X, '-', F;
  ri = x->term_num + 5, ArrayPush(x->reducing_index, &ri);
  // 9. X = F;
  ri = x->term_num + 5, ArrayPush(x->reducing_index, &ri);
  // 10. F = m;
  ri = x->term_num + 6, ArrayPush(x->reducing_index, &ri);
  // 11. F = s;
  ri = x->term_num + 6, ArrayPush(x->reducing_index, &ri);
  // 12. F = ;
  ri = x->term_num + 6, ArrayPush(x->reducing_index, &ri);
  // reducing_length
  int rl;
  // 0. S = P;
  rl = 1, ArrayPush(x->reducing_length, &rl);
  // 1. P = P, E;
  rl = 2, ArrayPush(x->reducing_length, &rl);
  // 2. P = ;
  rl = 0, ArrayPush(x->reducing_length, &rl);
  // 3. E = m, '=', T, ';';
  rl = 4, ArrayPush(x->reducing_length, &rl);
  // 4. T = T, '|', C;
  rl = 3, ArrayPush(x->reducing_length, &rl);
  // 5. T = C;
  rl = 1, ArrayPush(x->reducing_length, &rl);
  // 6. C = C, ',' X;
  rl = 3, ArrayPush(x->reducing_length, &rl);
  // 7. C = X;
  rl = 1, ArrayPush(x->reducing_length, &rl);
  // 8. X = X, '-', F;
  rl = 3, ArrayPush(x->reducing_length, &rl);
  // 9. X = F;
  rl = 1, ArrayPush(x->reducing_length, &rl);
  // 10. F = m;
  rl = 1, ArrayPush(x->reducing_length, &rl);
  // 11. F = s;
  rl = 1, ArrayPush(x->reducing_length, &rl);
  // 12. F = ;
  rl = 0, ArrayPush(x->reducing_length, &rl);
  return x;
}

void tokens_init(void *tokens)
{
  token_list_init(tokens);
}

int tokens_look(void* tokens)
{
  int type = token_list_top(tokens)->type;

#if 0 && NDEBUG
  token_show(token_list_top(tokens));
  puts("pass");
#endif

  switch (type) {
    case defininator:
      type = 2;
      break;
    case concatenator:
      type = 4;
      break;
    case sperator:
      type = 3;
      break;
    case exceptor:
      type = 5;
      break;
    case terminator:
      type = 6;
      break;
    case space:
    case tabulator:
    case new_line:
      line_no += (type == new_line);
      type = token_list_top(tokens)->type;
      for ( ; type == space || type == tabulator || type == new_line; ) {
        token_list_pop(tokens);
        type = token_list_top(tokens)->type;
      }
      type = tokens_look(tokens);
      break;
    case string:
      type = 1;
      break;
    case alpha:
    case meta_identifier:
      type = 0;
      break;
    case endless_story:
      type = 7;
      break;
    default:
      type = -3;
  }
  return type;
}

void *tokens_shift(void *tokens)
{
  token *t = token_copy(token_list_top(tokens));
  token_list_pop(tokens);
  return t;
}

void sdt_init()
{
  gb = gb_new();
  mm = gb->mm;
  mn = gb->mn;
  mnm = gb->mnm;
}

struct { int l; char *s;} rs[] = {
  {1, "<S>::=<P>"},
  {2, "<P>::=<P><E>"},
  {0, "<P>::="},
  {4, "<E>::=<m>'='<T>';'"},
  {3, "<T>::=<T>'|'<C>"},
  {1, "<T>::=<C>"},
  {3, "<C>::=<C>','<X>"},
  {1, "<C>::=<X>"},
  {3, "<X>::=<X>'|'<F>"},
  {1, "<X>::=<F>"},
  {1, "<F>::=<m>"},
  {1, "<F>::=<s>"},
  {0, "<F>::="}
};

void sdt_preprocess(int id, pstack *stack, void *istream, istream_i *ii)
{
#define reduce(x) {\
  for (int i = 0; i < rs[x].l; i++) {\
    token_remove(pstack_lookat(stack, 0));\
    pstack_pop(stack);\
  }\
  pstack_push(stack, token_new(meta_identifier, rs[x].s));\
}
  if (0 <= id && id < 13) {
    if (id == 3) {
      mn_map_push(mnm, ((token*)pstack_lookat(stack, 3))->lexeme, meta_name_size(mn));
      meta_name_push(mn, ((token*)pstack_lookat(stack, 3))->lexeme);
    }
    reduce(id);
#if 0 && NDEBUG
    token_show(pstack_lookat(stack, 0));
#endif
  } else if (id == -1){
#if 0 && NDEBUG
    printf("Pointer stack has %d element at last.\n", pstack_size(stack));
#endif
    token_remove(pstack_lookat(stack, 0));
    token_remove(pstack_lookat(stack, 1));
  } else {
  }
#undef reduce
}

void sdt_action(int id, pstack *stack, void *istream, istream_i *ii)
{
#define lookat(x) pstack_lookat(stack, (x))
#define push(x)   pstack_push(stack, (x))
#define pop(x)    pstack_npop(stack, (x))
  meta_body *mb;
  meta_body_set *mbs;
  int i;
  token *t;

#if 0 && NDEBUG
  if (id != -1) {
    printf("reducing %4d. %30s\n", id, rs[id].s);
  }
#endif
  switch (id) {
    case -1:
      t = lookat(0);
      token_remove(t);
      pop(1);
      break;
    case 0:
    case 1:
    case 2:
      break;
    case 3:
      // <E>::=<m>'='<T>';'
      t = lookat(3);
      if ((mbs = mbs_map_get(mm, t->lexeme))) {
        mbs_clear(mbs);
        mbs_uni(mbs, lookat(1));
      } else {
        mbs_map_push(mm, t->lexeme, lookat(1));
      }
      token_remove(lookat(3));
      token_remove(lookat(2));
      token_remove(lookat(0));
      pop(3);
      break;
    case 4:
      // <T>::=<T>'|'<C>
      mbs_push(lookat(2), lookat(0));
      token_remove(lookat(1));
      meta_body_remove(lookat(0));
      pop(2);
      break;
    case 5:
      // <T>::=<C>
      mbs = mbs_new();
      mbs_push(mbs, lookat(0));
      meta_body_remove(lookat(0));
      pop(1);
      push(mbs);
      break;
    case 6:
      // <C>::=<C>','<X>
      meta_body_cat(lookat(2), lookat(0));
      token_remove(lookat(1));
      meta_body_remove(lookat(0));
      pop(2);
      break;
    case 7:
      // <C>::=<X>
      break;
    case 8:
      // <X>::=<X>'-'<F>
      mb = meta_body_sub(lookat(2), lookat(0), gb);
#if 1 && NDEBUG
      printf("    "); meta_body_show(lookat(2)); puts("");
      printf("-   "); meta_body_show(lookat(0)); puts("");
      puts("------------------------------------------"); 
      printf("    "); meta_body_show(mb); puts("\n");
#endif
      meta_body_remove(lookat(2));
      token_remove(lookat(1));
      meta_body_remove(lookat(0));
      pop(3);
      push(mb);
      break;
    case 9:
      // <X>::=<F>
      break;
    case 10:
      // <F>::=<m>
      t = lookat(0);
      pop(1);
      i = mn_map_get(mnm, t->lexeme);
      mb = meta_body_new();
      meta_body_push(mb, __gs_nonterminal + i);
      token_remove(t);
      push(mb);
      break;
    case 11:
      // <F>::=<s>
      t = lookat(0);
      pop(1);
      mb = meta_body_new();
      i = strlen(t->lexeme);
      for (int j = 1; j < i - 1; j++) {
        meta_body_push(mb, __gs_terminal + t->lexeme[j]);
      }
      token_remove(t);
      push(mb);
      break;
    case 12:
      // <F>::=
      push(meta_body_new());
      break;
    default:
      ;
  }
#undef lookat
#undef pop
}

grammar_buffer *sdt_end()
{
  return gb;
}

istream_i _tokens_ii = {
  tokens_init,
  tokens_look,
  tokens_shift
},
  *tokens_ii = &_tokens_ii;
