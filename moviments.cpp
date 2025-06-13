
#include "moviments.h"

Moviments::Moviments(const Posicio& posInicial, bool menjat, bool dama) : m_menjadesMaximes(0), m_menjadesDames(0), m_menjat(menjat)
{
    m_menjadesMaximes = 0;
    m_menjadesDames = 0;
    m_menjat = menjat;
    m_posicions.push_back(posInicial);

}

void Moviments::afegirPosicio(const Posicio& p)
{
    m_posicions.push_back(p);
}

void Moviments::neteja()
{
    m_posicions.clear();
    m_posicionsMenjades.clear();
    m_menjadesMaximes = 0;
    m_menjadesDames = 0;
    m_menjat = false;
}

int Moviments::getDamesMenjades() const
{
    return m_menjadesDames;
}

Posicio Moviments::getFitxaMatada(int j) const
{
    Posicio p;
    if (j >= 0 && j < m_posicionsMenjades.size())
        p = m_posicionsMenjades[j];
    else
        p = Posicio(-1, -1);
    return p;
}

Posicio Moviments::getPosicioIndex(int n) const
{
    Posicio p;
    if (n >= 0 && n < m_posicions.size())
        p = m_posicions[n];
    else
        p =  Posicio(-1, -1);
    return p;
}

void Moviments::afegirMoviment(const std::vector<Posicio>& p, int menjades)
{
    m_posicions = p;
    m_menjadesMaximes = menjades;
}

Posicio Moviments::getUltimaPosicio() const
{
    Posicio p;
    if (m_posicions.empty())
        p = Posicio(-1, -1);
    else
        p = m_posicions.back();
    return p;
}

bool Moviments::esUltimaPosicio(const Posicio& p) const
{
    return (!m_posicions.empty() && p == m_posicions.back());
}

bool Moviments::estaDesti(const Posicio& p) const
{
    int  i = 0;
    bool trobat = false;
    while (i < m_posicions.size() && !trobat)
    {
        Posicio pos = m_posicions[i];
        if (p == pos)
            trobat = true;
        i++;
    }
    return trobat;
}

bool Moviments::operator==(const Moviments& m) const
{
    return (m_posicions == m.m_posicions) &&
        (m_menjadesMaximes == m.m_menjadesMaximes) &&
        (m_menjadesDames == m.m_menjadesDames) &&
        (m_menjat == m.m_menjat) &&
        (m_posicionsMenjades == m.m_posicionsMenjades);
}

void Moviments::afegirMort(const Posicio& p)
{
    if (m_menjat == false)
        m_menjat = true;
    m_posicionsMenjades.push_back(p);
    m_menjadesMaximes = m_posicionsMenjades.size();
}

Moviments& Moviments::operator=(const Moviments& m)
{
    if (this != &m)
    {
        m_posicions = m.m_posicions;
        m_posicionsMenjades = m.m_posicionsMenjades;
        m_menjadesMaximes = m.m_menjadesMaximes;
        m_menjadesDames = m.m_menjadesDames;
        m_menjat = m.m_menjat;
    }
    return *this;
}