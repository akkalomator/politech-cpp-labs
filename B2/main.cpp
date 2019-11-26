#include <iostream>
#include <string>

void task1();
void task2();

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "invalid amount of arguments" << std::endl;
      return 1;
    }

    char *pointer = nullptr;
    int number_task = std::strtol(argv[1], &pointer, 10);
    if (*pointer)
    {
      std::cerr << "invalid argument" << std::endl;
      return 1;
    }

    switch (number_task)
    {
      case 1:
      {
        task1();
        break;
      }
      case 2:
      {
        task2();
        break;
      }
      default:
      {
        std::cerr << "invalid argument" << std::endl;
        return 1;
      }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
