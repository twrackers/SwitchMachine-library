#ifndef _TRIAD__H_
#define _TRIAD__H_

// This is a convenience template class used to group three values or objects
// of the same type into one struct.  This is most useful if you want to easily
// create an array of these groups.  This class is used by the SwitchMachine-
// Controller sketch.

// Because this is a struct and not a class, all data members and methods are
// public by default.

template <class T>
struct Triad {
  T first;
  T second;
  T third;
  
  // constructor
  Triad(T f, T s, T t) :
    first(f), second(s), third(t) {}
};

#endif
