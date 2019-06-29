#include <iostream>
#include <functional>
#include <math.h>
// #include "4.cc"

static double sh(double x) {
    return (std::exp(x) - std::exp(-x)) / 2;
}

static double ch(double x) {
    return (std::exp(x) + std::exp(-x)) / 2;
}

static double th(double x) {
    return sh(x)/ch(x);
}

// Integrate from 0 to 1: 2.82122
static const double a1 = 0.;
static const double b1 = 1.;

static const auto f_5a = [](double x) {
    return (1 + std::cos(x)) / std::pow(x, 1./3);
};

static const auto x = [](double t, double a, double b) {
    return 1./2*(a + b) + 1./2*(b - a) * th(t);
};

static const auto f_5at = [](double t) {
    return f_5a(x(t, a1, b1)) * (b1 - a1)/2 / std::pow(ch(t), 2);
};

// Integrate from 0 to +inf: 3.03147
static const double a2 = 0.;

static const auto f_5b = [](double x) {
    return (1 + std::exp(-x))/(1 + std::pow(x, 3./2));
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
    int N = std::pow(2*T*std::sqrt(2) / M_PI, 2); // Smirnov, OVF part I, p. 66, f. (41), without proof
    std::cout << "First integral with Singularity in 0: " << SimpsonRule(N, f_5at, -T, T) << std::endl;
    
    /*  b = |a/(n-1)delta|^(1/(n-1)), where |f(x)| <= Ax^-n
        for our case we use ~x^(-3/2) => A=1, n=-3/2; */
    const double err = 1e-10;
    const int iteration = 1e4;
    double b = std::pow(std::abs(1./(-3./2/err)), -2./5);
    std::cout << "Second integral with +inf: " << SimpsonRule(iteration, f_5b, a2, b) << std::endl; 
    return 0;
}