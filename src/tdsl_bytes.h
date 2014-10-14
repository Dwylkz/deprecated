#ifndef TDSL_BYTES_H
# define TDSL_BYTES_H

#include <tdsl_comm.h>

typedef struct tdsl_bytes_t {
  char* data;
  int size;
  int volume;
} tdsl_bytes_t;

tdsl_bytes_t* tdsl_bnew();

void tdsl_bfree(tdsl_bytes_t* self);

int tdsl_bappend(tdsl_bytes_t* self, const char* elem);

void tdsl_bclear(tdsl_bytes_t* self);

char* tdsl_bprobe(tdsl_bytes_t* self, tdsl_probe_i probe);

int tdsl_bmap(tdsl_bytes_t* self, tdsl_map_i map);

#endif
