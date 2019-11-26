#include "triangle.hpp"

#include <iostream>

std::ostream& Triangle::draw(std::ostream& out) const
{
  return out << "TRIANGLE (" << centerX_ << "; " << centerY_ << ')';
}
