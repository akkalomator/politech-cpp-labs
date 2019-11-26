#include "shape.hpp"

#include <string>

bool Shape::isMoreLeft(const Shape& rhs) const
{
  return (centerX_ < rhs.centerX_);
}

bool Shape::isUpper(const Shape& rhs) const
{
  return (centerY_ > rhs.centerY_);
}
