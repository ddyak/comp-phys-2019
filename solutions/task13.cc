#include <iostream>
#include <math.h>
#include <complex>
#include <vector>
const std::complex<double> imaginary(0, 1); // C++ ¯\_(ツ)_/¯ 

#include "gnuplotwrapper.h"

const int N = 100;
double t1 = -M_PI, t2 = M_PI;

double a0 = 1, a1 = 0.02;
double w0 = 5.1, w1 = 5 * w0;

inline double f(double t) { return a0 * sin(w0 * t) + a1 * sin(w1 * t); }

inline double HannWindow(int k) { return 0.5 * (1 - cos(2 * M_PI * k / N)); }

inline double RectangleWindow(int k) { return ((k >= 0) && (k < N)) ? 1 : 0; }

inline double t(int k) { return k * (t2 - t1) / N; }

std::vector<std::vector<double>> DFT(double (*window) (int)) {
    std::vector<std::vector<double>> spectrum; // pair (w, |F+[f]|)
    for (int j = 0; j < N; ++j) {
        std::complex<double> ftr(0, 0);
        for (int k = 0; k < N; ++k)
            ftr += f(t(k)) * exp(2 * M_PI * imaginary * (j * k * 1. / N)) * window(j);

        spectrum.push_back({2 * M_PI * j / (t2 - t1), abs(ftr)});
    }
    return spectrum;
}

int main() {
    std::vector<std::vector<double>> function;
    for (int i = 0; i < N; ++i)
        function.push_back({t1 + t(i), f(t(i))});
    
    auto solutionRectangle = DFT(RectangleWindow);
    auto solutionHann = DFT(HannWindow);

    Gnuplot plot;
    plot("set multiplot title \"Task 13\" font \",14\"");
    plot("set size 1, 0.3");
    plot("set origin 0.0, 0.6");
    plot("plot '-' using 1:2 w l title 'Function'");
    plot.catData(function);
    plot("set size 1, 0.3");
    plot("set origin 0.0, 0.3");
    plot("plot '-' using 1:2 w l title 'Rectangle'");
    plot.catData(solutionRectangle);
    plot("set size 1, 0.3");
    plot("set origin 0.0, 0.0");
    plot("plot '-' using 1:2 w l title 'Hann'");
    plot.catData(solutionHann);
    plot("unset multiplot");

    return 0;
}
