#include <iostream>
#include <vector>

#include "gnuplotwrapper.h"

/** solution for system:
 *  u' = f(u, v)
 *  v' = g(u, v)
 *  
 *  see formula (99)
 */

double f(double u, double v) {return 998 * u + 1998 * v;}
double f_u() {return 998;}
double f_v() {return 1998;}


double g(double u, double v) {return -999 * u - 1999 * v;}
double g_u() {return -999;}
double g_v() {return -1999;}

double det(double h) {
    return (1 - h*f_u())*((1 - h*g_v()) - (h * f_v()) * (h * g_u()));
}

//@arg 4,5 useless in this case, becose funciton convergence in one step.
double u_n1_s1(double h, double u_n, double v_n, double u_n1_s = -1, double v_n1_s = -1) {
    u_n1_s = u_n;
    v_n1_s = v_n;
    return u_n1_s + 1 / det(h) * ((1 - h*g_v()) * (u_n - u_n1_s + h*f(u_n1_s, v_n1_s)) 
                                +  (h * f_v()) * (v_n - v_n1_s + h*g(u_n1_s, v_n1_s)));  
}

double v_n1_s1(double h, double u_n, double v_n, double u_n1_s = -1, double v_n1_s = -1) {
    u_n1_s = u_n;
    v_n1_s = v_n;
    return v_n1_s + 1 / det(h) * ( (h*g_u()) * (u_n - u_n1_s + h*f(u_n1_s, v_n1_s)) 
                                +  (1 - h * f_u()) * (v_n - v_n1_s + h*g(u_n1_s, v_n1_s)));  
}

/** I used Cauchy Problem: (x, v) = (1, 1) at t = 0. 
 *  Analytical solution:
 *      u(t) = 4exp(-t) - 3exp(-1000t) 
 *      v(t) = 3exp(-1000t) - 2exp(-t) 
 */

int main() {
    double h = 1e-5; // h < 1e-3
    double t = 0, u = 1, v = 1;
    std::vector<std::vector<double>> data;
    data.push_back({t, u, v}); 
    for (; t < 1; t += h) {
        u = data.back()[1];
        v = data.back()[2];
        data.push_back({t, u_n1_s1(h, u, v), v_n1_s1(h, u, v)});
    }
    Gnuplot plot;
    plot("set logscale y"); 
    plot("plot '-' using 1:(abs($2 - 4*exp(-$1) + 3*exp(-1000*$1)))  w l title 'err u(t)',\
                '' using 1:(abs($3 - 3*exp(-1000*$1) + 2*exp(-$1)))  w l title 'err v(t)'");
    plot.catData(data, 2);
    return 0;
}

// Что такое жесткие уравнения? complete
// Что такое неявное жесткое уравнение, схема, границы применимости? complete
