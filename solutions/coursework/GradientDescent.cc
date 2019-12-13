#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>
#include <functional>

#include "../gnuplotwrapper.h"

// SGD, Nesterov Accelerated Gradient
// http://proceedings.mlr.press/v28/sutskever13.pdf
// https://habr.com/ru/post/318970/


// https://en.wikipedia.org/wiki/Rosenbrock_function
// f(x,y) = (1-x^2) + 100 * (x - y^2)^2
// Has global min in (x, y) = (1,1), where f(x,y) = 0

double Rosenbrock(const std::vector<double>& args) {
    return pow(1 - args[0], 2) + 100 * pow(args[1] - pow(args[0], 2), 2);
}

double Sphere(const std::vector<double>& args) {
    return pow(args[0], 2) + pow(args[1], 2);
}

double McCormick(const std::vector<double>& args) {
    return sin(args[0] + args[1]) + pow((args[0] - args[1]), 2) - 1.5 * args[0] + 2.5 * args[1] + 1;
}

const double lr = 0.0021;   // learning rate
const double mr = 0.9;      // memory rate
const double delta = 1e-8; 
int MAX_ITERATION = 300;

std::vector<double> gradient(std::function<double(const std::vector<double>&)> f, 
                             const std::vector<double>& point) {
    std::vector<double> grad;
    for (int i = 0; i < point.size(); ++i) {
        std::vector<double> point_dx = point;
        point_dx[i] += delta;
        grad.push_back((f(point_dx) - f(point)) / (delta));
    }
    return grad;
}

std::vector<std::vector<double>> GD(std::function<double(const std::vector<double>&)> f,
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

std::vector<std::vector<double>> Nesterov_Momentum(std::function<double(const std::vector<double>&)> f,
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

void saveSolution(const std::vector<std::vector<double>>& solution, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& sample : solution) {
        for (size_t i = 0; i < sample.size(); ++i) {
            file << sample[i] << ((i + 1 != sample.size()) ? "," : "");
        }
        file << std::endl;
    }
    file.close();
}

struct Sample {
    std::string name;
    std::function<double(const std::vector<double>&)> foo;
    std::vector<double> initPoint;
};
    
int main() {
    std::vector<double> initPoint = {1.1, 0.9};
    
    std::vector<Sample> functions = {{"Sphere", Sphere, {1.1, 0.9}},
                                     {"Rosenbrock", Rosenbrock, {1.1, 0.9}},
                                     {"McCormick", McCormick, {1.1, 0.9}}
                                     };

    MAX_ITERATION = 10000;

    for (auto& [name, foo, initPoint] : functions) {
        const auto solutionGD = GD(foo, initPoint);
        const auto solutionNM = Nesterov_Momentum(foo, initPoint);
        saveSolution(solutionNM, name + "_NM.csv");
        saveSolution(solutionGD, name + "_GD.csv");
    }
  
    return 0;
}
