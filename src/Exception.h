#ifndef EXCEPTION_H_ 
#define EXCEPTION_H_

#include "dac.h"
#include "setjmp.h"
#include "Array.h"

typedef struct Exception {
  dac_int flag_;
  Array *data_;
} Exception;
extern Type *ExceptionT;

Exception *ExceptionNew();

void ExceptionPush(Exception *self);

jmp_buf *ExceptionTop(Exception *self);

void ExceptionEnd(Exception *self);

void ExceptionThrow(
    Exception *self,
    dac_int i_sig,
    dac_char *fmt, ...);

dac_int ExceptionHappend(Exception *self);

void *ExceptionRemove(void *self);

#define ExceptionTry(E) \
  ExceptionPush(E);\
  if (!setjmp(*ExceptionTop(E)))

#endif // EXCEPTION_H_
