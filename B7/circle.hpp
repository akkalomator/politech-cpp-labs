#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape {
public:
  std::ostream& draw(std::ostream& out) const override;
};

#endif //!CIRCLE_HPP
