#include <iostream>
#include <vector>
#include <functional>
#include <math.h>

static const double x0 = 0;
static const double y_0 = 1;
static const double left = 0;
static const double right = 3;

/** dy/dx = f(x, y) */
static const auto f = [](double x, double y) {
    return -y;
};

std::pair<std::vector<double>, std::vector<double>> 
EulerFirst(int N, const std::function<double(double, double)> &f, std::pair<double, double> CauchyProblem, std::pair<double, double> bounds) {
    std::vector<double> x, y;
    x.push_back(CauchyProblem.first);
    y.push_back(CauchyProblem.second);
    double h = (bounds.second - bounds.first) / N;
    for (int i = 0; i < N; ++i) {
        y.push_back(y.back() + h*f(x.back(), y.back()));
        x.push_back(x.back() + h);
    }
    return {x, y};
}

std::pair<std::vector<double>, std::vector<double>> 
RungeKuttaMethods(int N, double alpha, const std::function<double(double, double)> &f, std::pair<double, double> CauchyProblem, std::pair<double, double> bounds) {
    std::vector<double> x, y;
    x.push_back(CauchyProblem.first);
    y.push_back(CauchyProblem.second);
    double h = (bounds.second - bounds.first) / N;
    for (int i = 0; i < N; ++i) {
        y.push_back(y.back()+h*((1-alpha)*f(x.back(), y.back()) + alpha*f(x.back() + h/(2*alpha), y.back() + h/(2*alpha)*f(x.back(), y.back()))));
        x.push_back(x.back() + h);
    }
    return {x, y};
}

std::pair<std::vector<double>, std::vector<double>> 
EulerCorrected(int N, const std::function<double(double, double)> &f, std::pair<double, double> CauchyProblem, std::pair<double, double> bounds) {
    return RungeKuttaMethods(N, 0.5, f, CauchyProblem, bounds);
}

std::pair<std::vector<double>, std::vector<double>> 
EulerModified(int N, const std::function<double(double, double)> &f, std::pair<double, double> CauchyProblem, std::pair<double, double> bounds) {
    return RungeKuttaMethods(N, 1, f, CauchyProblem, bounds);
}


int main () {
    const int N = 100;
    auto solution = RungeKuttaMethods(N, 0.75, f, {x0, y_0}, {left, right});
    for (int i = 0; i <= N; ++i) {
        std::cout << solution.first.at(i) << '\t' << solution.second.at(i) - std::exp(-3./N*i) << std::endl; 
    }
    return 0;
}

// Runge kut 2, 4;
// 