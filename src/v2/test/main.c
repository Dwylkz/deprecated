#include <Comm.h>
#include <Basic.h>
#include <Wrapper.h>
#include <MArray.h>
#include <MSet.h>
#include <Array.h>
#include <IntArray.h>
#include <StringArray.h>
#include <AddressArray.h>
#include <Bytes.h>
#include <MSet.h>
#include <Set.h>
#include <IntSet.h>
#include <StringSet.h>
#include <AddressSet.h>
#include <MPair.h>
#include <Pair.h>
#include <Map.h>

int int_lower = 10;
int int_upper = 1000;
int ints_len = 1e1;
int* ints;

int str_lower = 'a'; int str_upper = 'z' + 1;
int str_len = 10;
int strs_len = 1e1;
char** strs;

void TestMap()
{
  char* buf;
  DacMap* m;

  m = DacMapNew(DacStringType, DacIntType);
  for (int i = 0; i < strs_len; i++)
    DacMapInsert(m, strs[i], &ints[i]);

  for (int i = 0; i < strs_len; i++)
    DacMapInsert(m, strs[i], &ints[i]);

  for (int i = 0; i < strs_len/2; i++)
    DacMapRemove(m, strs[i]);

  DacMapClear(m);

  for (int i = 0; i < strs_len/2; i++)
    DacMapInsert(m, strs[i], &ints[i]);

  for (int i = 0; i < strs_len; i++) {
    int *ret = DacMapFind(m, strs[i]);
    printf("%d\n", ret == NULL? 0: *ret);
  }

  int i = -1;
  for (DacPair* p; (p = DacMapForward(m, &i)) != NULL; )
    DacPutsAndFree(DacPairPush(p));
  puts("------");
  for (DacPair* p; (p = DacMapBackward(m, &i)) != NULL; )
    DacPutsAndFree(DacPairPush(p));

  buf = DacMapPush(m);
  DacMapFree(m);
  DacMapPull(buf, &m);
  free(buf);
  DacPutsAndFree(DacMapPush(m));
}

void TestPair()
{
  DacPair* p = DacPairNew(DacStringType,
                          strs[0],
                          DacIntType,
                          &ints[0]);
  DacSet* s = DacSetNew(DacPairType);
  for (int i = 0; i < strs_len; i++) {
    printf("%s, %d\n", (char*)DacPairGet(p, 0), *(int*)DacPairGet(p, 1));
    DacPairFree(p);
    p = DacPairNew(DacStringType,
                   strs[i],
                   DacIntType,
                   &ints[i]);
    // int zero = 0;
    // DacPairSet(p, 1, &zero);
    // DacPairSet(p, 0, strs[0]);
    DacSetSearch(s, p);
  }
  DacPutsAndFree(DacSetPush(s));
  DacSetFree(s);

  char *buf = DacPairPush(p);
  DacPairFree(p);
  DacPairPull(buf, &p);
  DacPutsAndFree(DacPairPush(p));
  DacPairFree(p);
}

void TestMPair()
{
  DacWrapper* left = DacWrapperNew(DacStringType, strs[0]);
  DacWrapper* right = DacWrapperNew(DacIntType, &ints[0]);

  DacMPair* p = DacMPairNew(left, right);
  DacPutsAndFree(DacMPairPush(p));

  DacMArray* a = DacMArrayNew();
  for (int i = 0; i < strs_len; i++) {
    DacWrapperSet(left, DacStringType, strs[i]);
    DacMArrayPushBack(a, left, 1);
  }
  DacWrapperSet(right, DacMArrayType, a);
  DacMPairSet(p, 1, right);

  char* buf = DacMPairPush(p);
  puts(buf);

  DacMPairFree(p);

  DacMPairPull(buf, &p);
  DacMPairSet(p, 0, right);
  DacPutsAndFree(DacMPairPush(p));
  
  DacWrapperFree(left);
  DacWrapperFree(right);
  DacMPairFree(p);
  DacMArrayFree(a);
  DacStringFree(buf);
}

