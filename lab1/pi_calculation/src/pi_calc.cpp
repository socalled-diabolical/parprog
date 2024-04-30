#include <iostream>
#include <iomanip>
#include <chrono>
#include <array>
#include <thread>
#include <vector>
#include "numerical_integration/numerical_integration.hpp"

#define PI_CONSTANT 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

using namespace std::chrono_literals;
using namespace parprog;

namespace parprog {

class PiCalculator {
  
  private:
	
	double pi = 1;
	double step = 1e-10;

  public:
	
	double calculate_pi_fragment(std::array<double, 2> limits) {
        auto func = [](const double& x){return (4/(1+x*x));};

        NumericalIntegrator<decltype(func)> integrator(func, step, limits);
        
        return integrator.integrate();
	}

	double calculate_pi_parallel() {
		return pi;
	}

    PiCalculator() = delete;
	PiCalculator(const double& step) : step{step}{}
};

}; // namespace parprog

int main() {

	double step = 1e-9;
        
    MPI_Init(nullptr, nullptr);
	std::chrono::high_resolution_clock clock;

    int my_rank = 0;
    int amount_of_communicators = 0;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &amount_of_communicators);
    
    double start_point, end_point = 0;

    double limits_recv[2];
    std::vector<double> limits;
    double limits_step = 1.0/amount_of_communicators;

    double start = 0;
    for (int i = 0; i < amount_of_communicators; ++i, start += limits_step) {
        limits.push_back(start);
        limits.push_back(start + limits_step);
    }

    MPI_Scatter(limits.data(), 2, MPI_DOUBLE, limits_recv, 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    std::array<double, 2> limits_arr {limits_recv[0], limits_recv[1]};
   	
    auto start_timestamp = clock.now();

    PiCalculator calc {step};	
    double pi_part = calc.calculate_pi_fragment(limits_arr);
	double pi = 0;

    MPI_Reduce(&pi_part, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(my_rank == 0) {
        auto end_timestamp = clock.now();
    
        std::cout << "Pi_parallel = " << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10) << pi << std::endl; 
        std::cout << "Difference with PI_CONSTANT = " << std::fixed << 
                      std::setprecision(std::numeric_limits<double>::max_digits10) << PI_CONSTANT - pi << std::endl;
        std::cout << "Time taken to calculate in parallel = " << 
                    (end_timestamp - start_timestamp) / 1ns << "ns" 
                    << std::endl;
        auto delta_parallel = (end_timestamp - start_timestamp) / 1ns;
    }

    MPI_Finalize();

	return 0;
}
