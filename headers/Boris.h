#ifndef BORIS_H
#define BORIS_H

#include "force.h"

/**
 * @brief Met à jour le vecteur vitesse d'une particule selon l'algorithme de Boris (3D).
 * * @param p La particule à mettre à jour (passée par référence)
 * @param dt Le pas de temps
 * @param Ex, Ey, Ez Composantes du champ électrique au niveau de la particule
 * @param Bx, By, Bz Composantes du champ magnétique au niveau de la particule
 */

void Boris(Particule &p, 
                           double dt, 
                           double Ex, double Ey, double Ez, 
                           double Bx, double By, double Bz);

#endif // BORIS_H