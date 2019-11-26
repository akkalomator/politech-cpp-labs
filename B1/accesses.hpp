#ifndef ACCESSES_HPP
#define ACCESSES_HPP

#include <iterator>

template <typename T>
struct BracketsAccess
{
  static typename T::reference getElement(T& collection, size_t i)
  {
    return collection[i];
  }

  static size_t getNext(size_t i)
  {
    return i + 1;
  }

  static size_t getStart(const T&)
  {
    return 0;
  }

  static size_t getEnd(const T& collection)
  {
    return collection.size();
  }
};

template <typename T>
struct AtAccess
{
  static typename T::reference getElement(T& collection, size_t i)
  {
    return collection.at(i);
  }

  static size_t getNext(size_t i)
  {
    return i + 1;
  }

  static size_t getStart(const T&)
  {
    return 0;
  }

  static size_t getEnd(const T& collection)
  {
    return collection.size();
  }
};

template <typename T>
struct IteratorAccess
{
  typedef typename T::iterator iterator;

  static typename T::reference getElement(T&, iterator& iterator)
  {
    return *iterator;
  }

  static iterator getNext(iterator& iterator)
  {
    return std::next(iterator);
  }

  static iterator getStart(T& collection)
  {
    return collection.begin();
  }

  static iterator getEnd(T& collection)
  {
    return collection.end();
  }
};

#endif
