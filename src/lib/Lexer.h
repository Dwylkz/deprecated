#ifndef LEXER_H_
#define LEXER_H_

#include "Token.h"
#include "stdio.h"
#include "string.h"
#include "dac/List.h"

/*              +-----+
 * file.dlex2-->|Lexer|--->tokens[]
 *              +-----+  
 * */
void Lexer(FILE *i_fp, List **o_tokens);

#endif // LEXER_H_
