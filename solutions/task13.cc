#include <iostream>
#include <math.h>

const double T = 2 * M_PI;
double a0 = 1, a1 = 0.002;
double w0 = 5.1, w1 = 5 * w0;

inline double f(double t) {
    return a0 * sin(w0 * t) + a1 * sin(w1 * t);
}


int main() {
    // Hanna's window
    // rectangle window
    return 0;
}