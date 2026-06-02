#include "physics.h"
#include "kernel.h"
#include <cmath>

void compute_density_pressure(std::vector<Particle>& particles, Grid& grid, const Config& cfg) {
    for (size_t i = 0; i < particles.size(); ++i) {
        auto& pi = particles[i];
        pi.rho = 0.0;
        auto neighbors = grid.get_neighbors(pi.x, pi.y, pi.z);
        for (int j : neighbors) {
            auto& pj = particles[j];
            double dx = pi.x - pj.x;
            double dy = pi.y - pj.y;
            double dz = pi.z - pj.z;
            double r = std::sqrt(dx*dx + dy*dy + dz*dz);
            if (r < 2.0 * cfg.h) {
                pi.rho += pj.mass * W_cubic(r, cfg.h);
            }
        }
        if (pi.rho < 0.001) pi.rho = 0.001;
        pi.p = cfg.B_k * (std::pow(pi.rho / cfg.rest_density, 7.0) - 1.0);
        if (pi.p < 0.0) pi.p = 0.0;
    }
}

void compute_forces_mhd(std::vector<Particle>& particles, Grid& grid, const Config& cfg) {
    for (size_t i = 0; i < particles.size(); ++i) {
        auto& pi = particles[i];
        pi.ax = 0.0; pi.ay = 0.0; pi.az = 0.0;
        pi.dbx = 0.0; pi.dby = 0.0; pi.dbz = 0.0;
        auto neighbors = grid.get_neighbors(pi.x, pi.y, pi.z);
        for (int j : neighbors) {
            if (i == j) continue;
            auto& pj = particles[j];
            double dx = pi.x - pj.x;
            double dy = pi.y - pj.y;
            double dz = pi.z - pj.z;
            double r = std::sqrt(dx*dx + dy*dy + dz*dz);
            if (r < 2.0 * cfg.h && r > 0.0) {
                double gx, gy, gz;
                gradW_cubic(dx, dy, dz, r, cfg.h, gx, gy, gz);
                
                double pres_term = (pi.p / (pi.rho * pi.rho)) + (pj.p / (pj.rho * pj.rho));
                
                double vx_ab = pi.vx - pj.vx;
                double vy_ab = pi.vy - pj.vy;
                double vz_ab = pi.vz - pj.vz;
                double v_dot_r = vx_ab*dx + vy_ab*dy + vz_ab*dz;
                double visc_term = 0.0;
                if (v_dot_r < 0.0) {
                    double mu_ab = (cfg.h * v_dot_r) / (r*r + 0.01 * cfg.h * cfg.h);
                    double c_ab = 10.0; 
                    double rho_ab = 0.5 * (pi.rho + pj.rho);
                    visc_term = (-cfg.alpha_visc * c_ab * mu_ab) / rho_ab;
                }

                double p_tot = pres_term + visc_term;
                
                pi.ax -= pj.mass * p_tot * gx;
                pi.ay -= pj.mass * p_tot * gy;
                pi.az -= pj.mass * p_tot * gz;

                double mag_pres_i = (pi.bx*pi.bx + pi.by*pi.by + pi.bz*pi.bz) / (2.0 * cfg.mu_0);
                double mag_pres_j = (pj.bx*pj.bx + pj.by*pj.by + pj.bz*pj.bz) / (2.0 * cfg.mu_0);
                double m_pres_term = (mag_pres_i / (pi.rho * pi.rho)) + (mag_pres_j / (pj.rho * pj.rho));
                
                pi.ax -= pj.mass * m_pres_term * gx;
                pi.ay -= pj.mass * m_pres_term * gy;
                pi.az -= pj.mass * m_pres_term * gz;

                double t_xx_i = pi.bx * pi.bx / cfg.mu_0;
                double t_xy_i = pi.bx * pi.by / cfg.mu_0;
                double t_xz_i = pi.bx * pi.bz / cfg.mu_0;
                double t_xx_j = pj.bx * pj.bx / cfg.mu_0;
                double t_xy_j = pj.bx * pj.by / cfg.mu_0;
                double t_xz_j = pj.bx * pj.bz / cfg.mu_0;

                pi.ax += pj.mass * ((t_xx_i / (pi.rho*pi.rho) + t_xx_j / (pj.rho*pj.rho)) * gx + 
                                    (t_xy_i / (pi.rho*pi.rho) + t_xy_j / (pj.rho*pj.rho)) * gy + 
                                    (t_xz_i / (pi.rho*pi.rho) + t_xz_j / (pj.rho*pj.rho)) * gz);
                
                pi.dbx += (1.0 / pi.rho) * pj.mass * (vx_ab * (pi.bx * gx + pi.by * gy + pi.bz * gz) - pi.bx * (vx_ab * gx + vy_ab * gy + vz_ab * gz));
                pi.dby += (1.0 / pi.rho) * pj.mass * (vy_ab * (pi.bx * gx + pi.by * gy + pi.bz * gz) - pi.by * (vx_ab * gx + vy_ab * gy + vz_ab * gz));
                pi.dbz += (1.0 / pi.rho) * pj.mass * (vz_ab * (pi.bx * gx + pi.by * gy + pi.bz * gz) - pi.bz * (vx_ab * gx + vy_ab * gy + vz_ab * gz));
            }
        }
    }
}