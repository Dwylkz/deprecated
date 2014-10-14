#include <lexer.h>

token_t* token_new(token_e type, const char* lexeme)
{
  token_t* bud = calloc(1, sizeof(token_t));
  if (bud == NULL)
    TDSL_GOTO(err_0, TDSL_ESYS);

  bud->lexeme = strdup(lexeme);
  if (bud->lexeme == NULL)
    TDSL_GOTO(err_1, TDSL_ESYS);

  bud->type = type;
  return bud;
err_1:
  free(bud);
err_0:
  return NULL;
}

void token_free(token_t* self)
{
  free(self->lexeme);
  free(self);
}

tokens_t* tokens_new(const char* str)
{
  tokens_t* bud = tdsl_anew();
  if (bud == NULL)
    TDSL_GOTO(err_0, "create tokens failed");

  char* ch = (char*)str;
  while (*ch != '\0')
    if (isspace(*ch)) {
    }
    else if (*ch == '#') {
    }
    else if (*ch == '\'') {
    }
    else if (*ch == '=') {
    }
    else if (*ch == '|') {
    }
    else if (*ch == ',') {
    }
    else if (*ch == '-') {
    }
    else if (*ch == ';') {
    }
    else if (*ch == '(') {
    }
    else if (*ch == ')') {
    }
    else if (*ch == '{') {
    }
    else if (*ch == '}') {
    }
    else if (islower(*ch)) {
    }
    else if (isupper(*ch)) {
    }
    else {
    }
  return bud;
err_1:
  tokens_free(bud);
err_0:
  return NULL;
}

int tokens_append(tokens_t* self, token_e type, const char* lexeme)
{
  token_t* token = token_new(type, lexeme);
  if (token == NULL)
    TDSL_GOTO(err_0, "create token failed");

  if (tdsl_aappend(self, token) == -1)
    TDSL_GOTO(err_1, "append token failed");

  return 0;
err_1:
  token_free(token);
err_0:
  return -1;
}

int tokens_free_helper(void* self)
{
  token_free(self);
}

void tokens_free(tokens_t* self)
{
  tdsl_amap(self, tokens_free_helper);
  tdsl_afree(self);
} 
