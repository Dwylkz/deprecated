#include "List.h"

ListNode *ListNodeNew(CRI i_cp, void *i_data)
{
  ListNode *bud = malloc(sizeof(ListNode));
  assert(bud);
  bud->to_[0] = bud->to_[1] = bud;
  bud->data_ = i_cp(i_data);
  return bud;
}

void ListNodeRemove(ListNode *i_old, CRI i_rm)
{
  i_old->to_[0]->to_[1] = i_old->to_[1];
  i_old->to_[1]->to_[0] = i_old->to_[0];
  i_rm(i_old->data_);
  free(i_old);
}

ListNode *ListNodeTo(ListNode *self, dac_int i_ht)
{
  return self->to_[i_ht];
}

void *ListNodeData(ListNode *self)
{
  return self->data_;
}

List *ListNew(Type *i_datat)
{
  List *bud = malloc(sizeof(List));
  assert(bud);
  bud->datat_ = i_datat;
  dac_int size = 0;
  bud->head_ = ListNodeNew(IntT->cp_, &size);
  return bud;
}

void ListPush(List *self, void *i_data, dac_int i_ht)
{
  ListNode *bud = ListNodeNew(self->datat_->cp_, i_data),
           *head = self->head_;
  head->to_[i_ht]->to_[!i_ht] = bud;
  bud->to_[i_ht] = head->to_[i_ht];
  head->to_[i_ht] = bud;
  bud->to_[!i_ht] = head;
  ++*(dac_int*)head->data_;
}

void *ListFind(List *self, void *i_data)
{
  ListNode *head = self->head_,
           *x = head->to_[1];
  for ( ; x != head; x = x->to_[1]) {
    if (self->datat_->eq_(x->data_, i_data)) {
      return x->data_;
    }
  }
  return 0;
}

void ListPop(List *self, dac_int i_ht)
{
  ListNode *head = self->head_;
  ListNodeRemove(head->to_[i_ht], self->datat_->rm_);
  --*(dac_int*)head->data_;
}

void *ListGet(List *self, dac_int i_ht)
{
  ListNode *head = self->head_;
  return head == head->to_[i_ht]? 0: head->to_[i_ht]->data_;
}

void ListClear(List *self)
{
  ListNode *head = self->head_,
            *x = head->to_[1],
            *y;
  for ( ; x != head; ) {
    y = x->to_[1];
    ListNodeRemove(x, self->datat_->rm_);
    x = y;
  }
  *(dac_int*)head->data_ = 0;
}

void *ListRemove(void *self)
{
  List* old = self;
  ListClear(old);
  ListNodeRemove(old->head_, IntT->rm_);
  free(old);
  return old;
}

dac_int ListSize(List *self)
{
  return *(dac_int*)self->head_->data_;
}

ListNode *ListBegin(List *self, dac_int i_ht)
{
  return self->head_->to_[i_ht];
}

ListNode *ListEnd(List *self)
{
  return self->head_;
}

Type _ListT = {
  0,
  0,
  0,
  ListRemove
},
  *ListT = &_ListT;
