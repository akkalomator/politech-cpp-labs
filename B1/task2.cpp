#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <iostream>

const size_t INITIAL_SIZE = 1024;

void task2(const char* filename)
{
  using charArray = std::unique_ptr<char[], decltype(&free)>;

  std::ifstream inputFile(filename);
  if (!inputFile)
  {
    throw std::ios_base::failure("Failed to open the file");
  }

  size_t size = INITIAL_SIZE;

  charArray arr(static_cast<char*>(malloc(size)), &free);

  size_t i = 0;
  while (inputFile)
  {
    inputFile.read(&arr[i], INITIAL_SIZE);
    i += inputFile.gcount();

    if (inputFile.gcount() == INITIAL_SIZE)
    {
      size += INITIAL_SIZE;
      charArray temp(static_cast<char*>(realloc(arr.get(), size)), &free);

      if (temp)
      {
        arr.release();
        std::swap(arr, temp);
      }
      else
      {
        throw std::runtime_error("Failed to realloc");
      }
    }
  }
  inputFile.close();
  
  std::vector<char> vector(&arr[0], &arr[i]);

  // I'd better use printCollection, but acceptance tests require different output format
  for (const auto& it: vector)
  {
    std::cout << it;
  }
}
