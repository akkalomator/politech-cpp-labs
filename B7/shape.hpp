#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>

class Shape {
public:
  int centerX_;
  int centerY_;
  virtual ~Shape() = default;
  bool isMoreLeft(const Shape& rhs) const;
  bool isUpper(const Shape& rhs) const;
  virtual std::ostream& draw(std::ostream&) const = 0;
};

#endif //!SHAPE_HPP
