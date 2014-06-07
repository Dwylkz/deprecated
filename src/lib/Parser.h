#ifndef PARSER_H_
#define PARSER_H_

#include "Comm.h"
#include "Token.h"
#include "Tree.h"
#include "SymbolTable.h"

/*            +------+
 * tokens[]-->|Parser|-->tree
 *            +--+---+
 *               A
 *               |
 *               V
 *            symboltable[]
 * 
 * LL(1):
 *
 *   P  = Meta, '=', E, ';', P      First(P)    = { Meta, "" }
 *      | "";                       Follow(P)   = { EOF }
 *
 *   E  = T, E1;                    First(E)    = { '(', '{', Char, Meta }
 *                                  Follow(E)   = { ';', ')', '}' }
 *
 *   E1 = '|', T, E1                First(E1)   = { '|', '' }
 *      | "";                       Follow(E1)  = { ';', ')', '}' }
 *
 *   T  = F, T1;                    First(T)    = { '(', '{', Char, Meta }
 *                                  Follow(T)   = { ';', ')', '}', '|' }
 *
 *   T1 = ',', F, T1                First(T1)   = { ',', '' }
 *      | "";                       Follow(T1)  = { ';', ')', '}', '|' }
 *
 *   F  = '(', E, ')'               First(F)    = { '(', '{', Char, Meta }
 *      | '{', E, '}'               Follow(F)   = { ';', ')', '}', '|', ',' }
 *      | Char
 *      | Meta;
 *
 * SDD:
 *
 *   P  = Meta, '=' E, ';', P       { P.tree  = Union(E.tree, P.tree),
 *                                    NewEntry(Meta.lexenme, E.tree) }
 *      | "";                       { P.tree  = niltree }
 *
 *   E  = T, E1;                    { E.tree  = Union(T.tree, E1.tree) }
 *                                 
 *
 *   E1 = '|', T, E1                { E1.tree = Union(T.tree, E1.tree) }
 *      | "";                       { E1.tree = niltree }
 *
 *   T  = F, T1;                    { T.tree  = Concate(F.tree, T1.tree) }
 *                                 
 *
 *   T1 = ',', F, T1                { T1.tree = Concate(F.tree, T1.tree) }
 *      | "";                       { T1.tree = niltree }
 *
 *   F  = '(', E, ')'               { F.tree  = E.tree }
 *      | '{', E, '}'               { F.tree  = Closure(E.treee) }
 *      | Char                      { F.tree  = NewTree(Char.lexeme) }
 *      | Meta;                     { F.tree  = Entry(Meta.lexeme) }
 * */
void Parser(
    List *i_tokens,
    Map **o_table,
    Tree **o_tree);

int IsMeta(int x);

int MetaEC(int x);

int MetaDC(int x);

#endif // PARSER_H_
