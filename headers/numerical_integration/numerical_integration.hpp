#include "mpi.h"
#include <array>
#include <exception>
namespace parprog {

template <typename Function>
class NumericalIntegrator {

	Function func;
    double step;
    std::array<double, 2> limits;

  public:

    double integrate() {
       
        double sum = 0;

        for (double x = limits[0]; x < limits[1]; x += step) {
            sum += func(x)*step;
        }
        
        return sum;
    }

    NumericalIntegrator(const Function& func, const double& step, const std::array<double, 2>& limits) 
                                                        : func{func}, step{step}, limits{limits} {
        if (step > limits[1] - limits[0]) {
            throw std::logic_error("Step in numerical integration should lie in bound (0, limits[1] - limits[0])");
        }
        else if(limits[1] - limits[0] <= 0) {
            throw std::logic_error("limits[1] <= limits[0], (higher limit of integration is lower or equal to lower limit)");
        }
        else if(step <= 0) {
            throw std::logic_error("step <= 0");
        }
    }
};

};
