#include "cuamoviments.h"
#include <string>

CuaMoviments::CuaMoviments() : primer(nullptr), ultim(nullptr) {}

CuaMoviments::~CuaMoviments() 
{
    while (primer != nullptr) 
    {
        NodeMoviment* tmp = primer;
        primer = primer->seguent;
        delete tmp;
    }
    ultim = nullptr;
}

bool CuaMoviments::buida() 
{
    return primer == nullptr;
}

void CuaMoviments::afegirMoviment(const Moviments& m) 
{
    NodeMoviment* nou = new NodeMoviment(m);
    if (ultim == nullptr) 
    {
        primer = ultim = nou;
    }
    else 
    {
        ultim->seguent = nou;
        ultim = nou;
    }
}

Moviments CuaMoviments::treuPrimerMoviment()
{
    Moviments m;

    if (primer != nullptr)
    {
        m = primer->moviment;
        NodeMoviment* tmp = primer;
        primer = primer->seguent;

        if (primer == nullptr)
            ultim = nullptr;
        delete tmp;
    }
    return m;
}


Moviments CuaMoviments::treuPrimer() 
{
    if (primer == nullptr)
        return Moviments();
    return primer->moviment;
}

void CuaMoviments::guardarMoviments(const std::string& nomFitxer) 
{
    std::ofstream fitxer(nomFitxer);
    if (fitxer.is_open()) 
    {
        NodeMoviment* actual = primer;
        while (actual != nullptr) 
        {
            const Moviments& m = actual->moviment;
            if (m.getNombre() >= 2) 
            {
                fitxer << m.getPosicioIndex(0).toString() << " " << m.getUltimaPosicio() << std::endl;
            }
            actual = actual->seguent;
        }
        fitxer.close();
    }
}

void CuaMoviments::carregaMoviments(const std::string& nomFitxer) 
{
    std::ifstream fitxer(nomFitxer);
    if (fitxer.is_open()) {
        while (!buida()) 
        {
            treuPrimerMoviment();
        }
        std::string origen, desti;
        while (fitxer >> origen >> desti) 
        {
            Moviments m;
            m.afegirPosicio(Posicio(origen));
            m.afegirPosicio(Posicio(desti));
            afegirMoviment(m);
        }
        fitxer.close();
    }
}
