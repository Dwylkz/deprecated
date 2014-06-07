#ifndef DOUBLYQUEUE_I_
#define DOUBLYQUEUE_I_

Interface {
  Method 
    SetM(PushFront),
    SetM(PopFront),
    SetM(PushBack),
    SetM(PopBack),
    SetM(Front),
    SetM(Back),
    SetM(Empty);
} DoublyQueueI;

SetT(void, PushFront, Obj _element);
SetT(void, PopFront);
SetT(void, PushBack, Obj _element);
SetT(void, PopBack);
SetT(Obj, Front);
SetT(Obj, Back);
SetT(dif_int, Empty);

#endif // DOUBLYQUEUE_I_
