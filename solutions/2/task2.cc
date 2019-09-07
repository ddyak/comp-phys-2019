#include <iostream>
#include <functional>
#include <math.h>
#include <fstream>
#include <iomanip>

/** equation of the form f(e)=0, where e is energy in main state
    for the problem where the particle is in a rectangular
    potential well of size [-a, a] and potential -|U0|. */

static const double root = -0.603898;
static const double err = 5e-7;
static const double a = 1;
static const double U0 = 1;
static const double E0 = -0.95;

static const auto f(double E) {
    const double xi = -E / U0;
    return 1 / std::tan(std::sqrt(2 * a * a * U0 * (1 - xi))) - std::sqrt(1 / xi - 1);
};

static const auto df(double E) {
    const double xi = -E / U0;
    return - a * a * std::pow(1/(std::sin(std::sqrt(2 * a * a * U0 * (1 - xi)))), 2) /
           std::sqrt(2 * a * a * U0 * (1 - xi)) - U0 / (xi * xi * 2 * std::sqrt(1 / xi - 1));
};

static double Dichotomy(const double err, const double a, const double b, std::ofstream & out)
{
    double middle = (a + b) / 2;
    double value = f(middle);
    double currentError = (b - a) / 2;
    out << currentError << std::endl;
    if (currentError < err)
        return middle;
    if (value * f(a) <= 0) {
        return Dichotomy(err, a, middle, out);
    } else {
        return Dichotomy(err, middle, b, out);
    }
}

static double FixedPointIteration(const double err, const double x, std::ofstream & out)
{
    const double lambda = 1 / df(root); 
    double value = -lambda * f(x);
    double currentError = std::abs(root - x);
    out << currentError << std::endl;
    if (currentError < err) {
        return x;
    } else {
        return FixedPointIteration(err, x + value, out);
    }
}

static double NewtonMethod(const double err, const double x, std::ofstream & out)
{
    double value = f(x) / df(x);
    double currentError = std::abs(root - x);
    out << currentError << std::endl;
    if (currentError < err) {
        return x;
    } else {
        return NewtonMethod(err, x - value, out);
    }
}

int main()
{
    std::ofstream dichotomyStream("dichotomy.csv", std::ios_base::out);
    std::ofstream fixedPointStream("fixedPointIteration.csv", std::ios_base::out);
    std::ofstream newthonStream("newthon.csv", std::ios_base::out);

    std::cout << "Dichotomy method: " << Dichotomy(err, -1, -0, dichotomyStream) << std::endl;
    std::cout << "Fixed Point Iteration method: " << FixedPointIteration(err, E0, fixedPointStream) << std::endl;
    std::cout << "Newton's method: " << NewtonMethod(err, E0, newthonStream) << std::endl;

    dichotomyStream.close();
    fixedPointStream.close();
    newthonStream.close();
    return 0;
}