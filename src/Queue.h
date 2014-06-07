#ifndef QUEUE_H_
#define QUEUE_H_

#include "Info.h"
#include "DoublyQueue.i"

#include "LinkedList.h"

Define(QueueD) {
  Info _;
  DoublyQueueI DoublyQueue_;
};
Define(Queue) {
  struct LinkedList _;
};
extern Type Queue;

/* OK */  Func(Obj, QueueConstruct, va_list* _ptr_ap);
/* OK */  Func(Obj, QueueDestruct);
/* OK */  Func(dif_int, QueueIsEqual, Obj _that);
/* OK */  Func(dif_int, QueueIsGreater, Obj _that);
/* OK */  Func(void, QueueCopy, Obj _that);

/* OK */  Func(void, QueuePushFront, Obj _element);
/* OK */  Func(void, QueuePopFront);
/* OK */  Func(void, QueuePushBack, Obj _element);
/* OK */  Func(void, QueuePopBack);
/* OK */  Func(Obj, QueueFront);
/* OK */  Func(Obj, QueueBack);
/* OK */  Func(dif_int, QueueEmpty);

#endif // QUEUE_H_
