#include "moviments.h"

void Moviments::afegirPosicio(const Posicio& p)
{
    if (m_nMoviments < POSICIONS_MAXIMES)
    {
        m_posicions[m_nMoviments] = p;
        m_nMoviments++;
    }
}
void Moviments::neteja()
{
    m_nMoviments = 0;
}

Posicio Moviments::getPosicioIndex(int n)
{
    return m_movimentsValides[n];

}

bool Moviments::operator==(const Moviments& m) const
{
    bool igual = true;
    if (m_nMoviments != m.m_nMoviments)
    {
        igual = false;
    }
    else
    {
        for (int i = 0; i < m_nMoviments; ++i)
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


Posicio Moviments::getPosicioIndex(int n)
{
    return m_movimentsValides[n];

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
    if (m_nMoviments < POSICIONS_MAXIMES)
    {
        m_posicions[m_nMoviments] = p;
        m_nMoviments++;
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
    return (m_posicions[m_nPosicionsValides - 1]== p);
}



//Posicio getUltimaPosicio(const Posicio& posInicial) const {
//    if (nPosicions == 0) {
//        return posInicial; // Si no hay movimientos, devuelve la posición inicial
//    }
//    else {
//        return posicions[nPosicions - 1]; // Última posición registrada
//    }
//}
