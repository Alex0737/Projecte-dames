#include "fitxa.h"

int Fitxa::getTipusFitxa()
{
	if ()
}

void Fitxa::convertirDama()
{
	m_tipus = TIPUS_DAMA;
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
void Fitxa::posicionsMoviment()
{

}
