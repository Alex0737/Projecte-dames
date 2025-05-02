#include "fitxa.h"

void Fitxa::calcularMovimentsValids(const Tauler& tauler)
{
    netejaMoviments();
    bool acabat = false;
    Moviments pendents[MAX_MOVS_FITXA];
    int inici = 0, final = 0;
    pendents[final++] = Moviments();

    int direccions[4][2];
    int nDireccions = 0;

    if (m_tipus == TIPUS_NORMAL)
    {
        nDireccions = 2;
        if (m_color == COLOR_BLANC)
        {
            direccions[0][0] = -1;
            direccions[0][1] = 1;
        }
        else
        {
            direccions[1][0] = -1;
            direccions[1][1] = -1;

        }
    }
    else
    {
        if (m_tipus == TIPUS_DAMA)
        {
            nDireccions = 4;
            direccions[0][0] = 1;
            direccions[0][1] = 1;
            direccions[1][0] = 1;
            direccions[1][1] = -1;
            direccions[2][0] = -1;
            direccions[2][1] = 1;
            direccions[3][0] = -1;
            direccions[3][1] = -1;
        }
    }


    while (inici < final && acabat)
    {
        Moviments actual = pendents[inici++];
        Posicio posActual = actual.getUltimaPosicio();
        int contadorDireccions = 0;
        while (contadorDireccions < nDireccions)
        {
            int dx = direccions[contadorDireccions][0];
            int dy = direccions[contadorDireccions][1];
            int x = posActual.getX();
            int y = posActual.getY();
            bool trobat = false;
            bool menjada = false;

            Moviments nouMov = actual;

            int iteracions = 0;
            int maxIter;
            if (m_tipus == TIPUS_DAMA)
            {
                maxIter = 7;
            }
            else
            {
                maxIter = 1;
            }

            while (iteracions < maxIter && !acabat)
            {
                x += dx;
                y += dy;
                iteracions++;

                if (tauler.dinsTauler(x, y))
                {
                    Fitxa casella = tauler.getFitxa(x, y);

                    if (casella.getTipus() == TIPUS_EMPTY && !menjada)
                    {
                        if (actual.getMenjades() == 0)
                        {
                            nouMov.afegirPosicio(Posicio(x, y));
                            afegirMoviment(nouMov);
                        }
                    }
                    else
                    {
                        if (casella.getColor() != m_color)
                        {
                            int xSalt = x + dx;
                            int ySalt = y + dy;
                            if (tauler.dinsTauler(xSalt, ySalt) && tauler.getFitxa(xSalt, ySalt).getTipus() == TIPUS_EMPTY)
                            {
                                nouMov.afegirPosicio(Posicio(xSalt, ySalt));
                                nouMov.incrementarMenjades();
                                if (tauler.getTipusFitxa(x, y) == TIPUS_DAMA)
                                {
                                    nouMov.incremetarMenjadesDames();
                                }
                                nouMov.setMenjat();
                                pendents[final++] = nouMov;
                                trobat = true;

                            }
                        }
                    }

                }
                else
                {
                    acabat = true;
                }
            }
            nDireccions++;
        }
    }
}

void Fitxa::afegirMoviment(const Moviments& m)
{
    m_moviments[m_nMoviments] = m;
    m_nMoviments++;
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

bool Fitxa::estaDesti(const Posicio& p)const
{
    int i = 0;
    int j = 0;
    bool trobat = false;
    while (j < m_nMoviments && trobat)
    {
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

int Fitxa::getIndexMoviment(const Posicio& p)const
{
    int i = 0;
    int res = -1;
    int j = 0;
    bool trobat = false;
    while (j < m_nMoviments && trobat)
    {
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
        if (!trobat)
            j++;
    }
    return res;
}
