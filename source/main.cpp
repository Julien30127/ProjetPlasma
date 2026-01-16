#include <math.h>
#include <random>

#include "particule.h"
#include "force.h"


int main() {
    int nbParticules = 100; 
    std::vector<Particule> liste;

    // Générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> disX(0.0, 100.0); 
    std::uniform_real_distribution<double> disY(50.0, 150.0); 

    for (int i = 0; i < nbParticules; ++i) {
        Particule p;
        p.position_x = disX(gen);
        p.position_y = disY(gen);
        p.vitesse = 0.0;        
        p.acceleration = -9.81; 
        
        liste.push_back(p);
    }

    deplacement(liste, 0.01);
    
    return 0;
}