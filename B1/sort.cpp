#include "sort.hpp"

#include <cstring>
#include <stdexcept>

SortOrder getSortOrder(const char* direction)
{
  if (std::strcmp(direction, "ascending") == 0)
  {
    return SortOrder::ASCENDING;
  }

  if (std::strcmp(direction, "descending") == 0)
  {
    return SortOrder::DESCENDING;
  }

  throw std::invalid_argument("No such sorting order");
}
