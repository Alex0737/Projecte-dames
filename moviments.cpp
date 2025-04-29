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
