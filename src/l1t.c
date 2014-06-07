#include "l1t.h"

// create a table from grammar
lalr_1_table *l1t_from_grammar(grammar *x)
{
  return 0;
}

lalr_1_table *l1t_new()
{
  lalr_1_table *x = calloc(1, sizeof(lalr_1_table));
  assert(x);
  if (x) {
    x->table = ArrayNew(AddrT);
    x->reducing_index = ArrayNew(IntT);
    x->reducing_length = ArrayNew(IntT);
  }
  return x;
}

void *l1t_remove(void *x)
{
  lalr_1_table *y = x;
  int i;
  for (i = 0; i < ArraySize(y->table); i++) {
    MapRemove(ArrayGet(y->table, i));
  }
  ArrayRemove(y->table);
  ArrayRemove(y->reducing_index);
  ArrayRemove(y->reducing_length);
  free(y);
  return y;
}

// create a table from ifile
lalr_1_table *l1t_from_file(FILE *ifile)
{
  return 0;
}

// put table to ofile
void l1t_to_file(lalr_1_table *x, FILE *ofile)
{
}

// return goto[s, i]
int l1t_goto(lalr_1_table *x, int s, int k)
{
#if 0 && NDEBUG
  return 0;
#endif
  Map *r = ArrayGet(x->table, s);
  if (r) {
    int *m = MapGet(r, &k);
    if (m) {
#if 0 && NDEBUG
      printf("map (%4d, %4d)->", s, k); motion_show("", *m, "\n");
#endif
      return *m;
    }
  }
#if 0 && NDEBUG
  printf("map fault\n");
#endif
  return motion_set_type(x->prod_num + s, __motion_error);
}

// return meta index which reduce number i represent
int l1t_get_mi(lalr_1_table *x, int i)
{
  return *(int*)ArrayGet(x->reducing_index, i);
}

// get producetion i's body length
int l1t_get_rl(lalr_1_table *x, int i)
{
  return *(int*)ArrayGet(x->reducing_length, i);
}

// set goto[s][i] = m
void l1t_push(lalr_1_table *x, int s, int i, int m)
{
  Map *t_map;
  for ( ; ArraySize(x->table) <= s; ) {
    t_map = MapNew(IntT, IntT);
    ArrayPush(x->table, t_map);
  }
  t_map = ArrayGet(x->table, s);
  MapPush(t_map, &i, &m);
}

// Print table x to a matrix attaching basic info
void l1t_show(lalr_1_table *x)
{
  int i, j;
  // basic info
  printf("\n%12c%-30s%-12c\n", '[', "show table begin", ']');
  printf("terminal_number       = %d\n", x->term_num);
  printf("nonterminal_number    = %d\n", x->nonterm_num);
  printf("state_number          = %d\n", x->state_num);
  printf("production_number     = %d\n", x->prod_num);
  printf("current_action_number = %d\n", x->eai);
  // print table
  puts("\nLALR(1) parsing table:");
  printf("%4c", ' ');
  for (i = 0; i < x->term_num + x->nonterm_num; i++) {
    printf(" %4d", i);
  }
  puts("");
  for (i = 0; i < ArraySize(x->table); i++) {
    Map *t_map = ArrayGet(x->table, i);

    printf("%4d", i);
#if 0
    int p = 0;
    for (j = 0; j < MapSize(t_map); j++) {
      int k = *(int*)MapPick(t_map, j + 1, MAP_KEY),
          m = *(int*)MapPick(t_map, j + 1, MAP_DATA);
      for ( ; p < k; p++) {
        printf(" %4c", ' ');
      }
      motion_show(" ", m);
      p++;
    }
#else
    for (j = 0; j < x->term_num + x->nonterm_num; j++) {
      int *m = MapGet(t_map, &j);
      if (m) {
        motion_show(" ", *m);
      } else {
        printf(" %4c", ' ');
      }
    }
#endif
    puts("");
  }
  // print reducing_index
  puts("\nreducing_index:");
  for (i = 0; i < ArraySize(x->reducing_index); i++) {
    printf("%4d->%4d\n", i, *(int*)ArrayGet(x->reducing_index, i));
  }
  // print reducing_length
  puts("\nreducing_length:");
  for (i = 0; i < ArraySize(x->reducing_length); i++) {
    printf("%4d->%4d\n", i, *(int*)ArrayGet(x->reducing_length, i));
  }
}
