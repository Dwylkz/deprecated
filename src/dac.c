#include "dac.h"

dac_int IntEqual(void *self, void *that)
{
  return *(dac_int*)self == *(dac_int*)that;
}

dac_int IntGreater(void *self, void *that)
{
  return *(dac_int*)self > *(dac_int*)that;
}

void *IntCopy(void *self)
{
  dac_int *bud = malloc(sizeof(dac_int));
  *bud = *(dac_int*)self;
  return bud;
}

void *IntRemove(void *self)
{
  free(self);
  return self;
}

Type _IntT = {
  IntEqual,
  IntGreater,
  IntCopy,
  IntRemove
},
  *IntT = &_IntT;

dac_int StringEqual(void *self, void *that)
{
  return !strcmp((dac_char*)self, (dac_char*)that);
}

dac_int StringGreater(void *self, void *that)
{
  return 0 < strcmp((dac_char*)self, (dac_char*)that);
}

void *StringCopy(void *self)
{
  dac_char *bud = malloc(strlen(self) + 1);
  strcpy(bud, self);
  return bud;
}

void *StringRemove(void *self)
{
  free(self);
  return self;
}

Type _StringT = {
  StringEqual,
  StringGreater,
  StringCopy,
  StringRemove
},
  *StringT = &_StringT;

dac_int AddrEqual(void *self, void *that)
{
  return self == that;
}

dac_int AddrGreater(void *self, void *that)
{
  return self > that;
}

void *AddrCopy(void *self)
{
  return self;
}

void *AddrRemove(void *self)
{
  return self;
}

Type _AddrT = {
  AddrEqual,
  AddrGreater,
  AddrCopy,
  AddrRemove
},
  *AddrT = &_AddrT;
