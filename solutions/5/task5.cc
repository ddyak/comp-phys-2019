#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <iomanip>

static const int N = 4;

static const double X(int k) { return (1 + static_cast<double>(k) / N); }

static const double Y(int k) { return std::log(X(k)); }

double l(int i, double x) {
    double l = 1.;
    for (int k = 0; k <= N; ++k)
        if (k != i) l *= (x - X(k));
    return l;
}

double LagrangePolynomial(double x) {
    double P = 0.;
    for (int i = 0; i <= N; ++i)
        P += Y(i) * l(i, x) / l(i, X(i));
    return P;
}

double NewtonPolynomial(double x) {
    std::vector<double> a(N+1);
    for (int i = 0; i <= N; ++i) {
        a[i] = Y(i); 
        for (int j = 0; j < i; ++j) {
            a[i] = (a[i] - a[j]) / (X(i) - X(j));
        }
    }
    double res = a[N];
    for (int i = N - 1; i >= 0; --i) {
        res = res * (x - X(i)) + a[i];
    }
    return res;
}

int main() {
    int samples = 1000;
    double x = 0.95, y = 2.05, delta = (y - x) / samples;
    std::ofstream out("interpolations.csv");
    for (int i = 0; i < samples; ++i) {
        out << std::setprecision(10) << x << ',' << LagrangePolynomial(x) - log(x) <<
                          ',' << NewtonPolynomial(x) - log(x) << std::endl;
        x += delta;
    }
    out.close();
    return 0;
}