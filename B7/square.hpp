#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "shape.hpp"

class Square : public Shape {
public:
  std::ostream& draw(std::ostream& out) const override;
};

#endif //!SQUARE_HPP
