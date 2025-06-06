
#include "moviments.h"

Moviments::Moviments(const Posicio& posInicial, bool menjat, bool dama) : m_menjadesMaximes(0), m_menjadesDames(0), m_menjat(menjat)
{
    m_posicions.push_back(posInicial);
    if (dama)
        m_menjadesDames = 1;
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
    if (j >= 0 && j < m_posicionsMenjades.size())
        return m_posicionsMenjades[j];
    else
        return Posicio(-1, -1);
}

Posicio Moviments::getPosicioIndex(int n) const
{
    if (n >= 0 && n < m_posicions.size())
        return m_posicions[n];
    else
        return Posicio(-1, -1);
}

void Moviments::afegirMoviment(const std::vector<Posicio>& p, int menjades)
{
    m_posicions = p;
    m_menjadesMaximes = menjades;
}

Posicio Moviments::getUltimaPosicio() const
{
    return m_posicions.empty() ? Posicio(-1, -1) : m_posicions.back();
}

bool Moviments::esUltimaPosicio(const Posicio& p) const
{
    return (!m_posicions.empty() && p == m_posicions.back());
}

bool Moviments::estaDesti(const Posicio& p) const
{
    for (const auto& pos : m_posicions)
    {
        if (p == pos)
            return true;
    }
    return false;
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
