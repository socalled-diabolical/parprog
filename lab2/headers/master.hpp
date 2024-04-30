#include "task.hpp"
namespace integration {
class Master {
  Master(const double &start, const double &end, const size_t &thread_amount)
      : start{start}, end{end}, thread_amount{thread_amount} {}

  void create_equal_tasks() {}

private:
  double start;
  double end;
  size_t thread_amount;
};
} // namespace integration
