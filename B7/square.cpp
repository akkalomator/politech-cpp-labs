#include "square.hpp"

#include <iostream>

std::ostream& Square::draw(std::ostream& out) const
{
  return out << "SQUARE (" << centerX_ << "; " << centerY_ << ')';
}
