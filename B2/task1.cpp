#include <functional>
#include <algorithm>
#include <sstream>
#include <map>
#include "queue-with-priority.hpp"

void onAdd(QueueWithPriority<std::string> &queue, std::stringstream &input);
void onGet(QueueWithPriority<std::string> &queue, std::stringstream &in);
void onAccelerate(QueueWithPriority<std::string> &queue, std::stringstream &in);

void task1()
{
  using queueCommand = std::function<void(QueueWithPriority<std::string> &, std::stringstream &)>;

  std::map<const std::string, queueCommand> commands =
    {
      {"add",        onAdd},
      {"get",        onGet},
      {"accelerate", onAccelerate}
    };

  QueueWithPriority<std::string> queue;

  std::string line;

  while (std::getline(std::cin, line))
  {
    std::stringstream lineStream(line);
    std::string commandName;
    lineStream >> commandName;

    auto predicate = [&](const std::pair<const std::string, queueCommand> &pair)
      {
        return (pair.first == commandName);
      };

    auto command = std::find_if(std::begin(commands), std::end(commands), predicate);

    if (command != std::end(commands))
    {
      command->second(queue, lineStream);
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << std::endl;
    }
  }
}
