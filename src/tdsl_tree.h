#ifndef TDSL_TREE_H_
# define TDSL_TREE_H_

#include <tdsl_comm.h>

typedef struct tdsl_tree_t {
  struct node_t* root;
  tdsl_compare_i compare;
  int size;
} tdsl_tree_t;

tdsl_tree_t* tdsl_tnew(tdsl_compare_i compare);

void tdsl_tfree(tdsl_tree_t* self);

void tdsl_tclear(tdsl_tree_t* self);

void* tdsl_tsearch(tdsl_tree_t* self, void* key);

void* tdsl_tfind(tdsl_tree_t* self, void* key);

void* tdsl_tselect(tdsl_tree_t* self, int rank);

void tdsl_tremove(tdsl_tree_t* self, void* key);

int tdsl_tmap(tdsl_tree_t* self, tdsl_map_i map);

#endif
