#include "mb.h"
#include "mbs.h"
#include "mbm.h"

meta_body *meta_body_sub(meta_body *x, meta_body *y, grammar_buffer *z)
{
  meta_body *w = meta_body_new();
  char *s = gb_ac_new(z);
  meta_body_set *lmbs = mbs_new(),            // extend x if it's neccessary
                *rmbs = mbs_new(),            // extend y if it's neccessary
                *mbs = mbs_new();
  mb_map *mbm = mb_map_new();

  if (!meta_body_size(x) || !meta_body_size(y)) {
    meta_body_cat(w, x);
    return w;
  }
  // create anonymous production
  mn_map_push(z->mnm, s, meta_name_size(z->mn));
  meta_name_push(z->mn, s);
  meta_body_push(w, __gs_nonterminal + mn_map_get(z->mnm, s));
  mbs_map_push(z->mm, s, mbs);

  // extend meta at most one time
  if (gs_get_ttype(meta_body_get(x, 0)) == __gs_terminal) {
    mbs_push(lmbs, x);
  } else {
//     mbs_uni(lmbs, mbs_map_get(z->mm, meta_name_get(z->mn, gs_get_data(meta_body_get(x, 0)))));
  }
  if (gs_get_ttype(meta_body_get(y, 0)) == __gs_terminal) {
    mbs_push(rmbs, y);
  } else {
//     mbs_uni(rmbs, mbs_map_get(z->mm, meta_name_get(z->mn, gs_get_data(meta_body_get(y, 0)))));
  }
#if 0 && NDEBUG
  puts("lmbs:");
  mbs_show(lmbs);
  puts("");
  puts("rmbs:");
  mbs_show(rmbs);
  puts("");
#endif

  // processing substract
//   for (int i = 0; i < mbs_size(rmbs); i++) {
//     mb_map_push(mbm, mbs_get(rmbs, i));
//   }
//   mb_map_show(mbm)

  mb_map_remove(mbm);
  mbs_remove(mbs);
  mbs_remove(lmbs);
  mbs_remove(rmbs);
  return w;
}

void meta_body_show(meta_body *x)
{
  int i;
  for (i = 0; i < meta_body_size(x); i++) {
    int j = meta_body_get(x, i);
    char ld = gs_get_ttype(j) == __gs_terminal? '"': '<',
         rd = gs_get_ttype(j) == __gs_terminal? '"': '>';
    printf((gs_get_ttype(j) == __gs_terminal? "%c%c%c": "%c%d%c"),
        ld, gs_get_data(j), rd);
  }
}
