#include <math.h>

#include "particule.h"
#include "force.h"


int main ()
{
    Particule p1 = {100.0, 0, -9.81};
    dynamique(p1,0.1);
    return 0;
}