#include <iostream>
#include <sstream>
#include "bookmarkManager.hpp"
#include "commands.hpp"

void task1()
{
  BookmarkManager manager;

  std::string line;

  while (std::getline(std::cin, line))
  {
    std::stringstream input(line);

    commands::parseTaskArguments(input)(manager, std::cout);
  }
}
