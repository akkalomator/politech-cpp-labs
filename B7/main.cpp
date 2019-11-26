#include <iostream>
#include <stdexcept>
#include <string>

void task1();
void task2();

int main(int argc, char * argv[])
{
  try {
    if (argc != 2) {
      std::cerr << "Invalid count of arguments" << '\n';
      return 1;
    }
    switch (std::stoi(argv[1])) {
      case 1:
        task1();
        break;
      case 2:
        task2();
        break;
      default:
        std::cerr << "No such task" << '\n';
        return 1;
    }
  }
  catch (std::bad_alloc&) {
    return 2;
  }
  catch (std::invalid_argument& exception) {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  return 0;
}
