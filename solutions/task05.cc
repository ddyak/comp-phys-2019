#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <numeric> // std::iota

#include "utils.h"
#include "gnuplotwrapper.h"

static int N = 4;

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
    double a = 1, b = 2, delta = (b - a) / samples;
    std::ofstream out("interpolations.csv");
    for (int i = 0; i < samples; ++i) {
        double x = a + delta * i;
        out << std::setprecision(10) << x << ',' << LagrangePolynomial(x) - log(x) <<
                          ',' << NewtonPolynomial(x) - log(x) << std::endl;
    }
    out.close();

    std::ofstream out2("integral.csv");
    std::vector<int> ivec(40);
    std::iota(ivec.begin(), ivec.end(), 3);
    for (auto N : ivec) {
        ::N = N;
        out2 << std::setprecision(12) << utils::Integrate(1000, a, b, [](double x) {
            return std::abs(LagrangePolynomial(x) - log(x));
        }) << std::endl;
    }
    out2.close();
    
    
    Gnuplot plot;
    plot("  set datafile separator \",\"\n\
            set multiplot layout 2, 1 title \"Task5 solution\" font \",14\"\n\
            set grid\n\
            set title 'Newthon Method'\n\
            set xlabel 'x'\n\
            set ylabel 'f(x)'\n\
            plot 'interpolations.csv' u 1:2 w l title 'Lagrange',\
                'interpolations.csv' u 1:3 w l title 'Newton' \n\
            set logscale y\n\
            plot 'integral.csv' u ($0+3):1 w lp title 'Loss Function'\n\
            unset multiplot");


    std::cin.get();
    std::remove("integral.csv");
    std::remove("interpolations.csv");

    return 0;
}
