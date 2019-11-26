#include <iostream>
#include <algorithm>
#include <list>
#include <cmath>
#include <iterator>
#include <functional>
#include <string>

void task1()
{
  std::list<std::string> strSequence;
  std::copy(
      std::istream_iterator<std::string>(std::cin),
      std::istream_iterator<std::string>(),
      std::back_inserter(strSequence)
  );
  std::list<double> sequence;
  std::transform(
      strSequence.begin(),
      strSequence.end(),
      std::back_inserter(sequence),
      std::bind(
          static_cast<double (*)(const std::string &, size_t *)>(&std::stod),
          std::placeholders::_1,
          static_cast<size_t *>(0)
      )
  );
  std::transform(sequence.begin(), sequence.end(), sequence.begin(),
                 std::bind(std::multiplies<double>(), M_PI, std::placeholders::_1));
  std::copy(sequence.begin(), sequence.end(), std::ostream_iterator<double>(std::cout, "\n"));
}
