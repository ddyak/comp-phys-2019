#include <math.h>
#include <vector>
#include <iostream>
#include "gnuplotwrapper.h"

double f(double x) {
    return sin(x);
}

const int N = 200;
double x1 = 0, x2 = M_PI, h = (x2-x1)/N;

std::vector<double> TridiagonalMatrixAlgorithm(std::vector<double>& a, std::vector<double>& b, 
                                std::vector<double>& c, std::vector<double>& d) {
    std::vector<double> y(N);
    for (int i = 0; i < N; ++i) {
        double xi = a[i]/b[i-1];
        a[i] = 0;
        b[i] -= xi * c[i-1];
        d[i] -= xi * d[i-1];
    }
    y[N-1] = d[N-1] / b[N-1];
    for (int i = N - 2; i >= 0; --i)
        y[i] = 1 / b[i] * (d[i] - c[i] * y[i+1]);    
    return y;
}

int main() {
    std::vector<double> a(N, 1); // [0, 1]
    std::vector<double> b(N, -2); // [-2]
    std::vector<double> c(N, 1); // [1, 0]
    a[0] = 0;
    c[N-1] = 0;

    std::vector<double> x, d;
    for (int i = 0; i < N; ++i) {
        x.push_back(x1 + h*i);
        d.push_back(h*h*f(x[i]));
    }
    auto y = TridiagonalMatrixAlgorithm(a, b, c, d);

    std::vector<std::vector<double>> data;
    for (int i = 0; i < N; ++i)
        data.push_back({x[i], y[i]});
    Gnuplot plot;
    plot("plot '<cat' using 1:2 w l");
    plot.catData(data, 1);
    return 0;
}
