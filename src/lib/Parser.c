#include "Parser.h"
#include "dac/Exception.h"

static ListNode *tokens; 
static Token *lookahead, *token;
static Map *table, *id_table;
static int linen, meta_idx;
static Exception *error;

#define META_SHIFT 128

int IsMeta(int x)
{
  return x >= META_SHIFT;
}

int MetaEC(int x)
{
  return x + META_SHIFT;
}

int MetaDC(int x)
{
  return x - META_SHIFT;
}

static void EatNewLine()
{
  for ( ; lookahead->type_ == kNewLine; ) {
    linen++;
    tokens = ListNodeTo(tokens, LIST_TAIL);
    lookahead = ListNodeData(tokens);
  }
}

static void SetTokens(List *i_tokens)
{
  linen = 1;
  tokens = ListBegin(i_tokens, LIST_TAIL);
  lookahead = ListNodeData(tokens);
  EatNewLine();
}

static Token *GetToken()
{
  Token *token = ListNodeData(tokens);
  tokens = ListNodeTo(tokens, LIST_TAIL);
  lookahead = ListNodeData(tokens);
  EatNewLine();
#if 0
  printf("get %-20s %s\n", TokenName[token->type_], token->lexeme_);
#endif
  return token;
}

static void MatchToken(TokenType i_token_type)
{
  ExceptionTry(error) {
    if (lookahead->type_ == i_token_type) {
      token = GetToken();
    } else {
      ExceptionThrow(error, 1, "Parser %d: I prefer to match %s instead of %s\n",
          linen, TokenName[i_token_type], TokenName[lookahead->type_]);
    }
  } else {
  } ExceptionEnd(error);
}

static void ParserF(Tree **o_tree);
static void ParserT1(Tree **o_tree);
static void ParserT(Tree **o_tree);
static void ParserE1(Tree **o_tree);
static void ParserE(Tree **o_tree);
static void ParserP(Tree **o_tree);

#define Judge_TreeRemove(t) \
  if ((t)) {\
    TreeRemove((t));\
  }

void Parser(
    List *i_tokens,
    Map **o_table,
    Tree **o_tree)
{
  SetTokens(i_tokens);
  table = MapNew(StringT, IntT);
  id_table = *o_table = MapNew(StringT, IntT);
  error = ExceptionNew();
  ExceptionTry(error) {
    *o_tree = 0;
    ParserP(o_tree);
  } else {
  } ExceptionEnd(error);
  if (ExceptionHappend(error)) {
    Judge_TreeRemove(*o_tree);
    *o_tree = TreeNew(0);
    fprintf(stderr, "Parser : Invaild syntax.\n");
  }
  ExceptionRemove(error);
  TableRemove(table);
}

static void ParserF(Tree **o_tree)
{
  Tree *E_tree = 0;
  ExceptionTry(error) {
    switch (lookahead->type_) {
      case kStartGroup:
        MatchToken(kStartGroup);
        ParserE(&E_tree);
        MatchToken(kEndGroup);

        *o_tree = E_tree;
        break;
      case kStartRepition:
        MatchToken(kStartRepition);
        ParserE(&E_tree);
        MatchToken(kEndRepition);

        *o_tree = TreeRepition(E_tree);
        TreeRemove(E_tree);
        break;
      case kChar:
        MatchToken(kChar);

        *o_tree = TreeNew(token->lexeme_[0]);
        break;
      case kMeta:
        MatchToken(kMeta);

        if (MapGet(table, token->lexeme_)) {
          Tree *nil_tree = TreeNew(0);
          E_tree = *(void**)MapGet(table, token->lexeme_);
          *o_tree = TreeConcatenate(E_tree, nil_tree);
          TreeRemove(nil_tree);
          break;
        }
      default :
        *o_tree = TreeNew(0);
        ExceptionThrow(error, 1, "Parser %d: Lookahead error detected in F production.\n", linen);
    }
  } else {
    Judge_TreeRemove(E_tree);
    *o_tree = TreeNew(0);
  } ExceptionEnd(error);
}

static void ParserT1(Tree **o_tree)
{
  Tree *F_tree = 0,
       *T1_tree = 0;
  ExceptionTry(error) {
    switch (lookahead->type_) {
      case kConcatenator:
        MatchToken(kConcatenator);
        ParserF(&F_tree);
        ParserT1(&T1_tree);

        *o_tree = TreeConcatenate(F_tree, T1_tree);
        TreeRemove(F_tree);
        TreeRemove(T1_tree);
        break;
      case kSeperator:
      case kTerminator:
      case kEndGroup:
      case kEndRepition:
        *o_tree = TreeNew(0);
        break;
      default :
        *o_tree = TreeNew(0);
        ExceptionThrow(error, 1, "Parser %d: Lookahead error detected in T1 production.\n", linen);
    }
  } else {
    Judge_TreeRemove(F_tree);
    Judge_TreeRemove(T1_tree);
    *o_tree = TreeNew(0);
  } ExceptionEnd(error);
}

