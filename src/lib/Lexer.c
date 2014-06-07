#include "Lexer.h"
#include "ctype.h"

char fp_buf[BUFSIZ],
     lexeme_buf[BUFSIZ];
FILE *lexer_fp;
int linen;

void SetBuf(FILE *i_fp)
{
  setbuf(lexer_fp = i_fp, fp_buf);
  linen = 1;
}

int GetC()
{
  int c = fgetc(lexer_fp);
  linen += (c == '\n');
  return c;
}

void UnGetC(int c)
{
  linen -= (c == '\n');
  ungetc(c, lexer_fp);
}

void Lexer(
    FILE *i_fp,
    List **o_tokens)
{
  SetBuf(i_fp);
  *o_tokens = ListNew(TokenT);
  int c;
  for ( ; ~(c = GetC()); ) {
    int i = 0, token_type = -1;
    if (isspace(c)) {
      if (c == '\n') {
        token_type = kNewLine;
        lexeme_buf[i++] = '\\';
        lexeme_buf[i++] = 'n';
      } else {
        for ( ; isspace(c = GetC()); ) {}
        UnGetC(c);
      }
    }  else if (isalpha(c) || c == '_') {
      token_type = kMeta;
      for (lexeme_buf[i++] = c; isalnum(c = GetC()) || c == '_'; ) {
        lexeme_buf[i++] = c;
        if (BUFSIZ <= i) {
          token_type = -1;
          i = 0;
          // Error, Meta too long 
          fprintf(stderr, "Lexer %d: Meta too long\n", linen);
          break;
        }
      }
      UnGetC(c);
    } else {
      switch (c) {
        case '=':
          token_type = kDefining;
          lexeme_buf[i++] = c;
          break;
        case '|':
          token_type = kSeperator;
          lexeme_buf[i++] = c;
          break;
        case ',': 
          token_type = kConcatenator;
          lexeme_buf[i++] = c;
          break;
        case '(':
          if ((c = GetC()) == '*') {
            int err_flag = 1;
            for ( ; ~(c = GetC()); ) {
              if (c == '*') {
                if ((c = GetC()) == ')') {
                  err_flag = 0;
                  break;
                } else {
                  UnGetC(c);
                }
              }
            }
            // Error Missing '*)'
            if (err_flag) {
              fprintf(stderr, "Lexer %d: Missing *)\n", linen);
            }
          } else {
            UnGetC(c);
            token_type = kStartGroup;
            lexeme_buf[i++] = '(';
          }
          break;
        case ')':
          token_type = kEndGroup;
          lexeme_buf[i++] = c;
          break;
        case '{':
          token_type = kStartRepition;
          lexeme_buf[i++] = c;
          break;
        case '}':
          token_type = kEndRepition;
          lexeme_buf[i++] = c;
          break;
        case ';':
          token_type = kTerminator;
          lexeme_buf[i++] = c;
          break;
        case '\'':
          token_type = kChar;
          if ((c = GetC()) != '\'') {
            lexeme_buf[i++] = c;
            if ((c = GetC()) != '\'') {
              token_type = -1;
              UnGetC(c);
              // Error, Missing "'"
              fprintf(stderr, "Lexer %d: Missing '\n", linen);
            }
          }
          break;
        case '"':
          token_type = kChar;
          if ((c = GetC()) != '"') {
            lexeme_buf[i++] = c;
            if ((c = GetC()) != '"') {
              token_type = -1;
              UnGetC(c);
              // Error, Missing '"'
              fprintf(stderr, "Lexer %5d: Missing \"\n", linen);
            }
          }
          break;
        default:
          token_type = kOther;
          lexeme_buf[i++] = c;
      } // switch(c)
    } // isalpha();
    lexeme_buf[i] = 0;
    if (token_type != -1) {
      Token *token = TokenNew(token_type, lexeme_buf);
      ListPush(*o_tokens, token, LIST_HEAD);
      TokenRemove(token);
    } 
  } // for ( ; ~(c = GetC(); )
  lexeme_buf[0] = 0;
  Token *token = TokenNew(kEOF, lexeme_buf);
  ListPush(*o_tokens, token, LIST_HEAD);
  TokenRemove(token);
}
