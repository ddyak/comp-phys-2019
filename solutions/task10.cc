#include <math.h>
#include <vector>
#include <iostream>

#include "gnuplotwrapper.h"

const int N = 5;
double x1 = 0, x2 = M_PI;
double h = (x2 - x1) / (N + 1);

double f(double x) {
    return sin(x);
}

// Another yet method for Egor
// I used notation from the atricle below:
// http://window.edu.ru/resource/958/40958/files/dvgu079.pdf

double lambda1 = 0, lamda2 = 0,
        nu1 = 1, nu2 = M_PI + 1;

std::vector<double> TMDA(std::vector<double>& a, std::vector<double>& b, 
                                std::vector<double>& c, std::vector<double>& d) {
    std::vector<double> alpha(N + 1, lambda1), beta(N + 1, nu1);
    
    for (int i = 0; i < N; ++i)
        alpha[i + 1] = (c[i] / (-b[i] - alpha[i] * a[i]));

    for (int i = 0; i < N; ++i)
        beta[i + 1] = ((a[i] * beta[i] - d[i]) / ( -b[i] - alpha[i] * a[i]));

    std::vector<double> y(N + 1);
    y[N] = (nu2 + lamda2 * beta[N]) / (1 - alpha[N] * lamda2);
    for (int i = N - 1; i >= 0; --i)
        y[i] = alpha[i + 1] * y[i + 1] + beta[i + 1];
    return y;
}


int main() {
    //* Par. 1.6, Smirnov, OVF p. 2 */
    std::vector<double> a(N + 1, 1);
    std::vector<double> b(N + 1, -2); 
    std::vector<double> c(N + 1, 1);
    
    a[0] = 2;
    c[0] = 0;

    std::vector<double> x, d ;
    for (int i = 0; i < N + 1; ++i) {
        x.push_back(x1 + h * i);
        d.push_back(h * h * f(x[i]));
    }

    auto y = TMDA(a, b, c, d);        
                            
    std::vector<std::vector<double>> data;
    for (int i = 0; i < N; ++i)
        data.push_back({x[i], y[i]});
    Gnuplot plot;
    plot("plot '<cat' using 1:2 w l");
    plot.catData(data, 1);

    return 0;
}

