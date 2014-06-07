#include "BitSet.h"

#define LS(x, y) ((x) << (y))
#define RS(x, y) ((x) >> (y))
#define GB(x, y) (RS(x, y) & 1)
#define SB(x, y) ((x) |= LS(1, y))
#define DB(x, y) ((x) &= ~LS(1, y))
#define Get(x, y) (*(dac_int*)ArrayGet((x)->data_, (y)))

BitSet *BitSetNew()
{
  BitSet *bud = malloc(sizeof(BitSet));
  bud->data_ = ArrayNew(IntT);
  return bud;
}

dac_int BitSetEqual(void *_this, void *_that)
{
  BitSet *self = _this,
         *that = _that;
  return ArrayEqual(self->data_, that->data_);
}

dac_int BitSetGreater(void *_this, void *_that)
{
  BitSet *self = _this,
         *that = _that;
  return ArrayGreater(self->data_, that->data_);
}

void *BitSetCopy(void *self)
{
  BitSet *old = self,
         *bud = BitSetNew();
  ArrayRemove(bud->data_);
  bud->data_ = ArrayCopy(old->data_);
  return bud;
}

void *BitSetRemove(void *self)
{
  BitSet *old = self;
  ArrayRemove(old->data_);
  free(old);
  return self;
}

void BitSetSet(BitSet *self, dac_int i_p)
{
  dac_int idx = i_p / BITWISE,
          i = i_p % BITWISE;
  if (idx >= ArraySize(self->data_)) {
    dac_int zero = 0;
    for ( ; ArraySize(self->data_) < idx + 1; ) {
      ArrayPush(self->data_, &zero);
    }
  }
  SB(Get(self, idx), i);
}

void BitSetDrop(BitSet *self, dac_int i_p)
{
  dac_int idx = i_p / BITWISE,
          i = i_p % BITWISE;
  if (idx < ArraySize(self->data_)) {
    DB(Get(self, idx), i);
  }
}

dac_int BitSetGet(BitSet *self, dac_int i_p)
{
  dac_int idx = i_p / BITWISE,
          i = i_p % BITWISE;
  if (idx < ArraySize(self->data_)) {
    return GB(Get(self, idx), i);
  }
  return 0;
}

void BitSetShift(BitSet *self, dac_int i_p)
{
  dac_int t_size = ArraySize(self->data_) * BITWISE,
          i;
  BitSet *bud = BitSetNew();
  for (i = 0; i < t_size; i++) {
    if (BitSetGet(self, i) && 0 <= i + i_p) {
      BitSetSet(bud, i + i_p);
    }
  }
  Array *t_data = self->data_;
  self->data_ = bud->data_;
  bud->data_ = t_data;
  BitSetRemove(bud);
}

void BitSetUnion(BitSet *self, BitSet *that)
{
  dac_int i, size = ArraySize(self->data_);
  if (size < ArraySize(that->data_)) {
    BitSetSet(self, BitSetSize(that) - 1);
    BitSetDrop(self, BitSetSize(that) - 1);
  } 
  size = ArraySize(that->data_);
  for (i = 0; i < size; i++) {
    Get(self, i) |= Get(that, i);
  }
}

void BitSetIntersect(BitSet *self, BitSet *that)
{
  dac_int i, size = ArraySize(self->data_);
  if (size > ArraySize(that->data_)) {
    size = ArraySize(that->data_);
  }
  for (i = 0; i < size; i++) {
    Get(self, i) &= Get(that, i);
  }
}

void BitSetDifference(BitSet *self, BitSet *that)
{
  dac_int i, size = ArraySize(self->data_);
  if (size > ArraySize(that->data_)) {
    size = ArraySize(that->data_);
  }
  for (i = 0; i < size; i++) {
    Get(self, i) &= ~Get(that, i);
  }
}

dac_int BitSetSize(BitSet *self)
{
  return ArraySize(self->data_) * BITWISE;
}

Type _BitSetT = {
  BitSetEqual,
  BitSetGreater,
  BitSetCopy,
  BitSetRemove
},
  *BitSetT = &_BitSetT;

#undef LS
#undef RS
#undef GB
#undef SB
#undef DB
#undef Get
