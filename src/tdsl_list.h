#ifndef TDSL_LIST_H
# define TDSL_LIST_H

#include <tdsl_comm.h>

typedef struct tdsl_list_t {
  void* data;
  struct tdsl_list_t* to[2];
} tdsl_list_t;

tdsl_list_t* tdsl_lnew();

void tdsl_lfree(tdsl_list_t* self);

int tdsl_lappend(tdsl_list_t* self, void* elem);

void tdsl_lremove(tdsl_list_t* self);

void tdsl_lclear(tdsl_list_t* self);

tdsl_list_t* tdsl_lprobe(tdsl_list_t* self, tdsl_probe_i probe);

int tdsl_lmap(tdsl_list_t* self, tdsl_map_i map);

#endif
