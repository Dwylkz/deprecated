#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "Comm.h"
#include "Tree.h"

typedef struct SymbolTable {
  char *key_;
  Tree *entry_;
} SymbolTable;

void TableRemove(Map *table);

void PutSymbolTable(
    List *i_table,
    FILE *o_fp);

#endif // SYMBOLTABLE_H_
