#ifndef PHYSICS_H
#define PHYSICS_H

#include "sph.h"
#include "grid.h"

void compute_density_pressure(std::vector<Particle>& particles, Grid& grid, const Config& cfg);
void compute_forces_mhd(std::vector<Particle>& particles, Grid& grid, const Config& cfg);

#endif