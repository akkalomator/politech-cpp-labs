#ifndef SORT_HPP
#define SORT_HPP

#include <functional>
#include "accesses.hpp"

enum class SortOrder
{
  ASCENDING,
  DESCENDING
};

SortOrder getSortOrder(const char* direction);

template <template <class T> class Access, typename T>
void sort(T& collection, SortOrder order)
{
  using value_type = typename T::value_type;

  std::function<bool(value_type, value_type)> compare = (order == SortOrder::ASCENDING)
      ? std::function<bool(value_type, value_type)>(std::less<value_type>())
      : std::function<bool(value_type, value_type)>(std::greater<value_type>());

  const auto begin = Access<T>::getStart(collection);
  const auto end = Access<T>::getEnd(collection);

  for (auto i = begin; i != end; ++i)
  {
    auto tmp = i;
    for (auto j = Access<T>::getNext(i); j != end; ++j)
    {
      if (compare(Access<T>::getElement(collection, j), Access<T>::getElement(collection, tmp)))
      {
        tmp = j;
      }
    }

    if (tmp != i)
    {
      std::swap(Access<T>::getElement(collection, tmp), Access<T>::getElement(collection, i));
    }
  }
}

#endif
