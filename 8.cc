#include "matplotlibcpp/matplotlibcpp.h"
namespace plt = matplotlibcpp;

#include <iostream>
#include <vector>
#include <functional>
#include <map>

static const int a = 10, b = 2, c = 2, d = 10;

static const auto f1 = [](double x, double y, double t) {
    return a * x - b * x * y;
};

static const auto f2 = [](double x, double y, double t) {
    return c * x * y - d * y;
};

std::tuple<std::vector<double>, std::vector<double>, std::vector<double>>
RungeKuttaMethods(int N, double alpha, std::tuple<double, double> InitPoint, std::pair<double, double> bounds)
{
    std::vector<double> x, y, t;
    x.push_back(std::get<0>(InitPoint));
    y.push_back(std::get<1>(InitPoint));
    t.push_back(bounds.first);
    double h = (bounds.second - bounds.first) / N;
    for (int i = 0; i < N; ++i) 
    {
        x.push_back(x[i] + h/2 * ((1 - alpha) * f1(x[i], y[i], y[i]) + alpha * f1(x[i] + h * 0.5 / alpha * f1(x[i], y[i], t[i]),
                                                                                y[i] + h * 0.5 / alpha * f2(x[i], y[i], t[i]),
                                                                                t[i] + h * 0.5 / alpha)));
        y.push_back(y[i] + h/2 * ((1 - alpha) * f2(x[i], y[i], y[i]) + alpha * f2(x[i] + h * 0.5 / alpha * f1(x[i], y[i], t[i]),
                                                                                y[i] + h * 0.5 / alpha * f2(x[i], y[i], t[i]),
                                                                                t[i] + h * 0.5 / alpha)));
        t.push_back(t[i] + h);
    }
    return {x, y, t};
}

static const double t1 = 0, t2 = 5;
static const double predator = 6, prey = 6;
static const double alpha = 0.75;
static const int iter = 100;

int main() {
    const auto & solution = RungeKuttaMethods(iter, alpha, {predator, prey}, {t1, t2});
    std::vector<double> x = std::get<0>(solution);
    std::vector<double> y = std::get<1>(solution);
    std::vector<double> t = std::get<2>(solution);
   
    plt::figure_size(600, 700);
    plt::subplot(2, 1, 1);
    plt::named_plot("x(t)", t, x);
    plt::named_plot("y(t)", t, y);
    plt::title("Task 8: Solution for predator-prey system");
    plt::xlabel("t");
    plt::ylabel("f(t)");
    plt::legend();
    plt::subplot(2, 1, 2);
    plt::named_plot("y(x)", x, y);
    plt::xlabel("x");
    plt::ylabel("y(x)");
    plt::legend();
    plt::show();
    return 0; 
}
