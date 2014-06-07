#include "Any2Tokens.h"

static int GetToken(DFA* dfa, FILE* file, Pair** token)
{
  static char word[BUFSIZ], *tail;
  tail = word;
  DFAInit(dfa);
  int c;
  while ((c = fgetc(file)) != EOF) {
    int ret = DFAMove(dfa, c);
    if (ret == 1) {
      *tail++ = c;
      continue;
    }
    *tail = '\0';
    if (ret == -1) {
      fprintf(stderr, "ERR: unknow character '%c'\n", c);
      return -2;
    }
    ret = DFAGetLastAc(dfa);
    if (ret == NOTAC) {
      fprintf(stderr, "ERR: unknow word \"%s\"", word);
      return -2;
    }
    *token = TokenNew(DFAGetMetaName(dfa, ret), word);
    ungetc(c, file);
    break;
  }
  return c == EOF? -1: 0;
}

int File2Tokens(DFA* dfa, FILE* file, Tokens** tokens)
{
  DFAInit(dfa);
  *tokens = TokensNew();
  Pair* token = NULL;
  while (1) {
    int ret = GetToken(dfa, file, &token);
    if (ret == -2) break;
    if (token) {
      TokensPush(*tokens, token);
      TokenRemove(token);
      token = NULL;
    }
    if (ret == -1) break;
  }
  return 0;
}
