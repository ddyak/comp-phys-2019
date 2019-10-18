#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>

#include "../gnuplotwrapper.h"

// SGD, Nesterov Accelerated Gradient
// http://proceedings.mlr.press/v28/sutskever13.pdf
// https://habr.com/ru/post/318970/


// https://en.wikipedia.org/wiki/Rosenbrock_function
// f(x,y) = (1-x^2) + 100 * (x - y^2)^2
// Has global min in (x, y) = (1,1), where f(x,y) = 0

double f(const std::vector<double>& args) { // notation for args as in PyROOT
    return pow(1 - args[0], 2) + 100 * pow(args[1] - pow(args[0], 2), 2);
}

const double lr = 0.0021;   // learning rate
const double mr = 0.9;      // memory rate
const double delta = 1e-8; 
const int MAX_ITERATION = 300;

std::vector<double> gradient(double (*f)(const std::vector<double>&), 
                             const std::vector<double>& point) {
    std::vector<double> grad;
    for (int i = 0; i < point.size(); ++i) {
        std::vector<double> point_dx = point;
        point_dx[i] += delta;
        grad.push_back((f(point_dx) - f(point)) / (delta));
    }
    return grad;
}

std::vector<std::vector<double>> GD(double (*f)(const std::vector<double>&),
                                     const std::vector<double>& initPoint) {
    std::vector<std::vector<double>> trace = { initPoint };
    std::vector<double> current = initPoint;

    for (int iter = 0; iter < MAX_ITERATION; ++iter) {
        std::vector<double> res = gradient(f, current);
        for (int i = 0; i < res.size(); ++i)
            current[i] -= lr * res[i];
        trace.push_back(current);
    }
    return trace;
}

std::vector<std::vector<double>> Nesterov_Momentum(double (*f)(const std::vector<double>&),
                                      const std::vector<double>& initPoint) {
    std::vector<std::vector<double>> trace = { initPoint };
    std::vector<double> current = initPoint;
    std::vector<double> momentum(current.size(), 0);
    std::vector<double> prevMomentum(current.size(), 0);

    for (int iter = 0; iter < MAX_ITERATION; ++iter) {
        std::vector<double> grad = gradient(f, current);
        for (int i = 0; i < grad.size(); ++i) {
            momentum[i] = mr * prevMomentum[i] - lr * grad[i];  
            current[i] += momentum[i];
        }
        prevMomentum = momentum;
        trace.push_back(current);
    }
    return trace;
}

int main() {
    std::vector<double> initPoint = {1.1, 0.9};
    const auto solutionGD = GD(f, initPoint);
    const auto solutionNM = Nesterov_Momentum(f, initPoint);
    
    Gnuplot plot;
    plot("set multiplot title \"GD vs NM on Reonbrock Function\" font \",14\"");
    plot("set size 0.6, 1");
    plot("set origin 0.0, 0.0");
    std::ifstream in("isolines.plot");
    std::string str((std::istreambuf_iterator<char>(in)),
                 std::istreambuf_iterator<char>());
    plot(str);
    
    plot("set size 0.4, 0.5");
    plot("set origin 0.6, 0.0");
    plot("set title 'GD'");
    plot("plot '-' using 1:2 title 'GD'");
    plot.catData(solutionGD);

    plot("set title 'NM'");
    plot("set size 0.4, 0.5");
    plot("set origin 0.6, 0.5");
    plot("plot '-' using 1:2 title 'NM'");
    plot.catData(solutionNM);

    plot("unset multiplot");
    return 0;
}
