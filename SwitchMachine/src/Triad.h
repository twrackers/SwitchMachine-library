#ifndef _TRIAD__H_
#define _TRIAD__H_

template <class T>
struct Triad {
  T first;
  T second;
  T third;
  Triad(T f, T s, T t) :
    first(f), second(s), third(t) {}
};

#endif
