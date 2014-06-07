#ifndef LIST_H_
#define LIST_H_

#include "dac.h"
#define LIST_HEAD 1
#define LIST_TAIL 0

#define QueuePush(x, y)       ListPush((x), (y), LIST_TAIL)
#define QueueFront(x)         ListGet((x), LIST_HEAD)
#define QueuePop(x)           ListPop((x), LIST_HEAD)

#define StackPush(x, y)       ListPush((x), (y), LIST_TAIL)
#define StackTop(x)           ListGet((x), LIST_TAIL)
#define StackPop(x)           ListPop((x), LIST_TAIL)

typedef struct ListNode {
  struct ListNode *to_[2];
  void *data_;
} ListNode;
typedef struct List {
  Type *datat_;
  ListNode *head_;
} List;
extern Type *ListT;

ListNode *ListNodeTo(ListNode *self, dac_int i_ht);

void *ListNodeData(ListNode *self);

List *ListNew(Type *i_datat);

void ListPush(List *self, void *i_data, dac_int i_ht);

void *ListFind(List *self, void *i_data);

void ListPop(List *self, dac_int i_ht);

void *ListGet(List *self, dac_int i_ht);

void ListClear(List *self);

void *ListRemove(void *self);

dac_int ListSize(List *self);

ListNode *ListBegin(List *self, dac_int i_ht);

ListNode *ListEnd(List *self);

#endif // LIST_H_
