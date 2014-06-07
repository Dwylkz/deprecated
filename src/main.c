#include "Object.h"
#include "Vector.h"
#include "Value.h"
#include "ListNode.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Pair.h"
#include "BSTNode.h"

Obj vec;

void VectorTest()
{
  Obj v = New(Vector, 2),
      a = New(Vector, 1),
      b = New(Object);

  Go(v, Insert, a, 0);
  Go(v, Insert, b, 1);
  Go(v, Insert, v, 2);

  Obj w = Clone(v);

  printf("v is %s\n", WhatIs(v));
  printf("w is %s\n", WhatIs(w));

  dif_int i = 0;
  printf("size = %d\n", Go(v, Size));
  for ( ; i < Go(v, Size); i++) {
    printf("%d: %s == %s?\n", i, WhatIs(Go(v, Select, i)), WhatIs(Go(w, Select, i)));
  }
  printf("size = %d\n", Go(v, Size));
  // Go(v, Delete, 2);
  puts("yes");
  Obj d = Go(v, Select, 2);
  for (i = 0 ; i < Go(v, Size); i++) {
    Obj c = Go(v, Select, i);
    printf("%d: %s == %s?\n", Go(v, Rank, c),
        WhatIs(Go(v, Select, i)), WhatIs(Go(d, Select, i)));
  }

  for (i = 0; i < 10; i++) {
    Go(v, Insert, New(Value, 10 - i - 1), i);
    Obj val = Go(v, Select, i);
    printf("%d\n", (dif_int)Go(val, Get_val));
  }
  printf("a == v? %d\n", Equal(a, v));
  printf("v == v? %d\n", Equal(v, v));
  Go(v, Clear);
  printf("size = %d\n", Go(v, Size));
  Drop(a, v, w, 0);
}

void  ValueTest()
{
  Obj v = New(Value, 10);
  printf("v is %s and val = %d\n",
      WhatIs(v), (dif_int)Go(v, Get_val));
  printf("Nil is %s and val = %d\n",
      WhatIs(Nil), (dif_int)Go(Nil, Get_val));
  Drop(v, 0);
}

void ListNodeTest()
{
  Obj rt = New(ListNode, 2, Nil);
  puts("yes");
  printf("rt is %s, (%p, %p)--{%s}\n",
      WhatIs(rt),
      Go(rt, Get_next, 0), Go(rt, Get_next, 1),
      WhatIs(Go(rt, Get_data)));
  Obj rt_ = Clone(rt);
  Go(rt, Set_next, rt, 0);
  Go(rt, Set_next, rt_, 1);
  printf("rt is %p, (%p, %p)--{%s}\n",
      rt,
      Go(rt, Get_next, 0), Go(rt, Get_next, 1),
      WhatIs(Go(rt, Get_data)));
  printf("rt is %s, (%s, %s)--{%s}\n",
      WhatIs(rt),
      WhatIs(Go(rt, Get_next, 0)), WhatIs(Go(rt, Get_next, 1)),
      WhatIs(Go(rt, Get_data)));
  Drop(rt_, 0);
  rt_ = Clone(rt);
  Go(rt_, Set_data, rt);
  printf("rt_ is %p, (%p, %p)--{%s}\n",
      rt_,
      Go(rt_, Get_next, 0), Go(rt_, Get_next, 1),
      WhatIs(Go(rt_, Get_data)));

  Obj rt__ = Go(rt_, Get_data);

  printf("rt__ is %p, (%p, %p)--{%s}\n",
      rt__,
      Go(rt__, Get_next, 0), Go(rt__, Get_next, 1),
      WhatIs(Go(rt__, Get_data)));

  Drop(rt, rt_, 0);
}

void ObjectTest()
{
  Obj a = New(Object),
      b = New(Object);
  printf("a == b? %d\n", Equal(a, b));
  Drop(a, b, 0);
}

