#include <iostream>
#include <functional>
#include <math.h>

// Integrate from -1 to 1: = pi/2
static const auto f_4a = [](float x) {
    return 1.f/(1+std::pow(x, 2));
};
// Integrate from 0 to 1: 1.29587400873
static const auto f_4b = [](float x) {
    return std::pow(x, 1.f/3)*std::exp(std::sin(x));
};

float TrapezoidalRule(int N, const std::function<float(float)> &f, float a, float b) {
    float h = (b - a) / N;
    float left = a;
    float right = a + h;
    float sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += (f(left) + f(right));
        left += h;
        right += h;
    }
    return sum * h / 2;
}

float SimpsonRule(int N, const std::function<float(float)> &f, float a, float b) {
    float h = (b - a) / N;
    float left = a;
    float right = a + h;
    float sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += f(left) + 4 * f((left + right) / 2) + f(right);
        left += h;
        right += h;
    }
    return sum * h / 6;
}

int main() {
    for (int N : {4, 8, 16}) { // set f1 or f2 function into loop
        std::cout << "Trapezoidal Rule with " << N << " iterations: " << TrapezoidalRule(N, f_4a, -1, 1) << std::endl;
        std::cout << "Simpson Rule " << N << " iterations: " << SimpsonRule(N, f_4a, -1, 1) << std::endl;
    }
    return 0;
}
