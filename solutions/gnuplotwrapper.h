#pragma once

/** 
 * Usage:
 * 
 *  int main() {
 *      std::vector<std::vector<double>> vec = {{1,2}, {3,4}, {5,5}};
 *      Gnuplot plot;
 *      plot("plot '<cat' using 1:2");
 *      plot.catData(vec);
 *  }
*/

#include <iostream>
#include <vector>

#define GNUPLOT_NAME "gnuplot -persist"

class Gnuplot {
public:
    Gnuplot();
    ~Gnuplot();
    void operator()(const std::string & command);
    void catData(const std::vector<std::vector<double>>& data, size_t iter = 1);
private:
    FILE *pipe;
};

Gnuplot::Gnuplot() {
    pipe = popen(GNUPLOT_NAME, "w");
    if (!pipe) 
        std::cerr << "Gnuplot not found!" << std::endl;
}

Gnuplot::~Gnuplot() {
    fprintf(pipe, "exit\n");
    pclose(pipe);
}

void Gnuplot::operator()(const std::string & command) {
    fprintf(pipe, "%s\n", command.c_str());
    fflush(pipe);
}

void Gnuplot::catData(const std::vector<std::vector<double>>& data, size_t iter) {
    for (size_t i = 0; i < iter; ++i) {
        for (const auto& string : data) { 
            for (const auto& arg : string) 
                fprintf(pipe, "%.15f ", arg);
            fprintf(pipe, "\n");
        }
        fprintf(pipe, "%s\n", "e");
    }
}
