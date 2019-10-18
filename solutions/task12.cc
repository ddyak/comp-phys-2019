#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "gnuplotwrapper.h"

constexpr int N = 200; // coordinate partition
double x1 = 0, x2 = 1;
double h = (x2 - x1) / N;

constexpr int T = 200; // time partition
constexpr double Time = 0.2;
double tau = Time / T;

double u0(double x) {
    return x * pow((1 - x), 2);
}

std::vector<std::vector<double>> u; // solution (heat map)

// init head map using boundary condition u(x, 0) = u0(x)
void init() { 
    std::vector<double> u_zero;
    for (int i = 0; i <= N; ++i) 
        u_zero.push_back(u0(i * h));
    u = std::vector<std::vector<double>>({u_zero});
}

double Lu(int j, int m) {
    return (u[m][j + 1] - 2 * u[m][j] + u[m][j - 1]) / pow(h, 2);
}

std::vector<double> TridiagonalMatrixAlgorithm(std::vector<double>& a, std::vector<double>& b, 
                                std::vector<double>& c, std::vector<double>& d) {
    int N = ::N - 2; // Boundary conditions u(0, t) = u(L, t) = 0
    std::vector<double> y(N);
    for (int i = 0; i < N; ++i) {
        double xi = a[i] / b[i - 1];
        a[i] = 0;                                   
        b[i] -= xi * c[i - 1];                      
        d[i] -= xi * d[i - 1];                      
    }
    y[N - 1] = d[N - 1] / b[N - 1];                 
    for (int i = N - 2; i >= 0; --i)                
        y[i] = 1 / b[i] * (d[i] - c[i] * y[i + 1]);
    return y;
}

int main() {
    //* Par. 3.4, Smirnov, OVF p. 2 */
    init();
    for (int m = 0; m < T; ++m) {
        std::vector<double> a(N - 1, -0.5 * tau / pow(h, 2));
        a[0] = 0;
        std::vector<double> b(N - 1, 1 + tau / pow(h, 2));
        std::vector<double> c(N - 1, -0.5 * tau / pow(h, 2));
        c[N - 2] = 0;    
        std::vector<double> d;
        for (int j = 1; j < N; ++j)
            d.push_back(u.back()[j] + tau / 2 * Lu(j, m));
    
        std::vector<double> layer = TridiagonalMatrixAlgorithm(a, b, c, d);
        layer.insert(layer.begin(), 0); // Boundary conditions u(0, t) = u(L, t) = 0
        layer.push_back(0);             //

        u.push_back(layer);
    }

    std::string filename = "heat_map_data.txt";
    std::ofstream file(filename);

    for (int m = 0; m <= T; ++m) {
        for (int j = 0; j <= N; ++j) {
            file << u[m][j] << ' ';
        }
        file << std::endl;
    }

    Gnuplot plot;
    plot("set title 'Heat Map'\n\
          set xlabel 'X'\n\
          set ylabel 'Time'\n");
    plot("plot '" + filename + "' matrix with image");
    return 0;
}
