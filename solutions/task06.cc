#include <iostream>
#include <math.h>
#include <vector>

#include "utils.h"
#include "gnuplotwrapper.h"

double BesselFunction(int m, double x, int N = 10000) {
    return 1/M_PI * utils::Integrate(N, 0, M_PI, [&m, &x](double t) {
        return std::cos(m * t - x * std::sin(t));
    } );
}

double BesselDerivative(int m, double x, int N = 10000) {
    return 1/M_PI * utils::Integrate(N, 0, M_PI, [&m, &x](double t) {
        return std::sin(t) * std::sin(m * t - x * std::sin(t));
    } );
}

double FiniteDifferenceDerivative(std::function<double(double)> f, double x, double h) {
    return (f(x + h / 2) - f(x - h / 2)) / h;
}

int main() {
    std::vector<std::vector<double>> vec;
    int N = 1000;
    double a = 0, b = 2 * M_PI;
    double h = (b - a) / N;
    for (double x = a; x < b; x += h) {
        auto LeibnizRuleSolution = BesselFunction(1, x) + BesselDerivative(0, x); 
        auto FiniteDifferenceSolution = BesselFunction(1, x) + FiniteDifferenceDerivative(
            [](double x){ return BesselFunction(0, x);}, x, 5e-5);
        vec.push_back({x, LeibnizRuleSolution, FiniteDifferenceSolution});
    }
    Gnuplot plot;
    plot("plot '-' using 1:2 title 'Leibniz integral rule', '' using 1:3 w l title 'ChangeRule'");
    plot.catData(vec, 2);
    return 0;
}
