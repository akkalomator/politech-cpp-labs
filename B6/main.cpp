#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include "Statistic.hpp"

int main()
{
  Statistics stats;

  std::for_each(std::istream_iterator<long long int>(std::cin), std::istream_iterator<long long int>(),
                std::ref(stats));

  if (!std::cin.eof())
  {
    std::cerr << "Non integral value" << std::endl;
    return 1;
  }

  std::cout.precision(1);

  try
  {
    std::cout << "Max: " << stats.getMax() << std::endl;
    std::cout << "Min: " << stats.getMin() << std::endl;
    std::cout << "Mean: " << std::fixed << stats.getMean() << std::endl;
    std::cout << "Positive: " << stats.getPositiveCount() << std::endl;
    std::cout << "Negative: " << stats.getNegativeCount() << std::endl;
    std::cout << "Odd Sum: " << stats.getOddSum() << std::endl;
    std::cout << "Even Sum: " << stats.getEvenSum() << std::endl;
    std::cout << "First/Last Equal: ";
    stats.isFLEqual() ? std::cout << "yes" : std::cout << "no";
    std::cout << std::endl;
  }
  catch (std::logic_error&)
  {
    std::cout << "No Data" << std::endl;
    return 0;
  }

  return 0;
}
