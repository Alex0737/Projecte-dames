#include "moviments.h"

void Moviments::afegirPosicio(const Posicio& p)
{
    if (m_nPosicionsValides < POSICIONS_MAXIMES)
    {
        m_posicions[m_nPosicionsValides] = p;
        m_nPosicionsValides++;
    }
}
void Moviments::neteja()
{
    m_nPosicionsValides = 0;

}

Posicio Moviments::getPosicioIndex(int n) const
{
    return m_posicions[n];

}

bool Moviments::operator==(const Moviments& m) const
{
    bool igual = true;
    if (m_nPosicionsValides != m.m_nPosicionsValides)
    {
        igual = false;
    }
    else
    {
        for (int i = 0; i < m_nPosicionsValides; ++i)
        {
            if (!(m_posicions[i] == m.m_posicions[i]))
            {
                igual = false;
                break;
            }
        }
    }
    return igual;
}



void Moviments::afegirMoviment(Posicio p[], int nPosicions, int menjades)
{
    m_nPosicionsValides = nPosicions;
    for (int i = 0; i < nPosicions; i++)
    {
        m_posicions[i] = p[i];
    }
    m_menjadesMaximes = menjades;
}




void Moviments::afegirPosicio(const Posicio& p)
{
    if (m_nPosicionsValides < POSICIONS_MAXIMES)
    {
        m_posicions[m_nPosicionsValides] = p;
        m_nPosicionsValides++;
    }
}

Posicio Moviments::getUltimaPosicio()
{
    return m_posicions[m_nPosicionsValides - 1];
}

bool Moviments::esUltimaPosicio(const Posicio& p) const
{
    return(p == m_posicions[m_nPosicionsValides - 1]);
}

bool Moviments::estaDesti(const Posicio& p)const
{
    int i = 0;
    bool trobat = false;
    while (i < m_nPosicionsValides && !trobat)
    {
        if (p == m_posicions[i])
        {
            trobat = true;
        }
    }

    return trobat;
}

Posicio Moviments::getFitxaMatada(int j) const
{
    return m_posicionsMenjades[j];
}

bool Moviments::estaFinal(const Posicio& p) const
{
    return (m_posicions[m_nPosicionsValides - 1] == p);
}

bool Moviments::operator==(const Moviments& m) const
{
    bool res = true;
    if (!(m_nPosicionsValides == m.m_nPosicionsValides && m_menjadesMaximes == m.m_menjadesMaximes && m_menjadesDames == m.m_menjadesDames && m_menjat == m.m_menjat))
    {
        res = false;
    }
    int i = 0;
    bool trobat = false;
    while (i < m_nPosicionsValides && res)
    {
        if (!(m_posicions[i] == m.m_posicions[i]))
        {
            res = false;

        }
    }
    while (i < m_nPosicionsValides && res)
    {
        if (!(m_posicionsMenjades[i] == m.m_posicionsMenjades[i]))
        {
            res = false;
        }
    }
}
