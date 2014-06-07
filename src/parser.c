#include "parser.h"
#include "sstack.h"

int parser(
    void *istream,
    istream_i *ii,
    lalr_1_table *table,
    actionfp action)
{
  sstack *s_stack = sstack_new();
  pstack *p_stack = pstack_new();
  int top,          // state stack's top
      lookahead,    // istream's top
      motion,       // shift? reduce? error?
      mi,           // meta index
      rl,           // reduce_length
      rv;           // return value 0:success/1:fail

  ii->init(istream);
  top = __uni_start_state;
  sstack_push(s_stack, top);

  for ( ; ; ) {
    top = sstack_top(s_stack);
    lookahead = ii->look(istream);
    motion = l1t_goto(table, top, lookahead);

#if __PLOG && NDEBUG
#if 1
//     puts("pass");
    printf("top = %d, lookhead = %d\n", top, lookahead);
#endif
//     motion_show("get motion", motion, "\n");
//     getchar();
//     motion = motion_set_type(motion, __motion_shift);
#endif

    switch (motion_get_type(motion)) {
      case __motion_shift:
        top = motion_get_index(motion);
        pstack_push(p_stack, ii->shift(istream));
#if __PLOG && NDEBUG
//         token_show(pstack_lookat(p_stack, 0));
        printf("shift %d and goto %d\n", lookahead, top);
//         token_remove(pstack_lookat(p_stack, 0));
#endif
        sstack_push(s_stack, top);
        break;
      case __motion_reduce:
        mi = l1t_get_mi(table, motion_get_index(motion));
        rl = l1t_get_rl(table, motion_get_index(motion));
#if __PLOG && NDEBUG
        printf("reducing prodcution %d which lenght is %d, table index is %d\n",
            motion_get_index(motion), rl, mi);
#endif
        for ( ; rl--; ) {
          sstack_pop(s_stack);
        }
#if __PLOG && NDEBUG
        printf("back to state %d\n", sstack_top(s_stack));
#endif
        top = l1t_goto(table, sstack_top(s_stack), mi);
        sstack_push(s_stack, top);
#if __PLOG && NDEBUG
        printf("goto state %d\n", sstack_top(s_stack));
#endif
        action(motion_get_index(motion), p_stack, istream, ii);
        break;
      case __motion_error:
        action(motion_get_index(motion), p_stack, istream, ii);
        rv = 1;
        break;
      default :
        rv = 1;
        ;
    }
#if 0 && NDEBUG
    if (lookahead == __uni_endless_story) {
      break;
    }
#endif
    if (sstack_top(s_stack) == __motion_accept) {
#if PLOG && NDEBUG
      puts("legal syntax\n");
//       getchar();
#endif
      action(__uni_ac_action, p_stack, istream, ii);
      rv = 0;
      break;
    }
  }

  sstack_remove(s_stack);
  pstack_remove(p_stack);
  return rv;
}
