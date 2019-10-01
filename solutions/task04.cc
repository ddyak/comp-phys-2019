#include <iostream>
#include <functional>
#include <math.h>
#include <iomanip>

#include "utils.h"

inline static double sh(double x) { return (std::exp(x) - std::exp(-x)) / 2; }
inline static double ch(double x) { return (std::exp(x) + std::exp(-x)) / 2; }
inline static double th(double x) { return sh(x) / ch(x); }

// Integrate from 0 to 1: 8.03491
static const double a1 = 0, b1 = 1;

static const double f_1(double x) {
    return (std::sin(M_PI * std::pow(x, 5))) / std::pow(x, 5) / (1 - x);
};

static const double x1(double t, double a, double b) {
    return 1./2 * (a + b) + 1./2 * (b - a) * th(t);
};

static const double ft_1(double t) {
    return f_1(x1(t, a1, b1)) * (b1 - a1) / (2 * std::pow(ch(t), 2));
};

// Integrate from 0 to +inf: 2.981003
static const double a2 = 0;

static const double f_2(double x) {
    return std::exp(-std::sqrt(x) + std::sin(x / 10));
};

static const double x2(double t) { return t/(1 - t); }

static const double ft_2(double t) {
    return f_2(x2(t)) * 1 / std::pow((1 - t), 2);
};

int main() {
    std::cout << std::setprecision(10);

    /** T = max possible value, which can be computated in double (becose exp^18.5 ~ too much)
    *   Smirnov, OVF part I, p. 66, f. (41), without any proofs
    */

    double T = 18.5; 
    int N = std::pow(2 * T * std::sqrt(2) / M_PI, 2);
    std::cout << "Integral with singularities in 0 and 1: " << utils::Integrate(N, -T, T, ft_1) << std::endl;
    
    /** 1st approach. Set boundary (b):
     *      R = Integrate e^(-sqrt(x)) from b to inf
     *      R = 2(sqrt(b) + 1) * e^(-sqrt(b)) 
     *      b ~ 500 (numerical solution by Wolfram or use method from 2nd task)
     *  2nd approach. Use variable replacement:
     *      x = t/(1-t)    
     *      integrate from 0 to 1
    */
    
    N = 1'000'000;
    double b = 500 * M_PI;
    std::cout << "Integral with +inf use limit boundary: " << utils::Integrate(N, a2, b, f_2) << std::endl; 
    std::cout << "Integral with +inf use x = t/(1-t): " << utils::Integrate(N, 0, 1-1e-8, ft_2) << std::endl; 

    return 0;
}
