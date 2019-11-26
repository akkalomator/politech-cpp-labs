#include <memory>
#include <vector>
#include <iterator>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "circle.hpp"
#include "triangle.hpp"
#include "square.hpp"

static std::istream &operator>>(std::istream &in, std::shared_ptr<Shape> &shape)
{
  if (in.peek() == EOF)
  {
    in.get();
    return in;
  }
  std::string tempShape;
  std::getline(in, tempShape);
  while (tempShape.find_first_not_of(" \t") == std::string::npos)
  {
    if (in.eof())
    {
      return in;
    }
    std::getline(in, tempShape);
  }
  if (tempShape.find_first_of('(') == std::string::npos)
  {
    throw std::invalid_argument("Invalid shape");
  }
  std::string type = tempShape.substr(0, tempShape.find_first_of('('));
  while (type.find_first_of(" \t") == 0)
  {
    type.erase(0, 1);
  }
  while (type.find_last_of(" \t") == type.size() - 1 && !type.empty())
  {
    type.pop_back();
  }
  if (type == "CIRCLE")
  {
    shape = std::make_shared<Circle>();
  } else if (type == "TRIANGLE")
  {
    shape = std::make_shared<Triangle>();
  } else if (type == "SQUARE")
  {
    shape = std::make_shared<Square>();
  } else
  {
    throw std::invalid_argument("Invalid shape");
  }
  std::string coordinates = tempShape.substr(tempShape.find_first_of('('));
  size_t posOfSemicolon = coordinates.find_first_of(';');
  size_t posOfClosingParenthesis = coordinates.find_first_of(')');
  if (posOfSemicolon == std::string::npos || posOfClosingParenthesis == std::string::npos ||
      posOfSemicolon > posOfClosingParenthesis)
  {
    throw std::invalid_argument("Invalid point's declaration");
  }
  shape->centerX_ = std::stoi(coordinates.substr(1, posOfSemicolon - 1));
  shape->centerY_ = std::stoi(coordinates.substr(posOfSemicolon + 1, posOfClosingParenthesis));
  return in;
};

static std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Shape> &shape)
{
  return shape->draw(out);
};

void task2()
{
  std::vector<std::shared_ptr<Shape> > shapes;
  std::copy(
      std::istream_iterator<std::shared_ptr<Shape> >(std::cin),
      std::istream_iterator<std::shared_ptr<Shape> >(),
      std::back_inserter(shapes)
  );
  std::cout << "Original:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout, "\n"));
  std::cout << "Left-Right:\n";
  std::stable_sort(shapes.begin(), shapes.end(),
                   [](const std::shared_ptr<Shape> &lhs, const std::shared_ptr<Shape> &rhs)
                   {
                     return lhs->isMoreLeft(*rhs);
                   }
  );
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout, "\n"));
  std::cout << "Right-Left:\n";
  std::stable_sort(shapes.begin(), shapes.end(),
                   [](const std::shared_ptr<Shape> &lhs, const std::shared_ptr<Shape> &rhs)
                   {
                     return !(lhs->isMoreLeft(*rhs));
                   });
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout, "\n"));
  std::cout << "Top-Bottom:\n";
  std::stable_sort(shapes.begin(), shapes.end(),
                   [](const std::shared_ptr<Shape> &lhs, const std::shared_ptr<Shape> &rhs)
                   {
                     return lhs->isUpper(*rhs);
                   });
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout, "\n"));
  std::cout << "Bottom-Top:\n";
  std::stable_sort(shapes.begin(), shapes.end(),
                   [](const std::shared_ptr<Shape> &lhs, const std::shared_ptr<Shape> &rhs)
                   {
                     return !(lhs->isUpper(*rhs));
                   });
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout, "\n"));
}
