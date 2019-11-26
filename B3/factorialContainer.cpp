#include "factorialContainer.hpp"

const size_t MaxContainerSize = 10;

FactorialIterator::FactorialIterator() :
  value_(1),
  index_(1)
{ }

FactorialIterator::FactorialIterator(size_t index) :
  value_(count(index)),
  index_(index)
{ }

unsigned long long& FactorialIterator::operator *()
{
  return value_;
}

unsigned long long* FactorialIterator::operator ->()
{
  return &value_;
}

FactorialIterator& FactorialIterator::operator ++()
{
  ++index_;
  value_ *= index_;

  return *this;
}

FactorialIterator& FactorialIterator::operator --()
{
  if (index_ > 1)
  {
    value_ /= index_;
    --index_;
  }

  return *this;
}

FactorialIterator FactorialIterator::operator ++(int)
{
  FactorialIterator temp = *this;
  ++(*this);

  return temp;
}

FactorialIterator FactorialIterator::operator --(int)
{
  FactorialIterator temp = *this;
  --(*this);

  return temp;
}

bool FactorialIterator::operator ==(const FactorialIterator& rhs) const
{
  return ((value_ == rhs.value_) && (index_ == rhs.index_));
}

bool FactorialIterator::operator !=(const FactorialIterator& rhs) const
{
  return !(*this == rhs);
}

unsigned long long FactorialIterator::count(size_t index) const
{
  if (index <= 1)
  {
    return 1;
  }
  else
  {
    return index * count(index - 1);
  }
}

FactorialIterator FactorialContainer::begin()
{
  return FactorialIterator(1);
}

FactorialIterator FactorialContainer::end()
{
  return FactorialIterator(MaxContainerSize + 1);
}

