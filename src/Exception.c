#include "Exception.h"

Exception *ExceptionNew()
{
  Exception *bud = malloc(sizeof(Exception));
  assert(bud);
  bud->flag_ = 0;
  bud->data_ = ArrayNew(IntT);
  return bud;
}

void ExceptionPush(Exception *self)
{
  jmp_buf *bud = malloc(sizeof(jmp_buf));
  ArrayPush(self->data_, &bud);
}

jmp_buf *ExceptionTop(Exception *self)
{
  dac_int size = ArraySize(self->data_);
  return *(jmp_buf**)ArrayGet(self->data_, size - 1);
}

void ExceptionEnd(Exception *self)
{
  dac_int size = ArraySize(self->data_);
  free(*(jmp_buf**)ArrayGet(self->data_, size - 1));
  ArrayPop(self->data_);
}

void ExceptionThrow(
    Exception *self,
    dac_int i_sig,
    dac_char *i_fmt, ...)
{
  va_list ap;

  va_start(ap, i_fmt);
  vfprintf(stderr, i_fmt, ap);
  va_end(ap);

  self->flag_ = 1;
  ExceptionEnd(self);
  longjmp(*ExceptionTop(self), i_sig);
}

dac_int ExceptionHappend(Exception *self)
{
  return self->flag_;
}

void *ExceptionRemove(void *self)
{
  Exception *old = self;
  dac_int i, size = ArraySize(old->data_);
  for (i = 0; i < size; i++) {
    free(*(jmp_buf**)ArrayGet(old->data_, i));
  }
  ArrayRemove(old->data_);
  free(old);
  return self;
}

Type _ExceptionT = {
  0,
  0,
  0,
  ExceptionRemove
};
Type *ExceptionT = &_ExceptionT;
