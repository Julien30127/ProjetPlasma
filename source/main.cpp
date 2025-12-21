#include <math.h>

#include "particule.h"
#include "force.h"


int main ()
{
    std::vector<Particule> particules =
    {
        {0.0,100.0,0.0,-9.81},
        {1.0,100.0,0.0,-5.0},
        {2.0,100.0,0.0,-2.5}
    };
    
    deplacement(particules, 0.05);

    return 0;
}