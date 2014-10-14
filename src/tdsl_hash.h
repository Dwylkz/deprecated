#ifndef TDSL_HASH_H_
# define TDSL_HASH_H_

#include <tdsl_comm.h>

typedef struct tdsl_hash_t {
  int* head; 
  struct node_t* data;
  int freed;
  int volume;
  tdsl_hash_i hash;
  tdsl_compare_i compare;
} tdsl_hash_t;

tdsl_hash_t* tdsl_hnew(tdsl_hash_i hash, tdsl_compare_i compare);

void tdsl_hfree(tdsl_hash_t* self);

void* tdsl_hsearch(tdsl_hash_t* self, void* elem);

void* tdsl_hfind(tdsl_hash_t* self, void* elem);

void tdsl_hremove(tdsl_hash_t* self, void* elem);

void tdsl_hclear(tdsl_hash_t* self);

int tdsl_hmap(tdsl_hash_t* self, tdsl_map_i map);

#endif
