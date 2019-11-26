#ifndef B3_FACTORIAL_CONTAINER_HPP
#define B3_FACTORIAL_CONTAINER_HPP

#include <iterator>

class FactorialIterator : public std::iterator<std::bidirectional_iterator_tag, unsigned long long,
  std::ptrdiff_t, unsigned long long*, unsigned long long>
{
public:
  FactorialIterator();
  explicit FactorialIterator(size_t index);

  unsigned long long& operator *();
  unsigned long long* operator ->();

  FactorialIterator& operator ++();
  FactorialIterator& operator --();

  FactorialIterator operator ++(int);
  FactorialIterator operator --(int);

  bool operator ==(const FactorialIterator& rhs) const;
  bool operator !=(const FactorialIterator& rhs) const;

private:
  unsigned long long value_;
  size_t index_;

  unsigned long long count(size_t index) const;
};

class FactorialContainer
{
public:
  FactorialContainer() = default;
  FactorialContainer(const FactorialContainer&) = delete;
  FactorialContainer(FactorialContainer&&) = delete;
  ~FactorialContainer() = default;

  FactorialContainer& operator =(const FactorialContainer&) = delete;
  FactorialContainer& operator =(FactorialContainer&&) = delete;

  FactorialIterator begin();
  FactorialIterator end();
};

#endif