static void ParserT(Tree **o_tree)
{
  Tree *F_tree = 0,
       *T1_tree = 0;
  ExceptionTry(error) {
    switch (lookahead->type_) {
      case kStartGroup:
      case kStartRepition:
      case kChar:
      case kMeta:
        ParserF(&F_tree);
        ParserT1(&T1_tree);

        *o_tree = TreeConcatenate(F_tree, T1_tree);
        TreeRemove(F_tree);
        TreeRemove(T1_tree);
        break;
      default :
        *o_tree = TreeNew(0);
        ExceptionThrow(error, 1, "Parser %d: Lookahead error detected in T production.\n", linen);
    }
  } else {
    Judge_TreeRemove(F_tree);
    Judge_TreeRemove(T1_tree);
    *o_tree = TreeNew(0);
  } ExceptionEnd(error);
}

static void ParserE1(Tree **o_tree)
{
  Tree *T_tree = 0,
       *E1_tree = 0;
  ExceptionTry(error) {
    switch (lookahead->type_) {
      case kSeperator:
        MatchToken(kSeperator);
        ParserT(&T_tree);
        ParserE1(&E1_tree);

        *o_tree = TreeSeperate(T_tree, E1_tree);
        TreeRemove(T_tree);
        TreeRemove(E1_tree);
        break;
      case kTerminator:
      case kEndGroup:
      case kEndRepition:
        *o_tree = TreeNew(0);
        (*o_tree)->nullable_ = 0;
        break;
      default :
        *o_tree = TreeNew(0);
        ExceptionThrow(error, 1, "Parser %d: Lookahead error detected in E1 production.\n", linen);
    }
  } else {
    Judge_TreeRemove(T_tree);
    Judge_TreeRemove(E1_tree);
    *o_tree = TreeNew(0);
  } ExceptionEnd(error);
}

static void ParserE(Tree **o_tree)
{
  Tree *T_tree = 0,
       *E1_tree = 0;
  ExceptionTry(error) {
    switch (lookahead->type_) {
      case kStartGroup:
      case kStartRepition:
      case kChar:
      case kMeta:
        ParserT(&T_tree);
        ParserE1(&E1_tree);

        *o_tree = TreeSeperate(T_tree, E1_tree);
        TreeRemove(T_tree);
        TreeRemove(E1_tree);
        break;
      default :
        *o_tree = TreeNew(0);
        ExceptionThrow(error, 1, "Parser %d: Lookahead error detected in E production.\n", linen);
    }
  } else {
    Judge_TreeRemove(T_tree);
    Judge_TreeRemove(E1_tree);
    *o_tree = TreeNew(0);
  } ExceptionEnd(error);
}

static void ParserP(Tree **o_tree)
{
  Tree *E_tree = 0,
       *P_tree = 0,
       *ac_tree = 0,
       *meta_tree = 0;
  ExceptionTry(error) {
    switch (lookahead->type_) {
      case kMeta:
        MatchToken(kMeta);
        char *meta_name = token->lexeme_;
        MatchToken(kDefining);
        ParserE(&E_tree);
        MatchToken(kTerminator);

        // Insert the new meta first start.
        MapPush(table, meta_name, &E_tree);
        MapPush(id_table, meta_name, &meta_idx);
        ac_tree = TreeNew(MetaEC(meta_idx++));
        meta_tree = TreeConcatenate(E_tree, ac_tree);
        // Insert the new meta first end.
        ParserP(&P_tree);

        *o_tree = TreeSeperate(meta_tree, P_tree);
        TreeRemove(ac_tree);
        TreeRemove(meta_tree);
        TreeRemove(P_tree);
        break;
      case kEOF:
        MatchToken(kEOF);

        *o_tree = TreeNew(0);
        (*o_tree)->nullable_ = 0;
        break;
      default:
        *o_tree = TreeNew(0);
        ExceptionThrow(error, 1, "Parser %d: Lookahead error detected in P production.\n", linen);
    }
  } else {
    Judge_TreeRemove(ac_tree);
    Judge_TreeRemove(meta_tree);
    Judge_TreeRemove(P_tree);
    *o_tree = TreeNew(0);
  } ExceptionEnd(error);
}

#undef Judge_TreeRemove
