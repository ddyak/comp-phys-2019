#include <functional>
#include <math.h>

namespace utils {

    double SimpsonRule(double left, double right, std::function<double(double)> f) {
        return (f(left) + 4 * f((left + right) / 2) + f(right)) / 6;
    }

    double Integrate(int N, double from, double to, std::function<double(double)> f) {
        double h = (to - from) / N;
        double left = from;
        double right = from + h;
        double sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += SimpsonRule(left, right, f);
            left += h;
            right += h;
        }
        return sum * h;
    }
}