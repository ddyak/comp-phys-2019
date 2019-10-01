#include <iostream>
#include <vector>
#include <functional>
#include <math.h>

#include "gnuplotwrapper.h"

static const auto CauchyProblemXY = std::make_pair(0., 1.);
static const auto bounds = std::make_pair(0., 3.);

/** dy/dx = f(x, y) */
const double f(double x, double y) {
    return -y;
};

std::pair<std::vector<double>, std::vector<double>> 
EulerFirst(int N, const std::function<double(double, double)> &f, 
            std::pair<double, double> CauchyProblem, std::pair<double, double> bounds) {
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

/** Euler corrected when alpha = 0.5, Euler modified when alpha = 1 */
std::pair<std::vector<double>, std::vector<double>> 
RungeKuttaMethods(int N, double alpha, const std::function<double(double, double)> &f,
                    std::pair<double, double> CauchyProblem, std::pair<double, double> bounds) {
    std::vector<double> x, y;
    x.push_back(CauchyProblem.first);
    y.push_back(CauchyProblem.second);
    double h = (bounds.second - bounds.first) / N;
    for (int i = 0; i < N; ++i) {
        y.push_back(y.back() + h*((1-alpha)*f(x.back(), y.back()) + alpha*f(x.back() + h/(2*alpha), y.back() + h/(2*alpha)*f(x.back(), y.back()))));
        x.push_back(x.back() + h);
    }
    return {x, y};
}

std::pair<std::vector<double>, std::vector<double>> 
RungeKuttaMethods4lvl(int N, const std::function<double(double, double)> &f,
                    std::pair<double, double> CauchyProblem, std::pair<double, double> bounds) {
    std::vector<double> x, y;
    x.push_back(CauchyProblem.first);
    y.push_back(CauchyProblem.second);
    double h = (bounds.second - bounds.first) / N;
    for (int i = 0; i < N; ++i) {
        auto k1 = f(x.back(), y.back());
        auto k2 = f(x.back() + h/2, y.back() + h/2*k1);
        auto k3 = f(x.back() + h/2, y.back() + h/2*k2);
        auto k4 = f(x.back() + h, y.back() + h*k3);
        y.push_back(y.back() + h/6 * (k1 + 2*k2 + 2*k3 + k4));
        x.push_back(x.back() + h);
    }
    return {x, y};
}

int main () {
    const int N = 100;
    auto solution = RungeKuttaMethods(N, 0.75, f, CauchyProblemXY, bounds);
    auto solution2 = RungeKuttaMethods4lvl(N, f, CauchyProblemXY, bounds);
    
    std::vector<std::vector<double>> data;
    for (int i = 0; i <= N; ++i) {
        std::vector<double> temp = {solution.first.at(i), 
                                    std::abs(solution.second.at(i) - std::exp(-3./N*i)),
                                    std::abs(solution2.second.at(i) - std::exp(-3./N*i))};
        data.emplace_back(temp);    
    }

    Gnuplot plot;
    plot("set logscale y");
    plot("plot '-' using 1:2 title 'Runge 2lvl', '' using 1:3 title 'Runge 4lvl'");
    plot.catData(data, 2);
    return 0;
}