void TestBasicSet()
{
  DacIntSet* s = DacIntSetNew();

  for (int i = 0; i < ints_len; i++)
    DacIntSetSearch(s, ints[i]);
  for (int i = 0; i < ints_len/2; i++)
    DacIntSetRemove(s, ints[i]);
  DacIntSetClear(s);
  for (int i = ints_len/2; i < ints_len; i++)
    DacIntSetSearch(s, ints[i]);
  for (int i = 0; i < ints_len; i++) {
    int* ret = DacIntSetFind(s, ints[i]);
    printf("%d%c", ret == NULL? 0: *ret, i < ints_len-1? ' ': '\n');
  }

  int i = -1;
  for (int* p; (p = DacIntSetForward(s, &i)) != NULL; )
    printf("%d\n", p == NULL? 0: *p);
  for (int* p; (p = DacIntSetBackward(s, &i)) != NULL; )
    printf("%d\n", p == NULL? 0: *p);

  char* buf = DacIntSetPush(s);
  DacIntSetFree(s);
  DacIntSetPull(buf, &s);
  DacPutsAndFree(DacIntSetPush(s));
  free(buf);

  s = DacStringSetNew();

  for (int i = 0; i < strs_len; i++)
    DacStringSetSearch(s, strs[i]);
  for (int i = 0; i < strs_len/2; i++)
    DacStringSetRemove(s, strs[i]);
  DacStringSetClear(s);
  for (int i = strs_len/2; i < strs_len; i++)
    DacStringSetSearch(s, strs[i]);
  for (int i = 0; i < strs_len; i++) {
    char* ret = DacStringSetFind(s, strs[i]);
    printf("%s%c", ret == NULL? 0: ret, i < strs_len-1? ' ': '\n');
  }

  buf = DacStringSetPush(s);
  DacStringSetFree(s);
  DacStringSetPull(buf, &s);
  DacPutsAndFree(DacStringSetPush(s));
  free(buf);

  s = DacAddressSetNew();

  for (int i = 0; i < strs_len; i++)
    DacAddressSetSearch(s, strs[i]);
  for (int i = 0; i < strs_len/2; i++)
    DacAddressSetRemove(s, strs[i]);
  DacAddressSetClear(s);
  for (int i = strs_len/2; i < strs_len; i++)
    DacAddressSetSearch(s, strs[i]);
  for (int i = 0; i < strs_len; i++) {
    char* ret = DacAddressSetFind(s, strs[i]);
    printf("%p%c", ret == NULL? 0: ret, i < strs_len-1? ' ': '\n');
  }

  buf = DacAddressSetPush(s);
  DacAddressSetFree(s);
  DacAddressSetPull(buf, &s);
  DacPutsAndFree(DacAddressSetPush(s));
  free(buf);
}

void TestSet()
{
  DacSet* s = DacSetNew(DacStringType);

  for (int i = 0; i < strs_len; i++)
    DacSetSearch(s, strs[i]);

  for (int i = 0; i < strs_len / 2; i++)
    DacSetRemove(s, strs[i]);
  puts("");

  for (int i = 0; i < strs_len; i++)
    printf("%p ", DacSetFind(s, strs[i]));
  puts("");

  int i = -1;
  for (char* p; (p = DacSetForward(s, &i)) != NULL; )
    DacPutsAndFree(DacStringPush(p));
  for (char* p; (p = DacSetBackward(s, &i)) != NULL; )
    DacPutsAndFree(DacStringPush(p));

  char* buf = DacSetPush(s);
  DacSetFree(s);
  DacSetPull(buf, &s);
  DacPutsAndFree(DacSetPush(s));
  DacSetFree(s);
}

void TestMSet()
{
  DacMSet* s = DacMSetNew();
  DacWrapper* w = DacWrapperNew(DacStringType, "wrapper");

  for (int i = 0; i < strs_len; i++) {
    DacWrapperSet(w, DacStringType, strs[i]);
    DacMSetSearch(s, w);
  }
  for (int i = 0; i < strs_len; i++) {
    DacWrapperSet(w, DacStringType, strs[i]);
    DacMSetSearch(s, w);
  }

  char* buf = DacMSetPush(s);
  puts(buf);
  DacMSetFree(s);
  DacMSetPull(buf, &s);
  free(buf);

  for (int i = 0; i < strs_len / 2; i++) {
    DacWrapperSet(w, DacStringType, strs[i]);
    DacMSetRemove(s, w);
  }
  for (int i = 0; i < strs_len / 2; i++) {
    DacWrapperSet(w, DacIntType, ints + i);
    DacMSetSearch(s, w);
  }

  DacPutsAndFree(DacMSetPush(s));

  DacMSetClear(s);
  for (int i = 0; i < strs_len / 2; i++) {
    DacWrapperSet(w, DacIntType, ints + i);
    DacMSetSearch(s, w);
  }
  printf("size=%d\n", s->size);
  // DacPutsAndFree(DacMSetPush(s));

  // int i = -1;
  // for (DacWrapper* p; (p = DacMSetForward(s, &i)) != NULL; )
  //   DacPutsAndFree(DacWrapperPush(p));
  // for (DacWrapper* p; (p = DacMSetBackward(s, &i)) != NULL; )
  //   DacPutsAndFree(DacWrapperPush(p));

  // DacPutsAndFree(DacMSetPush(s));
  // for (int i = 0; i < strs_len / 2; i++) {
  //   DacWrapperSet(w, DacIntType, ints + i);
  //   printf(DacMSetFind(s, w) == NULL? "0": "1");
  //   if (DacMSetFind(s, w) == NULL)
  //     DacMSetSearch(s, w);
  // }
  // puts("");

  for (int i = 0; i < 2; i++) {
    DacMPair* p = DacMPairNew(w, w);
    DacWrapperSet(w, DacMPairType, p);
    DacMSetSearch(s, w);
    DacMPairFree(p);
  }

  DacArray* ma = DacArrayNew(DacMSetType);
  DacArrayPushBack(ma, s, 2);
  DacWrapperSet(w, DacArrayType, ma);
  DacArrayFree(ma);
  DacMSetSearch(s, w);

  DacWrapperSet(w, DacMSetType, s);
  DacMSetSearch(s, w);

  buf = DacMSetPush(s);
  DacMSetFree(s);
  DacMSetPull(buf, &s);
  DacPutsAndFree(DacMSetPush(s));
  DacMSetFree(s);

  DacWrapperFree(w);
  DacWrapperPull(buf, &w);
  DacPutsAndFree(DacWrapperPush(w));
  s = DacWrapperExport(w);
  DacPutsAndFree(DacMSetPush(s));
  DacMSetFree(s);
  free(buf);
}

