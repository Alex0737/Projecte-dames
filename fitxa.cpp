#include "fitxa.h"

void Fitxa::afegirMoviment(const Moviments& m)
{
    m_moviments[m_nMoviments] = m;
    m_nMoviments++;
}

void Fitxa::setMoviment(const Moviments& m)
{
    m_moviments[m_nMoviments++] = m;
}

void Fitxa::convertirDama()
{
    m_tipus = TIPUS_DAMA;
}

void Fitxa::netejaMoviments()
{
    for (int i = 0; i < m_nMoviments; i++)
    {
        m_moviments[i].neteja();
    }
}

void Fitxa::setPosicioBuida()
{
    m_tipus = TIPUS_EMPTY;
}

bool Fitxa::operator==(const Fitxa& f) const
{
    return (m_posicio == f.getPosicio() && m_color == f.getColor() && m_tipus == f.getTipus());
}

void Fitxa::setPosNova(const Posicio& pos, ColorFitxa c, TipusFitxa t)
{
    int x = pos.getX();
    int y = pos.getY();
    m_posicio = pos;
    m_color = c;
    m_tipus = t;

}

int Fitxa::getMaxMenjades() const
{
    int max = 0;
    for (int i = 0; i < m_nMoviments; i++)
    {
        if (m_moviments[i].getMenjades() > max)
        {
            max = m_moviments[i].getMenjades();
        }
    }
    return max;
}

int Fitxa::getDamesMaximes() const
{
    int max = 0;
    for (int i = 0; i < m_nMoviments; i++)
    {
        if (m_moviments[i].getMenjades() > max)
        {
            max = m_moviments[i].getDamesMenjades();
        }
    }
    return max;
}

bool Fitxa::calBufar(const Posicio& p, int i) const
{
    bool res = false;
    int x = p.getX();
    int y = p.getY();
    if (!getMoviment(i).estaFinal(p) || getMaxMenjades() < getMoviment(i).getMenjades() || (getMaxMenjades() == getMoviment(i).getMenjades() && getMoviment(i).getDamesMenjades() < getDamesMaximes()))
    {
        res = true;
    }

    return res;
}

//comproba si una posicio es un destí correcte
bool Fitxa::estaDesti(const Posicio& p)const
{
    int j = 0;
    bool trobat = false;
    while (j < m_nMoviments && !trobat)
    {
        int i = 0;
        while (i < getMoviment(j).getNombre() && !trobat)
        {
            if (p == getMoviment(j).getPosicioIndex(i))
            {
                trobat = true;
            }
            else
                i++;
        }
        j++;
    }
    return trobat;
}

// retorna el index del moviment en la que es troba la posició pasada per parametre
int Fitxa::getIndexMoviment(const Posicio& p)const
{
    int res = -1;
    int j = 0;
    bool trobat = false;
    while (j < m_nMoviments && !trobat)
    {
        int i = 0;
        while (i < getMoviment(j).getNombre() && !trobat)
        {
            if (p == getMoviment(j).getPosicioIndex(i))
            {
                trobat = true;
                res = j;
            }
            else
                i++;
        }
        j++;
    }
    return res;
}