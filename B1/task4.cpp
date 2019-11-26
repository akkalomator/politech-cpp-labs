#include <random>
#include <vector>
#include <ctime>

#include "print.hpp"
#include "sort.hpp"

void fillRandom(double* array, size_t size)
{
  std::mt19937 rng(time(0));
  std::uniform_real_distribution<double> urd(-1.0, 1.0);
  for (size_t i = 0; i < size; ++i)
  {
    array[i] = urd(rng);
  }
}

void task4(const char* direction, size_t size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Size cannot be less than zero");
  }

  SortOrder dir = getSortOrder(direction);

  std::vector<double> vector(size);
  fillRandom(&vector[0], size);

  printCollection(vector);
  sort<BracketsAccess>(vector, dir);
  printCollection(vector);
}
