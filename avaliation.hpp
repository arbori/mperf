#ifndef __AVALIATION_HPP__
#define __AVALIATION_HPP__

#include <cmath>
#include <numeric>
#include <cstdlib>
#include <vector>
#include <chrono>

using namespace std::literals;

class avaliation_result {
private:
    long _iteration_limit;
    long _elements_amount;
    std::chrono::_V2::system_clock::time_point _start;

    std::vector<double> differences;

public:
    avaliation_result(long iteration_limit, long elements_amount) : 
            _iteration_limit(iteration_limit), 
            _elements_amount(elements_amount)
        {}

    void start() { _start = std::chrono::system_clock::now(); }
    
    void stop() {
        std::chrono::duration<double, std::milli> elapsed = std::chrono::system_clock::now() - _start;
        differences.push_back(elapsed.count());
    }
    
    double average() {
        return ( std::accumulate(differences.begin(), differences.end(), 0.0) / (double) differences.size());
    }
};

class avaliation_histance {
private:
    int _step;
    long _iteration_limit;
    long _elements_amount;

    avaliation_result _innerprod_result;
    avaliation_result _qsort_result;

    void fill_randomicaly(std::vector<float>& vector, long how_many) {
        vector.clear();
        
        while(how_many-- >= 0) {
            vector.push_back((float) std::rand() / (float) RAND_MAX);
        }
    }

public:
    avaliation_histance(int step, long iteration_limit) : 
            _step(step), 
            _iteration_limit(iteration_limit), 
            _elements_amount(std::lroundl(std::pow(2.0, (double) _step))),
            _innerprod_result(avaliation_result(_iteration_limit, _elements_amount)),
            _qsort_result(avaliation_result(_iteration_limit, _elements_amount))
        {
            std::srand(std::time(nullptr));
        }

    int step() { return _step; } 
     
    long iteration_limit() { return _iteration_limit; }

    long elements_amount() { return _elements_amount; }

    double get_innerprod_average() {
        return _innerprod_result.average();
    }

    double get_qsort_average() {
        return _qsort_result.average();
    }

    void run() {
        std::vector<float> vec_a;
        std::vector<float> vec_b;

        fill_randomicaly(vec_b, _elements_amount);

        for(long iteration = 0; iteration < _iteration_limit; iteration++) {
            fill_randomicaly(vec_a, _elements_amount);
    
            _innerprod_result.start();
            std::inner_product(vec_a.begin(), vec_a.end(), vec_b.begin(), 0.0);
            _innerprod_result.stop();

            _qsort_result.start();
            std::qsort(vec_a.data(), vec_a.size(), sizeof(decltype(vec_a)::value_type),
                [](const void* x, const void* y) {
                    const float arg1 = *static_cast<const float*>(x);
                    const float arg2 = *static_cast<const float*>(y);
                    const auto cmp = arg1 <= arg2;
                    if (cmp < 0) return -1;
                    if (cmp > 0) return 1;
                    return 0;
                });
            _qsort_result.stop();
        }
    }
};

#endif //__AVALIATION_HPP__
