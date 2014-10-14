#ifndef TDSL_ARRAY_H
# define TDSL_ARRAY_H

#include <tdsl_comm.h>

typedef struct tdsl_array_t {
  void** data;
  int size;
  int volume;
} tdsl_array_t;

tdsl_array_t* tdsl_anew();

void tdsl_afree(tdsl_array_t* self);

int tdsl_aappend(tdsl_array_t* self, void* elem);

void tdsl_aclear(tdsl_array_t* self);

void** tdsl_aprobe(tdsl_array_t* self, tdsl_probe_i probe);

int tdsl_amap(tdsl_array_t* self, tdsl_map_i map);

#endif