void TestBasicArray()
{
  DacIntArray* as = DacIntArrayNew();
  for (int i = 0; i < ints_len; i++)
    DacIntArrayPushBack(as, ints[i], 2);
  char* buf = DacIntArrayPush(as);
  puts(buf);
  DacIntArraySet(as, 2, 100);
  printf("%d\n", *DacIntArrayGet(as, 2));
  DacIntArrayFree(as);
  if (DacIntArrayPull(buf, &as) != NULL) {
    DacPutsAndFree(DacIntArrayPush(as));
    DacIntArrayFree(as);
  }
  free(buf);

  as = DacStringArrayNew();
  for (int i = 0; i < strs_len; i++)
    DacStringArrayPushBack(as, strs[i], 2);
  buf = DacStringArrayPush(as);
  printf("size=%dB\n", strlen(buf));
  puts(buf);
  DacStringArraySet(as, 2, "hehe");
  printf("%s\n", DacStringArrayGet(as, 2));
  DacStringArrayFree(as);
  if (DacStringArrayPull(buf, &as) != NULL) {
    // DacPutsAndFree(DacStringArrayPush(as));
    DacStringArrayFree(as);
  }
  free(buf);

  as = DacAddressArrayNew();
  for (int i = 0; i < strs_len; i++)
    DacAddressArrayPushBack(as, strs[i], 2);
  buf = DacAddressArrayPush(as);
  puts(buf);
  DacAddressArraySet(as, 2, ints);
  printf("%p\n", DacAddressArrayGet(as, 2));
  DacAddressArrayFree(as);
  if (DacAddressArrayPull(buf, &as) != NULL) {
    DacPutsAndFree(DacAddressArrayPush(as));
    DacAddressArrayFree(as);
  }
  free(buf);
}

void TestArray()
{
  DacArray* as = DacArrayNew(DacIntType);

  for (int i = 0; i < ints_len; i++)
    DacArrayPushBack(as, ints + i, 2);
  for (int i = 0; i < ints_len / 2; i++)
    DacArrayPopBack(as, 1);
  DacPutsAndFree(DacArrayPush(as));

  DacArraySet(as, 2, ints + 8);
  printf("%d\n", *(int*)DacArrayGet(as, 2));
  DacPutsAndFree(DacArrayPush(as));

  DacArray* bs = DacArrayCopy(as);
  char* buf = DacArrayPush(bs);
  DacArrayFree(bs);
  DacArrayPull(buf, &bs);
  free(buf);
  DacArrayPopBack(bs, 4);
  DacPutsAndFree(DacArrayPush(bs));

  DacArrayFree(as);
  DacArrayFree(bs);
}

void TestMArray()
{
  DacMArray* ma = DacMArrayNew();
  DacWrapper* w = DacWrapperNew(DacStringType, "temp");
  for (int i = 0; i < ints_len; i++) {
    DacWrapperSet(w, DacIntType, ints + i);
    if (w == NULL)
      DacErr(-1, "new wrapper failed");
    if (DacMArrayPushBack(ma, w, 1) != 0)
      DacErr(-1, "push back failed");
  }
  for (int i = 0; i < strs_len; i++) {
    DacWrapperSet(w, DacStringType, strs[i]);
    if (w == NULL)
      DacErr(-1, "new wrapper failed");
    if (DacMArrayPushBack(ma, w, 1) != 0)
      DacErr(-1, "push back failed");
  }

  DacWrapperSet(w, DacAddressType, ints);
  DacMArraySet(ma, 13, w);

  DacWrapperSet(w, DacMArrayType, ma);
  DacMArrayPushBack(ma, w, 1);

  char* buf = DacMArrayPush(ma);
  puts(buf);

  DacMArray* mb;
  DacMArrayPull(buf, &mb);
  DacMArrayPopBack(mb, 5);
  DacMArrayPushBack(mb, w, 5);
  DacPutsAndFree(DacMArrayPush(mb));

  printf("Vs = %d, Hash = %u\n",
         DacMArrayVs(ma, mb),
         DacMArrayHash(ma));

  DacMArrayClear(mb);
  DacPutsAndFree(DacMArrayPush(mb));

  free(buf);
  DacWrapperFree(w);
  DacMArrayFree(ma);
  DacMArrayFree(mb);
}

