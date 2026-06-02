#include "sph.h"
#include "grid.h"
#include "physics.h"
#include <iostream>
#include <fstream>

int main() {
    Config cfg;
    cfg.num_particles = 1000;
    cfg.h = 0.12;
    cfg.dt = 0.001;
    cfg.max_time = 0.1;
    cfg.rest_density = 1000.0;
    cfg.B_k = 10000.0;
    cfg.mu_0 = 1.0;
    cfg.alpha_visc = 0.1;

    std::vector<Particle> particles;
    double spacing = 0.1;
    for(int x = 0; x < 10; ++x) {
        for(int y = 0; y < 10; ++y) {
            for(int z = 0; z < 10; ++z) {
                Particle p = {};
                p.x = x * spacing;
                p.y = y * spacing;
                p.z = z * spacing;
                p.mass = cfg.rest_density * (spacing * spacing * spacing);
                p.bx = 0.0; p.by = 0.0; p.bz = 1.0;
                particles.push_back(p);
            }
        }
    }

    std::ofstream file("mhd_sph_output.csv");
    file << "t,id,x,y,z,rho,bx,by,bz\n";

    Grid grid(2.0 * cfg.h);

    double t = 0.0;
    int step = 0;
    while (t < cfg.max_time) {
        grid.build(particles);
        compute_density_pressure(particles, grid, cfg);
        compute_forces_mhd(particles, grid, cfg);

        for (size_t i = 0; i < particles.size(); ++i) {
            auto& p = particles[i];
            p.vx += p.ax * cfg.dt;
            p.vy += p.ay * cfg.dt;
            p.vz += p.az * cfg.dt;
            p.x += p.vx * cfg.dt;
            p.y += p.vy * cfg.dt;
            p.z += p.vz * cfg.dt;

            p.bx += p.dbx * cfg.dt;
            p.by += p.dby * cfg.dt;
            p.bz += p.dbz * cfg.dt;

            if (step % 10 == 0) {
                file << t << "," << i << "," << p.x << "," << p.y << "," << p.z << "," << p.rho << "," << p.bx << "," << p.by << "," << p.bz << "\n";
            }
        }

        t += cfg.dt;
        step++;
        if (step % 10 == 0) std::cout << "Time: " << t << std::endl;
    }

    file.close();
    return 0;
}