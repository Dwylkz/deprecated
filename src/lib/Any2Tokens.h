#pragma once

#include <dac/Array.h>
#include <dac/Pair.h>

#include "DFA.h"

#define TokenNew(l, r) PairNew(StringT, l, StringT, r)
#define TokenRemove PairRemove
#define TokenGetType(self) ((char*)PairGet(self, PAIR_L))
#define TokenGetLexeme(self) ((char*)PairGet(self, PAIR_R))
#define TokenShow(self) \
    printf("(%s, %s)", TokenGetType(self), TokenGetLexeme(self));

typedef Array Tokens;

#define TokensNew() ArrayNew(PairT)
#define TokensGet(self, i) ((Pair*)ArrayGet(self, i))
#define TokensPush ArrayPush
#define TokenSize ArraySize
#define TokensRemove ArrayRemove
#define TokensShow(self) \
    for (int i = 0; i < TokenSize(self); i++) {\
      TokenShow(TokensGet(self, i));\
      puts("");\
    }

int File2Tokens(DFA* dfa, FILE* file, Tokens** tokens);
