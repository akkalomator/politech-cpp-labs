#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>

template <typename T>
void printCollection(const T& collection)
{
  if (collection.empty())
  {
    return;
  }

  for (const auto& i: collection)
  {
    std::cout << i << " ";
  }

  std::cout << std::endl;
}

#endif
