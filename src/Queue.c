#include "Queue.h"

Func(Obj, QueueConstruct, va_list* _ptr_ap)
{
	return 0;
}

Func(Obj, QueueDestruct)
{
	return 0;
}

Func(dif_int, QueueIsEqual, Obj _that)
{
	return 0;
}

Func(dif_int, QueueIsGreater, Obj _that)
{
	return 0;
}

Func(void, QueueCopy, Obj _that)
{
}

Func(void, QueuePushFront, Obj _element)
{
  LinkedListInsert(_this, _element, 0, LL_HEAD);
}

Func(void, QueuePopFront)
{
  LinkedListDelete(_this, 0, LL_HEAD);
}

Func(void, QueuePushBack, Obj _element)
{
  LinkedListInsert(_this, _element, 0, LL_TAIL);
}

Func(void, QueuePopBack)
{
  LinkedListDelete(_this, 0, LL_TAIL);
}

Func(Obj, QueueFront)
{
	return LinkedListSelect(_this, 0, LL_HEAD);
}

Func(Obj, QueueBack)
{
	return LinkedListSelect(_this, 0, LL_TAIL);
}

Func(dif_int, QueueEmpty)
{
	return !LinkedListSize(_this);
}

struct QueueD _Queue = {
  // Info
  {
    "Queue",
    sizeof(struct Queue),
    sizeof(struct QueueD),
    // Basic
    {
      PutM(LinkedList, Construct),
      PutM(LinkedList, Destruct),
      PutM(LinkedList, IsEqual),
      PutM(LinkedList, IsGreater),
      PutM(LinkedList, Copy)
    }
  },
  // DoublyQueue
  {
    PutM(Queue, PushFront),
    PutM(Queue, PopFront),
    PutM(Queue, PushBack),
    PutM(Queue, PopBack),
    PutM(Queue, Front),
    PutM(Queue, Back),
    PutM(Queue, Empty)
  }
};
Type Queue = &_Queue;
