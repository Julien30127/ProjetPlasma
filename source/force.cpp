#include <fstream>
#include <vector>

#include "force.h"

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
            double qm = p.charge / p.masse;
            
            // Accélération de Lorentz (avec Bx = By = 0, Bz = cst)
            double ax = qm * (p.vy * Bz);
            double ay = qm * (-p.vx * Bz);

            p.vx += ax * dt;
            p.vy += ay * dt;
            p.x += p.vx * dt;
            p.y += p.vy * dt;
            p.z += p.vz * dt;
        }
        temps_total += dt;

        /*
        Note : Utilisation d'Euler semi-implicite, on fait l'hypothèse d'une accélération constante (pas la
        valeur absolue, mais plutôt la distribution sur les composantes en x et y) pendant dt.
        
        Conséquence : trajectoire rectiligne pendant dt, "fuite" de la particule.

        Pour la retarder, on peut imposer un dt très petit.

        L'éviter ? Voir "Algorithme de Boris".
        */
    }
    fichier.close();
    return temps_total;
}