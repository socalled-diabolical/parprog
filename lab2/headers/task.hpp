#include <chrono>
#include <functional>
#include <future>
#include <iostream>

namespace integration {
namespace task {

class Task;
double calculate_sum_gl(Task task);

class Task {
  // for now we will just calculate the function at n points and sum it up
public:
  Task(const double &step, const double &start, const double &end,
       const std::function<double(double)> &function, size_t task_id = 0)
      : step{step}, start{start}, end{end}, function{function},
        task_id{task_id} {}

  double calculate_sum() {
    for (double x = start; x < end; x += step) {
      sum += function(x) * step;
    }
    return sum;
  }

  std::vector<std::pair<std::packaged_task<double(Task)>, Task>>
  split_into_n_tasks(const size_t &n) {
    std::vector<std::pair<std::packaged_task<double(Task)>, Task>> tasks;

    size_t i = 0;
    for (double curr = start, curr_e = start + (end - start) / n; curr < end;
         curr += (end - start) / n, curr_e += (end - start) / n) {

      tasks.emplace_back(calculate_sum_gl,
                         Task{step, curr, curr_e, function, i});
      ++i;
    }
    return tasks;
  }

private:
  size_t task_id;
  double sum = 0;
  double step;
  double start;
  double end;
  std::function<double(double)> function;
};

double calculate_sum_gl(Task task) { return task.calculate_sum(); }
} // namespace task
} // namespace integration
