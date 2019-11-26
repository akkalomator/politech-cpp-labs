#include "circle.hpp"

#include <iostream>
#include <string>

std::ostream& Circle::draw(std::ostream& out) const
{
  return out << "CIRCLE (" << centerX_ << "; " << centerY_ << ')';
}
