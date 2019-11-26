#include <exception>
#include <algorithm>
#include <iterator>
#include "tokens.hpp"

int main(int argc, char *argv[])
{
  try
  {
    unsigned int line_width = 40;
    switch (argc)
    {
      case 1:
        break;
      case 3:
      {
        if (static_cast<std::string>(argv[1]) != "--line-width")
        {
          std::cerr << "Invalid settings\n";
          return 1;
        }
        line_width = std::atoi(argv[2]);
        if (line_width < 24)
        {                          //max width of number/word + " ---"
          std::cerr << "Invalid width\n";
          return 1;
        }
        break;
      }
      default:
        std::cerr << "Invalid number of input parameters\n";
        return 1;
    }
    Tokens tokens;
    std::copy(std::istream_iterator<Token>(std::cin), std::istream_iterator<Token>(), std::back_inserter(tokens));
    std::vector<std::string> strings = process_tokens(tokens, line_width);
    std::copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
  } catch (const std::bad_alloc &)
  {
    return 2;
  } catch (const std::exception &exception)
  {
    std::cerr << exception.what() << '\n';
    return 1;
  }
}
