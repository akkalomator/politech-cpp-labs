#ifndef B3_BOOKMARK_MANAGER_HPP
#define B3_BOOKMARK_MANAGER_HPP

#include <map>
#include "phonebook.hpp"

class BookmarkManager
{
public:
  enum class InsertPosition
  {
    BEFORE,
    AFTER
  };

  enum class MovePosition
  {
    FIRST,
    LAST
  };

  BookmarkManager();

  void add(const Phonebook::record_t& record);
  void store(const std::string& bookmark, const std::string& newBookmark);
  void insert(const std::string& bookmark, const Phonebook::record_t& record, InsertPosition position);
  void remove(const std::string& bookmark);
  void show(const std::string& bookmark, std::ostream& output) ;

  void move(const std::string& bookmark, int steps);
  void move(const std::string& bookmark, MovePosition position);

  void moveNext(const std::string& bookmark);
  void movePrev(const std::string& bookmark);
  void replace(const std::string& bookmark, const Phonebook::record_t& record);

  bool bookmarkExists(const std::string& bookmark) const;
  bool bookmarkValid(const std::string& bookmark);
  bool recordsEmpty() const;

private:
  using bookmarks = std::map<std::string, Phonebook::iterator>;

  Phonebook records_;
  bookmarks bookmarks_;

  bookmarks::iterator getElementIterator(const std::string& bookmark);
};

#endif
