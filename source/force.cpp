#include "force.h"

double dynamique(Particule &p, double dt)
{
    double temps_chute = 0.0;
    while (p.position_y > 0)
    {
        temps_chute += dt;
        p.vitesse += p.acceleration*dt;
        p.position_y += p.vitesse*dt;
    }
    return temps_chute;
}