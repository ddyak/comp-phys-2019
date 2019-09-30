#include <math.h>
#include <vector>
#include <iostream>
#include "gnuplotwrapper.h"

const int N = 10000;
double x1 = 0, x2 = M_PI, h = (x2-x1)/ (N + 1);

double f(double x) {
    return sin(x);
}

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
    // A' @see 1.6, Smirnov, part 2
    std::vector<double> a(N + 1, 1);
    std::vector<double> b(N + 1, -2); 
    std::vector<double> c(N + 1, 1);
    a[0] = 0;
    c[N - 1] = 0;

    std::vector<double> x, d;
    for (int i = 0; i < N + 1; ++i) {
        x.push_back(x1 + h*i);
        d.push_back(h*h*f(x[i]));
    }

    std::vector<double> v(N, 0);
    v[0] = 1;
    v[N - 1] = 1;
    std::vector<double> minus_u(N, 0);
    minus_u[0] = -1;
    minus_u[N - 1] = -1;

    auto p = TridiagonalMatrixAlgorithm(a, b, c, d);
    auto q = TridiagonalMatrixAlgorithm(a, b, c, minus_u);
    double x_n = (d[N] - v[0] * p[0] - a[N] * p[N-1]) / (b[N] + v[0] * q[1] + a[N] * q[N-1]);    
    
    std::vector<double> y(N + 1, 0);
    for (int i = 0; i < N + 1; ++i)
        y[i] = p[i] + x_n * q[i];

    std::vector<std::vector<double>> data;
    for (int i = 0; i < N; ++i)
        data.push_back({x[i], y[i]});
    Gnuplot plot;
    plot("plot '<cat' using 1:2 w l");
    plot.catData(data, 1);
    return 0;
}
