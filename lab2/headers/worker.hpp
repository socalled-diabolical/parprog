#include <cmath>
#include <queue>
#include <thread>

#include "task.hpp"

namespace integration {
namespace worker {
class Worker {
  std::queue<Task> tasks;
}; // Worker
} // namespace worker
} // namespace integration
