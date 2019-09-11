#include <iostream>
#include <functional>
#include <math.h>
#include <iomanip>

inline static double sh(double x) { return (std::exp(x) - std::exp(-x)) / 2; }
inline static double ch(double x) { return (std::exp(x) + std::exp(-x)) / 2; }
inline static double th(double x) { return sh(x) / ch(x); }

static const double err = 1e-8;

// Integrate from 0 to 1: 8.03491
static const double a1 = 0, b1 = 1;

static const double f_4a(double x) {
    return (std::sin(M_PI * std::pow(x, 5))) / std::pow(x, 5) / (1 - x);
};

static const double x(double t, double a, double b) {
    return 1./2 * (a + b) + 1./2 * (b - a) * th(t);
};

static const double ft_4a(double t) {
    return f_4a(x(t, a1, b1)) * (b1 - a1) / (2 * std::pow(ch(t), 2));
};

// Integrate from 0 to +inf: 2.981003
static const double a2 = 0;

static const double f_4b(double x) {
    return std::exp(-std::sqrt(x) + std::sin(x / 10));
};

double SimpsonRule(int N, const std::function<double(double)> &f, double a, double b) {
    double h = (b - a) / N;
    double left = a;
    double right = a + h;
    double sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += f(left) + 4 * f((left + right) / 2) + f(right);
        left += h;
        right += h;
    }
    return sum * h / 6;
}

int main() {
    std::cout << std::setprecision(10);

    /** T = max possible value, which can be computated in double (becose exp^18.5 ~ too much)
    *   Smirnov, OVF part I, p. 66, f. (41), without any proofs
    */
    double T = 18.5; 
    int N = std::pow(2 * T * std::sqrt(2) / M_PI, 2); 
    std::cout << "Integral with singularities in 0 and 1: " << SimpsonRule(N, ft_4a, -T, T) << std::endl;
    
    /** R = Integrate e^(-sqrt(x)) from b to inf
     *  R = 2(sqrt(b) + 1) * e^(-sqrt(b)) 
     *  b ~ 500 (numerical solution by Wolfram or use method from 2nd task)
    */
    const int iteration = 1e8;

    double b = 500 * M_PI;
    std::cout << "Integral with +inf: " << SimpsonRule(iteration, f_4b, a2, b) << std::endl; 
    return 0;
}
