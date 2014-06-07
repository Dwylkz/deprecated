#include "stdio.h"
#include "List.h"
#include "Array.h"
#include "Pair.h"
#include "Map.h"
#include "BitSet.h"
#include "Exception.h"
#include "v2/Basic.h"

dac_int i, a[] = {1, 2, 3, 4, 5, 6 , 7, 8, 9, 10, 11},
    n = sizeof(a) >> 2;

dac_char s[][20] = {"ab", "cd", "ef", "gh", "ij", "kl", "mn"},
     m = sizeof(s) / sizeof(s[0]);

void CommTest()
{
  char* buf = DacFormat("%d + %d = %d\n", 1, 2, 3);
  DacPutsAndFree(buf);
}

void ListTest()
{
  puts("List");
  List *q = ListNew(StringT);
  
  puts("Stack Push");
  for (i = 0; i < m; i++) {
    StackPush(q, s + i);
  }
  puts("Stack Pop");
  for (i = 0; i < m; i++) {
    printf("\tpush %s\n", (dac_char*)StackTop(q));
    StackPop(q);
  }

  puts("Queue Push");
  for (i = 0; i < m; i++) {
    QueuePush(q, s + i);
  }
  puts("Queue Pop");
  for (i = 0; i < m; i++) {
    printf("\tpush %s\n", (dac_char*)QueueFront(q));
    QueuePop(q);
  }

  puts("List");
  for (i = 0; i < m; i++) {
    ListPush(q, s + i, LIST_HEAD);
  }
  printf("size = %d\n", ListSize(q));
  ListNode *x;
  for (x = ListBegin(q, LIST_TAIL) ; x != ListEnd(q); x = ListNodeTo(x, LIST_TAIL)) {
    printf("\tpush %s\n", (dac_char*)ListNodeData(x));
  }
  ListClear(q);
  for (x = ListBegin(q, LIST_TAIL) ; x != ListEnd(q); x = ListNodeTo(x, LIST_TAIL)) {
    printf("\tpush %s\n", (dac_char*)ListNodeData(x));
  }
  printf("size = %d\n", ListSize(q));

  ListRemove(q);
}

void ArrayTest()
{
  Array *a = ArrayNew(StringT);
  puts("As Stack");
  for (i = 0; i < m; i++) {
    ArrayPush(a, s + i);
    printf("Push %s\n", (dac_char*)ArrayGet(a, ArraySize(a) - 1));
  }
  printf("Array Size = %d\n", ArraySize(a));
  for (i = 0; i < m; i++) {
    printf("Push %s\n", (dac_char*)ArrayGet(a, ArraySize(a) - 1));
    ArrayPop(a);
  }
  printf("Array Size = %d\n", ArraySize(a));
  
  puts("As Array");
  for (i = 0; i < m; i++) {
    ArrayPush(a, s + i);
    printf("\ta[%d] = %s", i, (dac_char*)ArrayGet(a, i));
    ArraySet(a, i, s + m - i - 1);
    printf("->a[%d] = %s\n", i, (dac_char*)ArrayGet(a, i));
  }
  printf("Array Size = %d\n", ArraySize(a));
  ArrayClear(a);
  printf("Array Size = %d\n", ArraySize(a));
  ArrayRemove(a);

  puts("ArrayCopy");
  a = ArrayNew(StringT);
  Array *b = ArrayCopy(a);
  puts("a");
  for (i = 0; i < m; i++) {
    ArrayPush(a, s + i);
    printf("\tPush %s\n", (dac_char*)ArrayGet(a, ArraySize(a) - 1));
  }
  puts("b");
  for (i = m - 1; 0 <= i; i--) {
    ArrayPush(b, s + i);
    printf("\tPush %s\n", (dac_char*)ArrayGet(b, m - i - 1));
  }
  puts(ArrayEqual(a, b)? "a == b": "a != b");
  puts(ArrayGreater(a, b)? "a > b": "a <= b");
  puts(ArrayGreater(b, a)? "b > a": "b <= a");
  ArrayRemove(a);
  ArrayRemove(b);

  a = ArrayNew(StringT);
  b = ArrayNew(StringT);
  puts("ArrayCat");
  puts("a");
  for (i = 0; i < m; i++) {
    ArrayPush(a, s + i);
    printf("\tPush %s\n", (dac_char*)ArrayGet(a, ArraySize(a) - 1));
  }
  printf("a's size = %d\n", ArraySize(a));
  puts("b");
  for (i = m - 1; 0 <= i; i--) {
    ArrayPush(b, s + i);
    printf("\tPush %s\n", (dac_char*)ArrayGet(b, m - i - 1));
  }
  printf("b's size = %d\n", ArraySize(b));
  ArrayCat(a, b);
  puts("ab");
  printf("ab's size = %d\n", ArraySize(a));
  for (i = 0; i < ArraySize(a); i++) {
    printf("\t%s\n", (dac_char*)ArrayGet(a, i));
  }
  ArrayRemove(a);
  puts("b");
  for (i = 0; i < ArraySize(b); i++) {
    printf("\tPush %s\n", (dac_char*)ArrayGet(b, i));
  }
  ArrayRemove(b);
}

