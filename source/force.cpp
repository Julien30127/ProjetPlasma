#include <fstream>

#include "force.h"

double dynamique(Particule &p, double dt)
{
    std::ofstream fichier("Positions.csv");

    fichier << "temps,position" << std::endl;

    double temps_chute = 0.0;
    while (p.position_y > 0)
    {
        temps_chute += dt;
        p.vitesse += p.acceleration*dt;
        p.position_y += p.vitesse*dt;

        fichier << temps_chute << "," << p.position_y << std::endl;
    }
    return temps_chute;
}