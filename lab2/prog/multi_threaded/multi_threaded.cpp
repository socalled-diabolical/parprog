#include "task.hpp"
#include <cmath>
#include <future>
#include <thread>

using namespace integration;

int main() {
  const auto start_timestamp{std::chrono::steady_clock::now()};
  double start = 0.01;
  double end = 1000;
  double step = 1e-7;

  size_t thread_amount = std::thread::hardware_concurrency();

  std::function<double(double)> func = [](double x) {
    return std::sin(x) / (x * x);
  };

  task::Task task{step, 1 / end, 1 / start, func};
  auto task_pairs = task.split_into_n_tasks(thread_amount);
  std::vector<std::future<double>> results;
  for (auto &&x : task_pairs) {
    results.emplace_back(x.first.get_future());
  }

  std::vector<std::thread> threads;
  for (auto &&x : task_pairs) {
    threads.emplace_back(std::move(x.first), x.second);
  }

  for (auto &&x : threads) {
    x.join();
  }

  double sum = 0;
  for (auto &&x : results) {
    sum += x.get();
  }

  const auto end_timestamp{std::chrono::steady_clock::now()};
  std::chrono::duration<double> elapsed{end_timestamp - start_timestamp};
  std::cout << "Elapsed: " << elapsed.count() << std::endl;
  std::cout << "Sum: " << sum << std::endl;
  return 0;
}
