#include <iostream>
#include <functional>
#include <math.h>

inline static double sh(double x) {
    return (std::exp(x) - std::exp(-x)) / 2;
}

inline static double ch(double x) {
    return (std::exp(x) + std::exp(-x)) / 2;
}

inline static double th(double x) {
    return sh(x)/ch(x);
}

// Integrate from 0 to 1: 8.03491
static const double a1 = 0.;
static const double b1 = 1.;

inline static const auto f_4a(double x) {
    return (std::sin(M_PI * std::pow(x, 5))) / std::pow(x, 5) / (1 - x);
};

static const auto x = [](double t, double a, double b) {
    return 1./2 * (a + b) + 1./2 * (b - a) * th(t);
};

inline static const auto ft_4a(double t) {
    return f_4a(x(t, a1, b1)) * (b1 - a1)/2 / std::pow(ch(t), 2);
};

// Integrate from 0 to +inf: 2.981003
static const double a2 = 0.;

inline static const auto f_4b(double x) {
    return std::exp(-std::sqrt(x) + std::sin(x/10));
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
    double T = 10; 
    /// Smirnov, OVF part I, p. 66, f. (41), without proof
    int N = std::pow(2 * T * std::sqrt(2) / M_PI, 2); 
    std::cout << "First integral with Singularity in 0: " << SimpsonRule(N, ft_4a, -T, T) << std::endl;
    
    // TODO: переделать.
    /*  b = |a/(n-1)delta|^(1/(n-1)), where |f(x)| <= Ax^-n
        for our case we use ~x^(-3/2) => A=1, n=-3/2; */
    const double err = 1e-10;
    const int iteration = 1e4;
    double b = 1000;//std::pow(std::abs(1./(-3./2/err)), -2./5);
    std::cout << "Second integral with +inf: " << SimpsonRule(iteration, f_4b, a2, b) << std::endl; 
    return 0;
}