#include <iostream>
#include <list>

const std::size_t MAX_SIZE = 20;
const int MAX = 20;
const int MIN = 1;

void recursiveWrite(std::list<int>::iterator start, std::list<int>::iterator end)
{
  if (start == end)
  {
    std::cout << std::endl;
    return;
  }
  if (start == std::prev(end))
  {
    std::cout << *start << std::endl;
    return;
  }
  std::cout << *start << " " << *(std::prev(end)) << " ";

  ++start;
  --end;

  recursiveWrite(start, end);
}

void task2()
{
  std::list<int> list;

  std::size_t size = 0;
  int temp = 0;

  while (std::cin && !(std::cin >> temp).eof())
  {
    if (std::cin.fail())
    {
      throw std::ios_base::failure("reading error");
    }

    if ((temp > MAX) || (temp < MIN))
    {
      throw std::ios_base::failure("invalid number");
    }

    ++size;
    if (size > MAX_SIZE)
    {
      throw std::ios_base::failure("invalid amount of number");
    }

    list.push_back(temp);
  }

  recursiveWrite(list.begin(), list.end());
};
