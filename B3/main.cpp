#include <iostream>
#include <string>

void task1();
void task2();

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Invalid number of arguments.\n";
      return 1;
    }

    char* ptr = nullptr;
    int taskNumber = std::strtol(argv[1], &ptr, 10);
    if (*ptr != 0x00)
    {
      std::cerr << "Incorrect argument.\n";
      return 1;
    }

    switch (taskNumber)
    {
      case 1:
        task1();
        break;

      case 2:
        task2();
        break;

      default:
        std::cerr << "Incorrect argument.\n";
        return 1;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';

    return 1;
  }

  return 0;
}