void MapTest()
{
  puts("Map");
  Map *map = MapNew(StringT, IntT);
  for (i = m - 1; 0 <= i; i--) {
    MapPush(map, s + i, a + i);
    printf("Push (%6s, %6d)\n", s[i], *(dac_int*)MapGet(map, s[i]));
  }
  printf("size = %d\n", MapSize(map));
  for (i = 0; i < m; i++) {
    printf("%6s's rank is %4d\n", s[i], MapRank(map, s + i));
  }
  for (i = 0; i < m; i++) {
    printf("Pick (%6s, %6d)\n",
        (dac_char*)MapPick(map, i + 1, MAP_KEY),
        *(dac_int*)MapPick(map, i + 1, MAP_DATA));
  }
  printf("size = %d\n", MapSize(map));
  for (i = m / 2; i < m; i++) {
    MapPop(map, s + i);
  }
  printf("size = %d\n", MapSize(map));
  puts("haha");
  for (i = 0; i < m / 2; i++) {
    printf("-Pick (%6s, %6d)\n",
        (dac_char*)MapPick(map, i + 1, MAP_KEY),
        *(dac_int*)MapPick(map, i + 1, MAP_DATA));
  }
  MapClear(map);
  printf("size = %d\n", MapSize(map));
  for (i = m - 1; 0 <= i; i--) {
    MapPush(map, s + i, a + i);
    printf("Push (%6s, %6d)\n", s[i], *(dac_int*)MapGet(map, s[i]));
  }
  for (i = 0; i < m; i++) {
    printf("+Pick (%6s, %6d)\n",
        (dac_char*)MapPick(map, i + 1, MAP_KEY),
        *(dac_int*)MapPick(map, i + 1, MAP_DATA));
  }
  puts("End");
  MapRemove(map);
}

void PairTest()
{
  puts("Pair");
  Map *map = MapNew(PairT, IntT);
  List *l = ListNew(PairT);
  for (i = 0; i < m; i++) {
    Pair *p = PairNew(IntT, a + i, StringT, s + i);
    printf("+Pair %4d, %4s\n", *(int*)PairGet(p, PAIR_L), (char*)PairGet(p, PAIR_R));
    MapPush(map, p, a + i);
    ListPush(l, p, LIST_TAIL);
    PairRemove(p);
  }
  puts("Map<Pair, int>");
  for (i = 0; i < m; i++) {
    Pair *p = MapPick(map, i + 1, MAP_KEY);
    int *b = MapPick(map, i + 1, MAP_DATA);
    printf("+Map (%4d, %4s) -> %4d\n",
        *(int*)PairGet(p, PAIR_L), (char*)PairGet(p, PAIR_R),
        *b);
  }
  puts("List<Pair>");
  ListNode *j = ListBegin(l, LIST_HEAD);
  for ( ; j != ListEnd(l); j = ListNodeTo(j, LIST_HEAD)) {
    Pair *p = ListNodeData(j);
    printf("+List %4d, %4s\n", *(int*)PairGet(p, PAIR_L), (char*)PairGet(p, PAIR_R));
  }
  ListRemove(l);
  MapRemove(map);
}

void BitSetTest()
{
#define Show(x, n) \
  printf(#x" = {");\
  for (i = 0; i < n; i++) {\
    if (BitSetGet(x, i)) {\
      printf(" %-3d", i);\
    }\
  }\
  puts("}")

  BitSet *A = BitSetNew(),
         *B = BitSetNew();
  printf("%d\n", BitSetSize(A));
  for (i = 0; i < n; i++) {
    if (i & 1) {
      BitSetSet(A, i);
    }
  }
  Show(A, n);
  for (i = 0; i < n; i++) {
    if (~i & 1) {
      BitSetSet(B, i);
    }
  }
  Show(B, n);
  puts(BitSetEqual(A, B)? "A == B": "A != B");
  puts(BitSetGreater(A, B)? "A > B": "A <= B");
  puts(BitSetGreater(B, A)? "B > A": "B <= A");
  BitSetRemove(A);
  A = BitSetCopy(B);
  Show(A, n);
  puts(BitSetEqual(A, B)? "A == B": "A != B");
  printf("%d\n", BitSetSize(A));
#if 1
  BitSetUnion(A, B);
  Show(A, BitSetSize(A));
#endif
#if 0
  BitSetIntersect(A, B);
  Show(A, n);
#endif
#if 0
  BitSetDifference(A, B);
  Show(A, n);
#endif
#if 0
  BitSetShift(A, 2);
  Show(A, n + 1);
#endif
#if 0
  BitSetShift(A, 1);
  BitSetUion(A, B);
  Show(A, n);
#endif
#if 0
  BitSetShift(A, -1);
  BitSetIntersect(A, B);
  Show(A, n);
#endif
#if 0
  BitSetShift(A, 3);
  BitSetDifference(A, B);
  Show(A, n + n);
#endif
  BitSetRemove(A);
  BitSetRemove(B);
#undef Show
}

void ExceptionRecursion(Exception *e, int n)
{
  ExceptionTry(e) {
    if (!n) {
      ExceptionThrow(e, 1, "Throw begin!!\n");
    }
    ExceptionRecursion(e, n - 1);
  } else {
    ExceptionThrow(e, 2, "In %d depth\n", n);
  } ExceptionEnd(e);
}

void ExceptionTest()
{
  Exception *e = ExceptionNew();

  ExceptionTry(e) {
    ExceptionRecursion(e, BUFSIZ);
  } else {
    fprintf(stderr, "Throw End.....\n");
    puts(ExceptionHappend(e)? "Exception detected!!!": "No Exception");
  } ExceptionEnd(e);

  ExceptionRemove(e);
}

int main()
{
  // ListTest();
  // ArrayTest();
  // MapTest();
  // PairTest();
  // BitSetTest();
  // ExceptionTest();
  CommTest();

  return 0;
}
