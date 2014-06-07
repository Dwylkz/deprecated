#include "Dlex.h"

static void LexerTest(List *tokens)
{
  puts("-------------------Tokens---------------------");
#if 1
  ListNode *x = ListBegin(tokens, LIST_TAIL);
  for ( ; x != ListEnd(tokens); x = ListNodeTo(x, LIST_TAIL)) {
    Token *token = ListNodeData(x);
    if (token->type_ != kNewLine) {
      printf("get %20s, %10s\n", TokenName[token->type_], token->lexeme_);
    }
  }
  printf("get %d tokens\n", ListSize(tokens));
#endif
}

static void ParserTest(Map *table, Tree *tree)
{
#if 0
  Tree *a, *b, *c, *d;
  a = TreeNew('a');
  TreeShow(a);
  b = TreeNew('b');
  TreeShow(b);
  c = TreeRepition(a);
  TreeShow(c);
  d = TreeSeperate(a, b);
  TreeShow(d);
  TreeRemove(a);
  TreeRemove(b);
  TreeRemove(c);
  TreeRemove(d);
#endif
#if 0
  puts("-------------------table---------------------");
  int j;
  printf("table size = %d\n", MapSize(table));
  for (j = 0; j < MapSize(table); j++) {
    char *name = MapPick(table, j + 1, MAP_KEY);
    Tree *t_tree = *(void**)MapPick(table, j + 1, MAP_DATA);
    printf("###%s###\n", name);
    TreeShow(t_tree);
  }
#endif
#if 0
  puts("-------------------Tree---------------------");
  TreeShow(tree);
#endif
}

static void DFATest(DFA *dfa)
{
#if 1
  FILE *ofile = fopen("../debug/test.dfa", "w");
  DFAToFile(dfa, ofile);
  fclose(ofile);
  ofile = fopen("../debug/test.dfa", "r");
  dfa = DFAFromFile(ofile);
  assert(dfa);
  fclose(ofile);
#endif
//   DFAShow(dfa);
#if 1
  FILE *ifile = fopen("../debug/test.dlx2", "rt");
#else
  FILE *ifile = fopen("../debug/ExBNF.dlx2", "rt");
#endif
  int c, lb = 0;
  char buf[BUFSIZ];
  DFAInit(dfa);
  for ( ; ~(c = fgetc(ifile)); ) {
#if 0
    printf("DFA in %4d state\n", DFAGet_CurrentS(dfa));
#endif
    int signal = DFAMove(dfa, buf[lb++] = c);
    if (signal != 1) {
      if (DFAGetLastAc(dfa) != NOTAC) {
        ungetc(buf[lb - 1], ifile);
        buf[lb - 1] = 0;
#if 1
        printf("Regonize (%20s, %20s)\n", DFAGetMetaName(dfa, DFAGetLastAc(dfa)), buf);
#endif
      } else {
        buf[lb] = 0;
#if 1
        printf("\tUnregonize \"%s\"\n", buf);
#endif
        if (signal != -1) {
          ungetc(buf[lb - 1], ifile);
        } else {
#if 1
          printf("\t'%c' is not in sigma.\n", buf[lb - 1]);
#endif
        }
      }
      DFAInit(dfa);
      lb = 0;
    }
  }
  fclose(ifile);
  DFARemove(dfa);
}

static char* GetOfileStr(const char* ifile_str, const char* odir_str)
{
  static char buf[BUFSIZ];
  const char* suffix = ".dfa";
  char* str = basename(ifile_str);
  strcpy(buf, odir_str);
  strcat(buf, "/");
  strcat(buf, str);
  if ((str = strrchr(buf, '.')) != NULL) *str = '\0';
  strcat(buf, suffix);
  return buf;
}

int Dlex(const char* ifile_str, const char* odir_str, DFA* ret_dfa)
{
  FILE* ifile = fopen(ifile_str, "r");
  FILE* ofile = fopen(GetOfileStr(ifile_str, odir_str), "w");
  // printf("%s -> %s, %s\n", ifile_str, odir_str, GetOfileStr(ifile_str, odir_str));
  if (ifile == NULL || ofile == NULL) return -1;

	List *tokens;
	Lexer(ifile, &tokens);
	fclose(ifile);
	//   LexerTest(tokens);

	Map *table;
	Tree *tree;
	Parser(tokens, &table, &tree);
	ListRemove(tokens);
	//   ParserTest(table, tree);

	DFA *dfa = DFANew(table, tree);
	TreeRemove(tree);
	//   DFATest(dfa);
  
	DFAToFile(dfa, ofile);
	fclose(ofile);
  if (ret_dfa == NULL) DFARemove(dfa);
  else ret_dfa = dfa;

	return 0;
}

int ShowDFA(const char* ifile_str)
{
  FILE* file = fopen(ifile_str, "r");
  if (!file) return -1;
  DFA* dfa = DFAFromFile(file);
  DFAShow(dfa);
  DFARemove(dfa);
  if (fclose(file) != 0) return -1;
  return 0;
}

int TestDFA(const char* dfa_str, const char* test_str)
{
  FILE* dfa_file = fopen(dfa_str, "r");
  FILE* test_file = fopen(test_str, "r");
  if (!dfa_file || !test_file) {
    perror("ERR: open file failed: ");
    return -1;
  }

  DFA* dfa = DFAFromFile(dfa_file);
  Tokens* tokens = NULL;
  File2Tokens(dfa, test_file, &tokens);
  DFARemove(dfa);
  TokensShow(tokens);
  TokensRemove(tokens);
  if (fclose(dfa_file) || fclose(test_file)) {
    perror("ERR: close file failed: ");
    return -1;
  }
  return 0;
}
