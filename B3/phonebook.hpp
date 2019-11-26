#ifndef B3_PHONEBOOK_HPP
#define B3_PHONEBOOK_HPP

#include <list>
#include <string>

class Phonebook
{
public:
  struct record_t
  {
    std::string name;
    std::string number;
  };

  using record_list = std::list<record_t>;

  using value_type = record_list::value_type;
  using difference_type = record_list::difference_type;
  using size_type = record_list::size_type;

  using reference = record_list::reference;
  using const_reference = record_list::const_reference;

  using pointer = record_list::pointer;
  using const_pointer = record_list::const_pointer;

  using iterator = record_list::iterator;
  using const_iterator = record_list::const_iterator;

  using reverse_iterator = record_list::reverse_iterator;
  using const_reverse_iterator = record_list::const_reverse_iterator;

  iterator begin() noexcept { return list_.begin(); };
  const_iterator cbegin() const noexcept { return list_.cbegin(); };

  iterator end() noexcept { return list_.end(); };
  const_iterator cend() const noexcept { return list_.cend(); };

  bool empty() const noexcept { return list_.empty(); };
  size_type size() const noexcept { return list_.size(); };
  size_type max_size() const noexcept { return list_.max_size(); };

  void push_back(const record_t& value) { list_.push_back(value); };
  iterator insert(const_iterator pos, const record_t& value) { return list_.insert(pos, value); };
  iterator erase(const_iterator pos) { return list_.erase(pos); };

private:
  record_list list_;
};

#endif
