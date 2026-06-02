#ifndef KERNEL_H
#define KERNEL_H

double W_cubic(double r, double h);
void gradW_cubic(double dx, double dy, double dz, double r, double h, double& grad_x, double& grad_y, double& grad_z);

#endif