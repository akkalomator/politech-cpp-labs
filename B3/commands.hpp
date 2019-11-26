#ifndef B3_COMMANDS_HPP
#define B3_COMMANDS_HPP

#include <functional>
#include <istream>
#include "bookmarkManager.hpp"

namespace commands
{
  using insert_position = BookmarkManager::InsertPosition;
  using move_position = BookmarkManager::MovePosition;
  using command = std::function<void(BookmarkManager&, std::ostream&)>;

  command parseTaskArguments(std::istream& input);

  command parseAddArguments(std::istream& input);
  command parseStoreArguments(std::istream& input);
  command parseInsertArguments(std::istream& input);
  command parseDeleteArguments(std::istream& input);
  command parseShowArguments(std::istream& input);
  command parseMoveArguments(std::istream& input);
}

namespace detail
{
  std::string readBookmarkFromStream(std::istream& input);
  std::string readNumberFromStream(std::istream& input);
  std::string readNameFromStream(std::istream& input);
}

#endif
