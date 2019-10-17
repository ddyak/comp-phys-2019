#include <iostream>
#include <vector>

// SGD, Nesterov Accelerated Gradient
// http://proceedings.mlr.press/v28/sutskever13.pdf
// https://habr.com/ru/post/318970/

double f(const std::vector<double>& args) {
    return args[0]*args[0] + (args[1] - 1) * (args[1] - 1);
}

const double lr = 0.1;
const double gamma = 0.1;
const double delta = 1e-5;

std::vector<double> gradient(double (*f)(const std::vector<double>&), 
                             const std::vector<double>& point) {
    std::vector<double> grad;
    for (int i = 0; i < point.size(); ++i) {
        std::vector<double> point2 = point;
        std::vector<double> point3 = point;
        point2[i] += delta;
        point3[i] -= delta;
        grad.push_back((f(point2) - f(point3)) / (2 * delta));
    }
    return grad;
}

// std::vector<double> gradient_descent() {
//     std::vector<double> current = {1., 3};
//     std::vector<double> prev(current.size(), 0);
//     for (int iter = 0; iter < 20; ++iter) {
//         std::vector<double> res = gradient(f, current);
//         for (int i = 0; i < res.size(); ++i) {
//             current[i] -= lr * res[i];
//         }
//         std::cout << current[0] << ' ' << current[1] << std::endl;
//     }
// }



int main() {
    std::vector<double> current = {1., 3};
    std::vector<double> prev(current.size(), 0);
    for (int iter = 0; iter < 20; ++iter) {
        std::vector<double> res = gradient(f, current);
        for (int i = 0; i < res.size(); ++i)
            current[i] -= (lr * res[i] + gamma * prev[i]);
        prev = res;
        std::cout << current[0] << ' ' << current[1] << std::endl;
    }
    return 0;
}