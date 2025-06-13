#pragma once
#include "nodeMoviment.h"
#include "tauler.hpp"
#include <fstream>
#include <string>

class CuaMoviments
{
private:
    NodeMoviment* primer;
    NodeMoviment* ultim;

public:
    CuaMoviments();
    ~CuaMoviments();
    CuaMoviments(Fitxa f, Posicio p1, Posicio p2);
    Moviments treuPrimerMoviment();
    bool buida();
    void carregaMoviments(const std::string& nomFitxer);
    void guardarMoviments(const std::string& nom);
    void afegirMoviment(const Moviments& m);
    Moviments treuPrimer();
};
