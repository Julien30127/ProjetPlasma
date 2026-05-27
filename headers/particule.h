#ifndef PARTICULE_H
#define PARTICULE_H

#include <iostream>
#include <vector>

inline constexpr int NOMBRE_PROTONS = 100;

struct Particule {
    double x, y, z;       
    double vx, vy, vz;    
    double charge;        
    double masse;
};

#endif