#include "gnuplotwrapper.h"

#include <iostream>
#include <vector>
#include <functional>

static const int a = 10, b = 2, c = 2, d = 10;
static const double f1(double x, double y) { return a * x - b*x*y; };
static const double f2(double x, double y) { return c*x*y - d * y; };

std::vector<std::vector<double>>
RungeKuttaMethods(int N, double alpha, std::pair<double, double> InitPoint, std::pair<double, double> bounds)
{
    std::vector<std::vector<double>> data;
    auto x = InitPoint.first;
    auto y = InitPoint.second;
    auto t = bounds.first;    
    data.push_back({t, x, y});
    double h = (bounds.second - bounds.first) / N;
    for (int i = 0; i < N; ++i) {
        double t = data[i][0], x = data[i][1], y = data[i][2];
        double next_t = t + h,
        next_x = x + h * ((1 - alpha) * f1(x, y) + alpha * f1(x + h / (2 * alpha) * f1(x, y), y + h / (2 * alpha) * f2(x, y))),
        next_y = y + h * ((1 - alpha) * f2(x, y) + alpha * f2(x + h / (2 * alpha) * f1(x, y), y + h / (2 * alpha) * f2(x, y)));
        data.push_back({next_t, next_x, next_y});
    }
    return data;
}

static const auto time_interval= std::make_pair(0., 50.);
static const double predator = 6, prey = 6;
static const double alpha = 0.75;
static const int N = 10000;

int main() {
    const auto solution = RungeKuttaMethods(N, alpha, {predator, prey}, time_interval);
    Gnuplot plot; 
    plot("plot '-' using 2:3  w l title 'Runge 2lvl'");
    plot.catData(solution);
    return 0; 
}
