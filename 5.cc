#include <iostream>
#include <math.h>
#include <vector>

static const int N = 4;

const auto x(int k) {
    return (1 + static_cast<double>(k) / N);
}

const auto y(int k) {
    return std::log(x(k));
}

static const auto X = [](int k) {
    return (M_PI * k) / (4. * N);
};

static const auto Y = [](int k) {
    return std::sin(X(k));
};

double l(int i, double x) {
    double l = 1.;
    for (int k = 0; k < N; ++k) {
        if (k != i) l *= (x - X(k));
    }
    return l;
}

double LagrangePolynomial(double x) {
    double P = 0.;
    for (int i = 0; i < N; ++i) {
        P += Y(i) * l(i, x) / l(i, X(i));
    }   
    return P;
}

int main() {
    double x = -1.;
    for (int i = 0; i < 2000; ++i) {
        std::cout << x << ',' << LagrangePolynomial(x) - std::sin(x) << std::endl;
        x += 1e-3;
    }
    return 0;
}
