#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <cstdlib>

class Statistics
{
public:
  Statistics();

  void operator()(long long int);

  long long int getMin();

  long long int getMax();

  double getMean();

  size_t getPositiveCount();

  size_t getNegativeCount();

  long long int getOddSum();

  long long int getEvenSum();

  bool isFLEqual();

private:
  long long int min_, max_, oddSum_, evenSum_, first_;
  size_t count_, positiveCount_, negativeCount_;
  bool equality_;
};

#endif // STATISTIC_HPP
