#ifndef NODEMOVIMENT_H
#define NODEMOVIMENT_H

#include "tauler.hpp"

class NodeMoviment 
{
public:
    Moviments moviment;
    NodeMoviment* seguent;

    NodeMoviment(const Moviments& m) : moviment(m), seguent(nullptr) {}
};

#endif
