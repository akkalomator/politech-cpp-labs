#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape {
public:
  std::ostream& draw(std::ostream& out) const override;
};

#endif //!TRIANGLE_HPP
