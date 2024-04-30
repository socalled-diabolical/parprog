#include "task.hpp"
#include <chrono>
#include <cmath>
#include <iostream>
int main() {
  const auto start_t{std::chrono::steady_clock::now()};
  double start = 0.01;
  double end = 1000;
  double step = 1e-7;

  using namespace integration;

  std::function<double(double)> func = [](double x) {
    return std::sin(x) / (x * x);
  };

  task::Task task{step, 1 / end, 1 / start, func};

  double sum = task.calculate_sum();
  const auto end_t{std::chrono::steady_clock::now()};

  const std::chrono::duration<double> elapsed{end_t - start_t};

  std::cout << "Elapsed: " << elapsed.count() << std::endl;
  std::cout << "Sum: " << sum << std::endl;

  return 0;
}
