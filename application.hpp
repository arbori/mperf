#ifndef __PARAMETERS_HPP__
#define __PARAMETERS_HPP__

#include <cstdlib>
#include <iostream>

#include "avaliation.hpp"

namespace mperf {

    class application_context {
    private:
        int _avaliations_limit;
        long _interation_limit;
        avaliation_histance _histance;

    public:
        application_context(int argc, char **argv) : _avaliations_limit(std::atoi(argv[1])), _interation_limit(std::atol(argv[2])), _histance(_avaliations_limit, _interation_limit) {
        }

        void start() {
            std::cout << "Computing average for Inner product and Quicksort...\n";
            
            _histance.run();

            std::cout << "Inner product average: " << _histance.get_innerprod_average() << std::endl
                << "Quicksort average: " << _histance.get_qsort_average() << std::endl;
        }
    };

}

#endif
