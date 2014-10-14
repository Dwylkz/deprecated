#ifndef TDSL_UTILS_H
# define TDSL_UTILS_H

#include <tdsl_comm.h>

int tdsl_free(void* self);

int tdsl_random_int(int lower, int upper);

char* tdsl_random_str(int lower, int upper, int size);

int tdsl_map(void* lower, void* upper, tdsl_map_i map);

void* tdsl_recduce(void* lower, void* upper,
                   void* init, tdsl_binary_i binary);

int tdsl_int_compare(void* lhs, void* rhs);

uint32_t tdsl_int_hash(void* self);

int tdsl_str_compare(void* lhs, void*rhs);

uint32_t tdsl_str_hash(void* self);

char* tdsl_loadfile(const char* name);

int tdsl_dumpfile(const char* mem, const char* name);

double tdsl_clock(void);

char* tdsl_raws2escs(const char* str);

char* tdsl_escs2raws(const char* str);

#endif
