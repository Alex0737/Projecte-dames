#include "moviments.h"

Moviments::Moviments(const Posicio& posInicial, bool menjat, bool dama)
{
    m_nPosicionsValides = 1;
    m_posicions[0] = posInicial;
    if (menjat)
    {
        m_menjadesMaximes = 1;

    }
    if (dama)
    {
        m_menjadesDames = 1;
    }
    m_menjat = menjat;
}

//afegeix una posicio al moviment
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

int Moviments::getDamesMenjades() const
{
    return m_menjadesDames;
}

Posicio Moviments::getFitxaMatada(int j) const
{
    return m_posicionsMenjades[j];
}

Posicio Moviments::getPosicioIndex(int n) const
{
    if (n >= 0 && n < m_nPosicionsValides)
        return m_posicions[n];
    else
        return Posicio(-1, -1);
}

int Moviments::getNombre() const
{
    return m_nPosicionsValides;
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

Posicio Moviments::getUltimaPosicio() const
{
    return m_posicions[m_nPosicionsValides - 1];
}

bool Moviments::esUltimaPosicio(const Posicio& p) const
{
    return(p == m_posicions[m_nPosicionsValides - 1]);
}

//mira si una posicio esta en el moviment
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
        else
            i++;
    }

    return trobat;
}


//compara si dos moviments son iguals
bool Moviments::operator==(const Moviments& m) const
{
    bool res = true;
    if (!(m_nPosicionsValides == m.m_nPosicionsValides && m_menjadesMaximes == m.m_menjadesMaximes && m_menjadesDames == m.m_menjadesDames && m_menjat == m.m_menjat))
    {
        res = false;
    }
    int i = 0;
    int j = 0;
    bool trobat = false;
    while (i < m_nPosicionsValides && res)
    {
        if (!(m_posicions[i] == m.m_posicions[i]))
        {
            res = false;

        }
        else
            i++;
    }
    while (j < m_nPosicionsValides && res)
    {
        if (!(m_posicionsMenjades[j] == m.m_posicionsMenjades[j]))
        {
            res = false;
        }
        else
            j++;
    }
    return res;
}

void Moviments::afegirMort(const Posicio& p)
{
    m_posicionsMenjades[m_menjadesMaximes++] = p;
}