#include "fitxa.h"


void Fitxa::convertirDama()
{
    m_tipus = TIPUS_DAMA;
}

bool Fitxa::operator==(const Fitxa& f) const
{
    return (m_posicio == f.m_posicio && m_color == f.m_color && m_tipus == f.m_tipus);
}

void Fitxa::afegirMoviment(const Moviments& moviment)
{
    m_movimentsPossibles.afegirMoviment(moviment);
}

void Fitxa::netejaMoviments()
{
    m_movimentsPossibles.neteja();
}

void Fitxa::setPosicioBuida(const Posicio& p)
{
	m_tipus = TIPUS_EMPTY;
}

bool Fitxa::operator==(const Fitxa& f)
{
	return (m_posicio == f.m_posicio && m_color == f.m_color && m_tipus == f.m_tipus);
}
void Fitxa::setPosNova(const Posicio& pos, ColorFitxa c, TipusFitxa t)
{
	int x = pos.getX();
	int y = pos.getY();
	m_color = c;
	m_tipus = t;

}

string Fitxa::posicionsMoviment()
{
	string s;
	for (int i = 0; i < m_nPosicionsValides - 2; i++)
	{
		s += m_movimentsPossibles.getPosicioIndex(i).toString();
		s += " ,";
	}
	s += m_movimentsPossibles.getPosicioIndex(m_nPosicionsValides - 1).toString();
	return s;
}

Posicio Fitxa::movimentsValids(int n)
{
	m_movimentsPossibles.getPosicioIndex(n);
}
