#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <tuple>
#include <numeric> // std::iota
#include <iomanip>

const auto roots = {1.57079632679, 1.29587400873};

static double f1(double x) {
    return 1.f/(1 + std::pow(x, 2));
};

static double f2(double x) {
    return std::pow(x, 1.f/3) * std::exp(std::sin(x));
};

double LeftRiemannSum(double left, double right, double (*f)(double)) {
    return f(left);
}

double RightRiemannSum(double left, double right, double (*f)(double)) {
    return f(right);
}

double TrapezoidalRule(double left, double right, double (*f)(double)) {
    return (f(left) + f(right))/2;
}

double SimpsonRule(double left, double right, double (*f)(double)) {
    return (f(left) + 4 * f((left + right) / 2) + f(right)) / 6;
}

double Integrate(int N, double a, double b, double (*f)(double), double (*rule)(double, double, double (*f)(double))) {
    double h = (b - a) / N;
    double left = a;
    double right = a + h;
    double sum = 0;
    for (int i = 0; i < N; ++i) {
        sum += rule(left, right, f);
        left += h;
        right += h;
    }
    return sum * h;
}

int main() {
    static int fooCounter = 1;
    std::vector<int> ivec(16);
    std::iota(ivec.begin(), ivec.end(), 1);

    for (auto [f, root, a, b]: {std::tuple{f1, 1.57079632679, -1, 1}, std::tuple{f2, 1.29587400873, 0, 1}}) {
        std::ofstream out("f" + std::to_string(fooCounter++) + ".csv", std::ios_base::out);
        out << std::setprecision(10);
        for (int N : ivec) {
            for (auto rule : {LeftRiemannSum, RightRiemannSum, TrapezoidalRule, SimpsonRule})
                out << std::abs(root - Integrate(N, a, b, f, rule)) << ((rule!=SimpsonRule)?",":"");
            out << std::endl;
        }
        out.close();
    }
    return 0;
}
