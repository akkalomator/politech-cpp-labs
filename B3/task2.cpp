#include <algorithm>
#include <iostream>
#include "factorialContainer.hpp"

void task2()
{
  FactorialContainer fc;

  std::copy(fc.begin(), fc.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  std::reverse_copy(fc.begin(), fc.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}
