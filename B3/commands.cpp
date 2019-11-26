#include "commands.hpp"
#include <algorithm>
#include <iomanip>
#include <cctype>
#include "manipulators.hpp"

using namespace std::placeholders;

const auto commandOnInvalid = std::bind([](std::ostream& output){ output << "<INVALID COMMAND>\n"; }, _2);

commands::command commands::parseTaskArguments(std::istream& input)
{
  struct command_t
  {
    const char* name;
    std::function<command(std::istream&)> action;
  };

  static const command_t Commands[] =
    {
      {"add", &parseAddArguments},
      {"store", &parseStoreArguments},
      {"insert", &parseInsertArguments},
      {"delete", &parseDeleteArguments},
      {"show", &parseShowArguments},
      {"move", &parseMoveArguments}
    };

  input >> std::noskipws;

  std::string commandName;
  input >> commandName;

  auto command = std::find_if(std::begin(Commands), std::end(Commands),
                              [&](const command_t& command) {return commandName == command.name;});

  if (command != std::end(Commands))
  {
    return command->action(input);
  }
  else
  {
    return commandOnInvalid;
  }
}

commands::command commands::parseAddArguments(std::istream& input)
{
  std::string number = detail::readNumberFromStream(input);
  std::string name = detail::readNameFromStream(input);
  if (number.empty() || name.empty())
  {
    return commandOnInvalid;
  }

  Phonebook::record_t record = {name, number};

  return std::bind(
    [&](BookmarkManager& manager, const Phonebook::record_t& record){ manager.add(record); }, _1, record);
}

commands::command commands::parseStoreArguments(std::istream& input)
{
  std::string bookmark = detail::readBookmarkFromStream(input);
  std::string newBookmark = detail::readBookmarkFromStream(input);
  if (bookmark.empty() || newBookmark.empty())
  {
    return commandOnInvalid;
  }

  std::string extraData;
  std::getline(input, extraData);
  if (!extraData.empty())
  {
    return commandOnInvalid;
  }

  return std::bind(
    [&](BookmarkManager& manager, std::ostream& output, const std::string& bookmark, const std::string& newBookmark)
    {
      if (!manager.bookmarkExists(bookmark))
      {
        output << "<INVALID BOOKMARK>\n";

        return;
      }

      manager.store(bookmark, newBookmark);
    }, _1, _2, bookmark, newBookmark);
}

commands::command commands::parseInsertArguments(std::istream& input)
{
  struct insert_positions_t
  {
    const char* name;
    insert_position position;
  };

  static const insert_positions_t InsertPositions[] =
    {
      {"before", insert_position::BEFORE},
      {"after", insert_position::AFTER}
    };

  std::string position;
  input >> manipulators::blank >> position;

  auto insertPosition = std::find_if(std::begin(InsertPositions), std::end(InsertPositions),
                                     [&](const insert_positions_t& insertPosition) { return position == insertPosition.name; });

  if (insertPosition == std::end(InsertPositions))
  {
    return commandOnInvalid;
  }

  std::string bookmark = detail::readBookmarkFromStream(input);
  std::string number = detail::readNumberFromStream(input);
  std::string name = detail::readNameFromStream(input);

  if (bookmark.empty() || number.empty() || name.empty())
  {
    return commandOnInvalid;
  }

  Phonebook::record_t record = {name, number};

  return std::bind(
    [&](BookmarkManager& manager, std::ostream& output,
        const std::string& bookmark, const Phonebook::record_t& record, insert_position position)
    {
      if (!manager.bookmarkExists(bookmark))
      {
        output << "<INVALID BOOKMARK>\n";

        return;
      }

      manager.insert(bookmark, record, position);
    }, _1, _2, bookmark, record, insertPosition->position);
}

commands::command commands::parseDeleteArguments(std::istream& input)
{
  std::string bookmark = detail::readBookmarkFromStream(input);
  if (bookmark.empty())
  {
    return commandOnInvalid;
  }

  std::string extraData;
  std::getline(input, extraData);
  if (!extraData.empty())
  {
    return commandOnInvalid;
  }

  return std::bind(
    [&](BookmarkManager& manager, std::ostream& output, const std::string& bookmark)
    {
      if (!manager.bookmarkExists(bookmark))
      {
        output << "<INVALID BOOKMARK>\n";

        return;
      }

      if (!manager.bookmarkValid(bookmark))
      {
        output << "<INVALID COMMAND>\n";

        return;
      }

      manager.remove(bookmark);
    }, _1, _2, bookmark);
}

