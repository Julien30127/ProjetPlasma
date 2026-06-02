#ifndef SPH_H
#define SPH_H

#include <vector>

struct Particle {
    double x, y, z;
    double vx, vy, vz;
    double ax, ay, az;
    double mass;
    double rho;
    double p;
    double bx, by, bz;
    double dbx, dby, dbz;
};

struct Config {
    int num_particles;
    double h;
    double dt;
    double max_time;
    double rest_density;
    double B_k;
    double mu_0;
    double alpha_visc;
};

#endif