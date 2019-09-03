#include <iostream>
#include <functional>
#include <math.h>

// Integrate from -1 to 1: = pi/2
static const float f1(float x) {
    return 1.f/(1 + std::pow(x, 2));
};
// Integrate from 0 to 1: 1.29587400873
static const float f2(float x) {
    return std::pow(x, 1.f/3) * std::exp(std::sin(x));
};

auto f = f1; // set f1 or f2 function into loop

float TrapezoidalRule(int N, float a, float b) {
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

float SimpsonRule(int N, float a, float b) {
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
    for (int N : {4, 8, 16}) {
        std::cout << "Trapezoidal Rule with " << N << " iterations: " << TrapezoidalRule(N, -1, 1) << std::endl;
        std::cout << "Simpson Rule " << N << " iterations: " << SimpsonRule(N, -1, 1) << std::endl;
    }
    return 0;
}
