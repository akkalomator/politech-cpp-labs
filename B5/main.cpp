#include <iostream>
#include <string>

void task1(std::istream &in, std::ostream &out);

void task2(std::istream &in, std::ostream &out);

int main(int args, char *argv[])
{

  if (args != 2)
  {
    std::cerr << "Invalid number of arguments";
    return 1;
  }

  try
  {
    int option = std::stoi(argv[1]);
    switch (option)
    {
      case 1:
        task1(std::cin, std::cout);
        break;
      case 2:
        task2(std::cin, std::cout);
        break;
      default:
        std::cerr << "Incorrect argument.\n"  ;
        return 1;
    }
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
