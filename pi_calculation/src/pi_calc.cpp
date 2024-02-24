#include <iostream>
#include <type_traits>
#include <iomanip>
#include <chrono>
#include <array>

#include "numerical_integration/numerical_integration.hpp"

using namespace std::chrono_literals;
using namespace parprog;

namespace parprog {
 class PiCalculator {
  
  private:
	
	double pi = 1;
	double step = 1e-10;

  public:
	
	double calculate_pi() {
        auto func = [](const double& x){return (4/(1+x*x));};

        std::array<double, 2> limits = {0, 1};
        NumericalIntegrator<decltype(func)> integrator(func, step, limits);
        
        return integrator.integrate();
	}

	double calculate_pi_parallel() {
		return pi;
	}

    PiCalculator() = delete;
	PiCalculator(const double& step) : step{step} {}
};
}; // namespace parprog

int main() {

	double step = 0;
	
	std::cout << "Please, input the desired step: ";
	std::cin >> step;

	PiCalculator calc (step);
	
	std::chrono::high_resolution_clock clock;
	auto start_timestamp = clock.now();
	double pi = calc.calculate_pi();
	auto end_timestamp = clock.now();

	std::cout << "Pi = " << pi << std::endl; 
	std::cout << "Time taken to calculate = " << 
				(end_timestamp - start_timestamp) / 1ns << "ns" 
				<< std::endl;
	

	return 0;
}
