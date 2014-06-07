#ifndef BITSET_H_
#define BITSET_H_

#include "dac.h"
#include "Array.h"

#define BITWISE (sizeof(dac_int) << 3)

typedef struct BitSet {
  Array *data_;
} BitSet;
extern Type *BitSetT;


BitSet *BitSetNew();

dac_int BitSetEqual(void *_this, void *_that);

dac_int BitSetGreater(void *_this, void *_that);

void *BitSetCopy(void *self);

void *BitSetRemove(void *self);

void BitSetSet(BitSet *self, dac_int i_p);

void BitSetDrop(BitSet *self, dac_int i_p);

dac_int BitSetGet(BitSet *self, dac_int i_p);

void BitSetShift(BitSet *self, dac_int i_p);

void BitSetUnion(BitSet *self, BitSet *that);

void BitSetIntersect(BitSet *self, BitSet *that);

void BitSetDifference(BitSet *self, BitSet *that);

dac_int BitSetSize(BitSet *self);

#endif // BITSET_H_
