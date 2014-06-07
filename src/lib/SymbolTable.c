#include "SymbolTable.h"

void TableRemove(Map *table)
{
  int i;
  for (i = 0; i < MapSize(table); i++) {
    Tree *t_tree = *(void**)MapPick(table, i + 1, MAP_DATA);
    TreeRemove(t_tree);
  }
  MapRemove(table);
}
