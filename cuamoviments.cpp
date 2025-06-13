#include "cuamoviments.h"
#include <string>
#include <fstream>

//EL BUENO


CuaMoviments::CuaMoviments()
{
    m_primer = nullptr;
    m_ultim = nullptr;
}

CuaMoviments::~CuaMoviments()
{
    while (m_primer != nullptr)
    {
        NodeMoviment* tmp = m_primer;
        m_primer = m_primer->getNext(); 
        delete tmp;
    }
    m_ultim = nullptr;
}

bool CuaMoviments::buida() const
{
    return (m_primer == nullptr);
}

void CuaMoviments::afegirMoviment(const Moviments& m)
{
    NodeMoviment* nou = new NodeMoviment(m);
    if (m_ultim == nullptr)
    {
        m_primer = nou;
        m_ultim = nou;
    }
    else
    {
        m_ultim->setNext(nou); 
        m_ultim = nou;
    }
}

Moviments CuaMoviments::treuPrimerMoviment()
{
    Moviments m;
    if (m_primer != nullptr)
    {
        m = m_primer->getValor();
        NodeMoviment* tmp = m_primer;
        m_primer = m_primer->getNext(); 
        if (m_primer == nullptr)
            m_ultim = nullptr;
        delete tmp;
    }
    return m;
}

Moviments CuaMoviments::treuPrimer()
{
    Moviments m;
    if (m_primer == nullptr)
        m = Moviments();
    else
        m = m_primer->getValor();
    return m; 
}

void CuaMoviments::guardarMoviments(const std::string& nomFitxer)
{
    ofstream fitxer(nomFitxer);
    if (fitxer.is_open())
    {
        NodeMoviment* actual = m_primer;
        while (actual != nullptr)
        {
            Moviments m = actual->getValor();
            if (m.getNombre() >= 2)
            {
                fitxer << m.getPosicioIndex(0).toString() << " " << m.getUltimaPosicio() << std::endl;
            }
            actual = actual->getNext(); 
        }
        fitxer.close();
    }
}

void CuaMoviments::carregaMoviments(const string& nomFitxer)
{
    ifstream fitxer(nomFitxer);
    if (fitxer.is_open()) {
        while (!buida())
        {
            treuPrimerMoviment();
        }
        string origen, desti;
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