#include <iostream>
#include <functional>
#include <math.h>

/*  equation of the form f(e)=0, where e is energy in main state
    for the problem where the particle is in a rectangular
    potential well of size [-a, a] and potential -|U0|. */

static const float err = 0.0001f;
static const float a = 1.f;
static const float U0 = 1.f;

static const auto f = [](float E) {
    float xi = -E / U0;
    return 1.f / std::tan(std::sqrt(2 * a * a * U0 * (1 - xi))) - std::sqrt(1.f / xi - 1);
};

static const auto df = [](float E) {
    float xi = -E / U0;
    return a * a * U0 * std::pow(std::sin(std::sqrt(2 * a * a * U0 * (1 - xi))), 2) /
               std::sqrt(2 * a * a * U0 * (1 - xi)) +
           1.f / (xi * xi * 2 * std::sqrt(1.f / xi - 1));
};

static const float left = -1.f;
static const float right = -0.f;

static float Dichotomy(const float err, const std::function<float(float)> &f, const float a, const float b)
{
    float middle = (a + b) / 2;
    float value = f(middle);
    if (b - a < err) {
        return middle;
    }
    if (value * f(a) <= 0) {
        return Dichotomy(err, f, a, middle);
    } else {
        return Dichotomy(err, f, middle, b);
    }
}

static const float lambda = 0.5f; // lambda -> 1/f'(x), but df/dx for this task is too hard, so I just guess lambda.
static const float E0 = -0.5f;

static float FixedPointIteration(const float err, const std::function<float(float)> &f, const float x)
{
    float value = -lambda * f(x);
    if (std::abs(value) < err) {
        return x;
    } else {
        return FixedPointIteration(err, f, x - value);
    }
}

static float NewtonMethod(const float err, const std::function<float(float)> &f, const std::function<float(float)> &df, const float x)
{
    float value = f(x) / df(x);
    if (std::abs(value) < err) {
        return x;
    } else {
        return FixedPointIteration(err, f, x - value);
    }
    return df(x);
}

int main()
{
    std::cout << "Dichotomy method: " << Dichotomy(err, f, left, right) << std::endl;
    std::cout << "Fixed Point Iteration method: " << FixedPointIteration(err, f, E0) << std::endl;
    std::cout << "Newton's method: " << NewtonMethod(err, f, df, E0) << std::endl;
    return 0;
}
