#pragma once
#include "nodeMoviment.h"
#include "tauler.hpp"
#include <fstream>
#include <string>

class CuaMoviments
{
private:
    NodeMoviment* m_primer;
    NodeMoviment* m_ultim;

public:
    CuaMoviments();
    ~CuaMoviments();
    Moviments treuPrimerMoviment();
    bool buida() const;
    void carregaMoviments(const string& nomFitxer);
    void guardarMoviments(const string& nom);
    void afegirMoviment(const Moviments& m);
    Moviments treuPrimer();
};