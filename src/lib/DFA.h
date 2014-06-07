#pragma once

#include "Comm.h"
#include "Parser.h"
#include "Tree.h"

#define SIGMA_SIZE 256
#define T_COL 3
#define T_BASE 0
#define T_NEXT 1
#define T_CHECK 2
#define NOTAC 0x7fffffff
typedef struct DFA {
  // Info
  Map *meta_to_id_;
  Array *id_to_meta_;
  int sigma_[SIGMA_SIZE],
      S_,
      s0_;
  Array *T_[T_COL],
        *F_;
  // Runtime
  int current_s_,
      current_len_,
      last_ac_,
      last_ac_len_;
} DFA;

/*
 *           +-------+
 * tree----->|MakeDFA|--->dfa
 *           +-------+
 * */

DFA *DFANew(Map* i_table, Tree *i_tree);

void* DFARemove(void *_this);

void DFAToFile(DFA *self, FILE *o_fp);

DFA *DFAFromFile(FILE *i_fp);

void DFAInit(DFA *self);

int DFAMove(DFA *self, int i_char);

int DFAGetCurrentS(DFA *self);

int DFAGetCurrentLen(DFA *self);

int DFAGetLastAc(DFA *self);

int DFAGetLastAcLen(DFA *self);

char* DFAGetMetaName(DFA *self, int i_id);

int DFAGetMetaID(DFA *self, char *i_meta);

void DFAShow(DFA *self);

void DFAExportBijection(DFA* self, FILE *o_fp);

void DFAPushMeta(DFA *self, char *i_meta);
