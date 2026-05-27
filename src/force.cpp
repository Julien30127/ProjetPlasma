#include <fstream>
#include <vector>

#include "Boris.h"

double force(std::vector<Particule> &liste, double dt) {
    std::ofstream fichier("Positions.csv");
    double temps_total = 0.0;
    double Bz = 2.0; // Champ magnétique (en Tesla). On l'oriente uniquement selon z pour l'instant.

    fichier << "temps";
    for(size_t i = 0; i < liste.size(); ++i) {
        fichier << ",x" << i << ",y" << i << ",z" << i;
    }
    fichier << "\n";

    for (int step = 0; step < 1000000; ++step) {
        if (step % 100 == 0) {                          // On enregistre tous les 100 pas (alléger le fichier)
            fichier << temps_total;
            for (auto &p : liste) {
                fichier << "," << p.x << "," << p.y << "," << p.z;
            }
            fichier << "\n";
        }

        for (auto &p : liste) {
            Boris(p, dt, 0.0, 0.0, 0.0, 0.0, 0.0, Bz);

            // Maj de la position (schéma Saute-Mouton)
            p.x += p.vx * dt;
            p.y += p.vy * dt;
            p.z += p.vz * dt;
        }
        temps_total += dt;
    }
    fichier.close();
    return temps_total;
}