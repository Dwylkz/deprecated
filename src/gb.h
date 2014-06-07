#ifndef DPA_GB_H_
#define DPA_GB_H_

#include "dpa.h"
#include "mm.h"
#include "mn.h"
#include "mnm.h"

typedef struct grammar_buffer {
  mbs_map *mm;
  meta_name *mn;
  mn_map *mnm;
  int ac;
} grammar_buffer;

grammar_buffer *gb_new();
void *gb_remove(void *x);
char *gb_ac_new(grammar_buffer *gb);

#define gb_show(x) {\
  mbs_map_show((x)->mm); puts("");\
  meta_name_show((x)->mn); puts("");\
  mn_map_show((x)->mnm); puts("");\
}

#endif // gb.h
