#include <forward_list>
#include <vector>
#include "sort.hpp"
#include "print.hpp"

void task1(const char* direction)
{
  SortOrder dir = getSortOrder(direction);

  std::vector<int> data;
  int num = 0;

  while (std::cin >> num)
  {
    data.push_back(num);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("Cannot read data properly");
  }

  if (data.empty())
  {
    return;
  }

  std::vector<int> collectionAt = data;
  std::forward_list<int> iterable(data.begin(), data.end());

  sort<BracketsAccess>(data, dir);
  sort<AtAccess>(collectionAt, dir);
  sort<IteratorAccess>(iterable, dir);

  printCollection(data);
  printCollection(collectionAt);
  printCollection(iterable);
}
