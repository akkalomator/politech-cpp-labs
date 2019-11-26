#include <algorithm>
#include <iterator>
#include <string>
#include <list>
#include <map>

bool isInSet(const std::string &word, std::map<std::string, bool> &set)
{
  auto it = set.find(word);
  if(!it->second)
  {
    it->second = true;
    return true;
  }
  else
  {
    return false;
  }

}

void task1(std::istream &in, std::ostream &out)
{
  std::list<std::string> words;
  std::copy(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>(), std::back_inserter(words));

  std::map<std::string, bool> wordSet;
  std::transform(words.begin(), words.end(), std::inserter(wordSet, wordSet.begin()),
                 [](const std::string &word)
                 { return std::pair<std::string, bool>(word, false); });

  std::copy_if(words.begin(), words.end(), std::ostream_iterator<std::string>(out, "\n"),
               [&](const std::string &word)
               { return isInSet(word, wordSet); });
}
