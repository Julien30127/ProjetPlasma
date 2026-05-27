#include "Boris.h"

void Boris(Particule &p, 
                           double dt, 
                           double Ex, double Ey, double Ez, 
                           double Bx, double By, double Bz) 
{
    double qm = p.charge / p.masse;
    double dt_demi = dt * 0.5;

    // Demi-poussée électrique : v_moins = v(t - dt/2) + (q*E/m) * (dt/2)
    double v_moins_x = p.vx + qm * Ex * dt_demi;
    double v_moins_y = p.vy + qm * Ey * dt_demi;
    double v_moins_z = p.vz + qm * Ez * dt_demi;

    // Rotation magnétique (transformation de Cayley) : vecteur t = (q*B/m) * (dt/2)
    double tx = qm * Bx * dt_demi;
    double ty = qm * By * dt_demi;
    double tz = qm * Bz * dt_demi;

    double t_carre = tx*tx + ty*ty + tz*tz;

    // Vecteur d'échelle s = 2*t / (1 + |t|^2)
    double s_facteur = 2.0 / (1.0 + t_carre);
    double sx = tx * s_facteur;
    double sy = ty * s_facteur;
    double sz = tz * s_facteur;

    // v' = v_moins + v_moins x t (produit vect)
    double v_prime_x = v_moins_x + (v_moins_y * tz - v_moins_z * ty);
    double v_prime_y = v_moins_y + (v_moins_z * tx - v_moins_x * tz);
    double v_prime_z = v_moins_z + (v_moins_x * ty - v_moins_y * tx);

    // v_plus = v_moins + v' x s
    double v_plus_x = v_moins_x + (v_prime_y * sz - v_prime_z * sy);
    double v_plus_y = v_moins_y + (v_prime_z * sx - v_prime_x * sz);
    double v_plus_z = v_moins_z + (v_prime_x * sy - v_prime_y * sx);

    // Seconde demi-poussée électrique : v(t + dt/2) = v_plus + (q*E/m) * (dt/2)
    p.vx = v_plus_x + qm * Ex * dt_demi;
    p.vy = v_plus_y + qm * Ey * dt_demi;
    p.vz = v_plus_z + qm * Ez * dt_demi;
}