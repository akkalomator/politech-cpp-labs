#include "Statistic.hpp"
#include <limits>
#include <stdexcept>

Statistics::Statistics() :
    min_(std::numeric_limits<int>::max()),
    max_(std::numeric_limits<int>::min()),
    oddSum_(0),
    evenSum_(0),
    first_(0),
    count_(0),
    positiveCount_(0),
    negativeCount_(0),
    equality_(false)
{
}

void Statistics::operator()(long long int num)
{
  if (num > max_)
  {
    max_ = num;
  }
  if (num < min_)
  {
    min_ = num;
  }

  if (num > 0)
  {
    positiveCount_++;
  } else if (num < 0)
  {
    negativeCount_++;
  }

  if (num % 2 == 0)
  {
    evenSum_ += num;
  } else
  {
    oddSum_ += num;
  }

  if (count_ == 0)
  {
    first_ = num;
  }

  equality_ = num == first_;

  count_++;
}

long long int Statistics::getMin()
{
  if (count_ < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return min_;
}

long long int Statistics::getMax()
{
  if (count_ < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return max_;
}

double Statistics::getMean()
{
  if (count_ < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  long long int count = count_;

  return (oddSum_ + evenSum_) / count;
}

size_t Statistics::getPositiveCount()
{
  if (count_ < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return positiveCount_;
}

size_t Statistics::getNegativeCount()
{
  if (count_ < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return negativeCount_;
}

long long int Statistics::getOddSum()
{
  if (count_ < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return oddSum_;
}

long long int Statistics::getEvenSum()
{
  if (count_ < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return evenSum_;
}

bool Statistics::isFLEqual()
{
  if (count_ < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return equality_;
}
