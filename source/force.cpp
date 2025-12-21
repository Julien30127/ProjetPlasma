#include <fstream>
#include <vector>

#include "force.h"

double deplacement(std::vector<Particule> &liste, double dt) {
    std::ofstream fichier("Positions.csv");
    double temps_total = 0.0;
    bool simulation_finie = false;

    fichier << "temps";
    for (size_t i = 0; i < liste.size(); ++i) {
        fichier << ",x" << i << ",y" << i;
    }
    fichier << "\n";

    while (!simulation_finie) {
        simulation_finie = true;
        fichier << temps_total;

        for (size_t i = 0; i < liste.size(); ++i) {
            if (liste[i].position_y > 0) {
                liste[i].vitesse += liste[i].acceleration * dt;
                liste[i].position_y += liste[i].vitesse * dt;
                simulation_finie = false;
            } else {
                liste[i].position_y = 0;
            }
            
            fichier << "," << liste[i].position_x << "," << liste[i].position_y;
        }
        fichier << "\n";
        temps_total += dt;
    }

    fichier.close();
    return temps_total;
}