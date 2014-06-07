#include "la.h"

static char ibuf[BUFSIZ],   // input buffer
            lexeme_buf[128];// lexeme_buf

// lexical analyzer
token_list *lexer(FILE *ifile)
{
  token_list *tokens = token_list_new();

//   DFAShow(dfa);
  char c, // temp character variable
       *p;// point to lexeme_buf
  int line = 0;        // line number

#define _init DFAInit(dfa), p = lexeme_buf
#define _eprint(fmt,...) fprintf(stderr, "Lexer %d: " fmt "\n", line + 1,##__VA_ARGS__)
#define _fgetc() (c = fgetc(ifile), line += (c == '\n'), ~c)
#define _ungetc() (line -= (c == '\n'), ungetc(c, ifile))
  setbuf(ifile, ibuf);
  _init;
  for ( ; _fgetc(); ) {
    char rv = DFAMove(dfa, c);
    switch (rv) {
      case 1:
        if (p - lexeme_buf > 128) {
          _eprint("this token is too long, man");
          _init;
          _ungetc();
        } else {
          *p++ = c;
        }
        break;
      case 0:
        lexeme_buf[DFAGet_LastAcLen(dfa)] = 0;
        if (DFAGet_LastAc(dfa) != NOTAC) {
          token *t = token_new(DFAGet_LastAc(dfa), lexeme_buf);
          token_list_push(tokens, t);
#if 0 && NDEBUG
          if (DFAGetMetaID(dfa, "space") != DFAGet_LastAc(dfa)
              && DFAGetMetaID(dfa, "new_line") != DFAGet_LastAc(dfa)) {
            printf("get (%20s, %40s)\n", DFAGetMetaName(dfa, t->type), t->lexeme);
          }
#endif
        } else {
          _eprint("I don't know what is %s\n", p);
        }
        _init;
        _ungetc();
        break;
      default:
        _eprint("%c is not in character set", c);
    }
  }
#undef _init
#undef _eprint
#undef _fgetc
#undef _ungetc

  return tokens;
}
