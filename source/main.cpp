#include <vector>
#include <random>

#include "force.h"

int main() {
    std::vector<Particule> liste;
    
    double q_proton = 1.6e-19;
    double m_proton = 1.67e-27;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> pos(-0.01, 0.01);
    std::uniform_real_distribution<double> vit(1e4, 5e4); // 10 à 50 km/s

    for (int i = 0; i < 6; ++i) {
        Particule p;
        p.x = pos(gen); p.y = pos(gen); p.z = 0;
        p.vx = vit(gen); p.vy = vit(gen); p.vz = vit(gen) / 10.0;
        p.charge = q_proton;
        p.masse = m_proton;
        liste.push_back(p);
    }

    force(liste, 1e-11); 
    
    return 0;
}