commands::command commands::parseShowArguments(std::istream& input)
{
  std::string bookmark = detail::readBookmarkFromStream(input);
  if (bookmark.empty())
  {
    return commandOnInvalid;
  }

  std::string extraData;
  std::getline(input, extraData);
  if (!extraData.empty())
  {
    return commandOnInvalid;
  }

  return std::bind(
    [&](BookmarkManager& manager, std::ostream& output, const std::string& bookmark)
    {
      if (!manager.bookmarkExists(bookmark))
      {
        output << "<INVALID BOOKMARK>\n";

        return;
      }

      if (manager.recordsEmpty())
      {
        output << "<EMPTY>\n";

        return;
      }

      if (!manager.bookmarkValid(bookmark))
      {
        return;
      }

      manager.show(bookmark, output);
    }, _1, _2, bookmark);
}

commands::command commands::parseMoveArguments(std::istream& input)
{
  struct move_positions_t
  {
    const char* name;
    move_position position;
  };

  static const move_positions_t MovePositions[] =
    {
      {"first", move_position::FIRST},
      {"last", move_position::LAST}
    };

  std::string bookmark = detail::readBookmarkFromStream(input);
  if (bookmark.empty())
  {
    return commandOnInvalid;
  }

  std::string steps;
  input >> manipulators::blank >> steps;

  std::string extraData;
  std::getline(input, extraData);
  if (!extraData.empty())
  {
    return commandOnInvalid;
  }

  auto movePosition = std::find_if(std::begin(MovePositions), std::end(MovePositions),
                                   [&](const move_positions_t& movePosition) { return steps == movePosition.name; });

  if (movePosition == std::end(MovePositions))
  {
    int multiplier = 1;
    if (*steps.begin() == '-')
    {
      multiplier = -1;
      steps.erase(steps.begin());
    }
    else if (*steps.begin() == '+')
    {
      steps.erase(steps.begin());
    }

    auto it = std::find_if(steps.begin(), steps.end(),
                           [&](auto digit){ return !std::isdigit(digit); });

    if (it != steps.end())
    {
      return std::bind([&](std::ostream& output){ output << "<INVALID STEP>\n"; }, _2);
    }

    return std::bind(
      [&](BookmarkManager& manager, std::ostream& output, const std::string& bookmark, int steps)
      {
        if (!manager.bookmarkExists(bookmark))
        {
          output << "<INVALID BOOKMARK>\n";

          return;
        }

        manager.move(bookmark, steps);
      }, _1, _2, bookmark, std::stoi(steps) * multiplier);
  }

  return std::bind(
    [&](BookmarkManager& manager, std::ostream& output, const std::string& bookmark, move_position position)
    {
      if (!manager.bookmarkExists(bookmark))
      {
        output << "<INVALID BOOKMARK>\n";

        return;
      }

      manager.move(bookmark, position);
    }, _1, _2, bookmark, movePosition->position);
}

std::string detail::readBookmarkFromStream(std::istream& input)
{
  std::string bookmark;
  input >> manipulators::blank >> bookmark;

  auto it = std::find_if(bookmark.begin(), bookmark.end(),
                         [&](auto character){ return (!std::isalnum(character) && !(character == '-')); });

  if (it != bookmark.end())
  {
    return "";
  }

  return bookmark;
}

std::string detail::readNumberFromStream(std::istream& input)
{
  std::string number;
  input >> manipulators::blank >> number;

  auto it = std::find_if(number.begin(), number.end(),
                         [&](auto digit){ return !std::isdigit(digit); });

  if (it != number.end())
  {
    return "";
  }

  return number;
}

std::string detail::readNameFromStream(std::istream& input)
{
  if ((input >> manipulators::blank).peek() != '\"')
  {
    return "";
  }

  std::string name;
  std::getline(input, name);
  if (name.back() != '\"')
  {
    return "";
  }

  std::stringstream namestream(name);
  std::string quoted;
  namestream >> std::quoted(quoted);

  if (quoted.empty())
  {
    return "";
  }

  std::string extraData;
  std::getline(input >> manipulators::blank, extraData);
  if (!extraData.empty())
  {
    return "";
  }

  return quoted;
}
