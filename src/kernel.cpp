#include "kernel.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double W_cubic(double r, double h) {
    double q = r / h;
    double sigma = 1.0 / (M_PI * h * h * h);
    if (q >= 2.0) return 0.0;
    if (q >= 1.0) return sigma * 0.25 * std::pow(2.0 - q, 3);
    return sigma * (1.0 - 1.5 * q * q + 0.75 * q * q * q);
}

void gradW_cubic(double dx, double dy, double dz, double r, double h, double& grad_x, double& grad_y, double& grad_z) {
    if (r == 0.0 || r >= 2.0 * h) {
        grad_x = grad_y = grad_z = 0.0;
        return;
    }
    double q = r / h;
    double sigma = 1.0 / (M_PI * h * h * h);
    double factor = 0.0;
    if (q >= 1.0) {
        factor = -sigma * 0.75 * std::pow(2.0 - q, 2) / (r * h);
    } else {
        factor = sigma * (-3.0 * q + 2.25 * q * q) / (r * h);
    }
    grad_x = factor * dx;
    grad_y = factor * dy;
    grad_z = factor * dz;
}