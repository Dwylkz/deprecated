#ifndef DLEX2_HEADER_
#define DLEX2_HEADER_

// This file is generate by Dlex2
enum token_id { // Meta to id
  digit,
  alpha,
  defininator,
  concatenator,
  sperator,
  exceptor,
  terminator,
  lcomment,
  rcomment,
  first_quote,
  second_quote,
  space,
  tabulator,
  new_line,
  empty,
  other,
  first_terminator,
  second_terminator,
  string,
  meta_identifier,
  endless_story 
};
#define token_name(n) token_name_##n
#define token_name_0 "digit"
#define token_name_1 "alpha"
#define token_name_2 "defininator"
#define token_name_3 "concatenator"
#define token_name_4 "sperator"
#define token_name_5 "exceptor"
#define token_name_6 "terminator"
#define token_name_7 "lcomment"
#define token_name_8 "rcomment"
#define token_name_9 "first_quote"
#define token_name_10 "second_quote"
#define token_name_11 "space"
#define token_name_12 "tabulator"
#define token_name_13 "new_line"
#define token_name_14 "empty"
#define token_name_15 "other"
#define token_name_16 "first_terminator"
#define token_name_17 "second_terminator"
#define token_name_18 "string"
#define token_name_19 "meta_identifier"
#define token_name_20 "endless_story"

#endif // DLEX2_HEADER_