void TestWrapper()
{
  DacWrapper* wrapper = DacWrapperNew(DacIntType, ints);
  if (wrapper == NULL) return ;

  DacPutsAndFree(DacWrapperPush(wrapper));

  DacWrapperFree(wrapper);

  char* pull = DacWrapperPull("d1000", &wrapper);
  if (pull !=  NULL) {
    DacPutsAndFree(DacWrapperPush(wrapper));

    DacWrapperSet(wrapper, DacStringType, "data\t\r\n\b");
    printf("get %s\n", DacWrapperGet(wrapper));

    DacWrapper* copy = DacWrapperCopy(wrapper);
    DacPutsAndFree(DacWrapperPush(wrapper));

    DacWrapperFree(wrapper);
    DacWrapperFree(copy);
  }
}

void TestBytes()
{
  DacBytes* b = DacBytesNew("test");
  for (int i = 0; i < strs_len; i++)
    DacBytesCatString(b, strs[i]);
  DacBytesCat(b, b);
  // DacPutsAndFree(DacBytesPush(b));
  DacBytesFree(b);
}

void TestBasic()
{
  time_t start = time(0);
  int zero = 100;
  int* one = DacIntCopy(&zero);
  printf("%d vs %d = %d\n", zero, *one, DacIntVs(&zero, one));
  *one += 1;
  printf("%d vs %d = %d\n", zero, *one, DacIntVs(&zero, one));
  *one -= 2;
  printf("%d vs %d = %d\n", zero, *one, DacIntVs(&zero, one));
  DacIntFree(one);
  printf("one = %p\n", one);

  char* temp = "this is a test";
  char* str = DacStringCopy(temp);
  printf("'%s' vs '%s' = %d\n", temp, str, DacStringVs(temp, str));
  DacStringFree(str);
  printf("str = %p\n", str);

  int* addr = DacAddressCopy(&zero);
  str = DacAddressPush(addr);
  if (str != NULL)
    DacPutsAndFree(str);
  printf("%p vs %p = %d\n", addr, &zero, DacAddressVs(addr, &zero));

  if (DacIntPull(" d2000", &one) != NULL)
    printf("one = %d\n", *one);
  DacIntFree(one);

  if (DacAddressPull("  p0x11112222", &addr) != NULL)
    printf("addr = %p\n", addr);

  if (DacStringPull("  You\\t\\nmagic is mine.\"", &str) != NULL) {
    printf("str = %s\n", str);
    DacStringFree(str);
  }

  one = DacIntFromString("-123");
  printf("int from string: %d\n", *one);
  free(one);

  one = DacAddressFromString("0x19191");
  printf("address from string: %p\n", one);
}

void TestComm()
{
  DacErr(-1, "hello world!: %s", "Dwylkz");
  DacWarn(0, "hello world!: %s", "Dwylkz");

  char* str = "hello";
  char* a = DacStringCopy(str);
  char* b = DacStringCopy(str);
  char* buf = DacFormat("[%*s, %s] = %s, %*s", a, "World!", b, b);
  if (buf != NULL)
    DacPutsAndFree(buf);
  else {
    free(a);
    free(b);
  }
  buf = DacReplace("[%*s, %*s] = %s", "%*s", "%s", 1);
  DacPutsAndFree(buf);
}

int main()
{
  time_t start = time(0);
  ints = DacRandomInts(int_lower, int_upper, ints_len);
  strs = DacRandomStrings(str_lower, str_upper, str_len, strs_len);
  DacCheck(ints == NULL, -1);

  for (int i = 0; i < ints_len; i++)
    printf("%d%c", ints[i], i < ints_len-1? ' ': '\n');
  
  // TestComm();
  // TestBasic();
  // TestBytes();
  // TestWrapper();
  // TestMArray();
  // TestArray();
  // TestBasicArray();
  // TestMSet();
  // TestSet();
  // TestBasicSet();
  // TestMPair();
  // TestPair();
  TestMap();

  DacRangeFree(strs, strs + strs_len, free);
  free(ints);
  printf("%us\n", time(0) - start);
  return 0;
}