void LinkedListTest()
{
  Obj l = New(LinkedList);
  printf("%d\n", Go(l, Size));
  int i;
  for (i = 0 ; i < 10; i++) {
    Obj v = New(Value, i);
    Go(l, Insert, v, i, LL_TAIL);
    Drop(v, 0);
    printf("size = %d\n", Go(l, Size));
  }
  for (i = 0 ; i < 10; i++) {
    Obj v = Go(l, Select, 10 - i - 1, LL_HEAD);
    printf("Delete %d\n", Go(v, Get_val));
    Go(l, Delete, 0, LL_TAIL);
  }
  Go(l, Clear);
  printf("size = %d\n", Go(l, Size));
  Drop(l, 0);
}

void QueueTest()
{
  Obj q = New(Queue),
      v;
  int i;

  puts("PushBack");
  for (i = 0; i < 10; i++) {
    v = Go(vec, Select, i);
    Go(q, PushBack, v);
    v = Go(q, Back);
    printf("Back is %d \n", Go(v, Get_val));
  }
  puts("PopBack");
  for ( ; !Go(q, Empty); ) {
    Go(q, PopBack);
    v = Go(q, Back);
    printf("Back is %d \n", v? Go(v, Get_val): -1);
  }
  puts("PushFront");
  for (i = 0; i < 10; i++) {
    v = Go(vec, Select, i);
    Go(q, PushFront, v);
    v = Go(q, Front);
    printf("Front is %d \n", Go(v, Get_val));
  }
  puts("PopBack");
  for ( ; !Go(q, Empty); ) {
    Go(q, PopBack);
    v = Go(q, Back);
    printf("Front is %d \n", v? Go(v, Get_val): -1);
  }
  puts("end");
  Drop(q, 0);
}

void PairTest()
{
  puts("Pair");
  Obj p = New(Pair, Nil, Nil),
      q = New(Pair, Nil, Nil);
  printf("p is a %s\n", WhatIs(p));
  printf("p == q? %d\n", Equal(p, q));
  temp_obj = New(Value, 10);
  Go(p, Set_first, temp_obj);
  Drop(temp_obj, 0);
  temp_obj = New(ListNode, 11);
  Go(p, Set_second, temp_obj);
  Drop(temp_obj, 0);
  printf("p == q? %d\n", Equal(p, q));
  printf("p > q? %d\n", Greater(p, q));
  printf("p = (%s, %s)\n",
      WhatIs(Go(p, Get_first)),
      WhatIs(Go(p, Get_second)));
  Drop(q, 0);
  q = Clone(p);
  printf("q = (%s, %s)\n",
      WhatIs(Go(q, Get_first)),
      WhatIs(Go(q, Get_second)));
  Drop(p, q, 0);
  puts("end");
}

void BSTNodeTest()
{
  Obj n = New(BSTNode, Nil);
  printf("%p = {%p, %p, %p, %s}\n",
      n, Go(n, Get_parent), Go(n, Get_lchild), Go(n, Get_rchild), WhatIs(Go(n, Get_data)));
  Go(n, Set_parent, n);
  Go(n, Set_lchild, n);
  Go(n, Set_rchild, n);
  Go(n, Set_data, n);
  printf("%p = {%p, %p, %p, %s}\n",
      n, Go(n, Get_parent), Go(n, Get_lchild), Go(n, Get_rchild), WhatIs(Go(n, Get_data)));
  Obj m = Clone(n);
  Go(n, Set_parent, m);
  Go(n, Set_lchild, m);
  Go(n, Set_rchild, m);
  Go(n, Set_data, n);
  printf("%p = {%p, %p, %p, %s}\n",
      n, Go(n, Get_parent), Go(n, Get_lchild), Go(n, Get_rchild), WhatIs(Go(n, Get_data)));
  Drop(n, m, 0);
}

int main()
{ 
  vec = New(Vector, 0);
  int i;
  for (i = 0 ; i < 10; i++) {
    Obj v = New(Value, i);
    Go(vec, Insert, v, i);
    Drop(v, 0);
    v = Go(vec, Select, i);
    //printf("Insert %d\n", Go(v, Get_val));
  }
  //printf("vec size = %d\n", Go(vec, Size));
  //ObjectTest();
  //VectorTest();
  //ValueTest();
  //ListNodeTest();
  //LinkedListTest();
  //QueueTest();
  //PairTest();
  BSTNodeTest();

  Drop(vec, 0);
  return 0;
}
