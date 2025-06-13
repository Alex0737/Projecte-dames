#include "posicio.h"

Posicio::Posicio(const string& pos)
{
	m_x = (N_FILES - 1) - (pos[1] - '1');
	m_y = pos[0] - 'a';
}

string Posicio::toString() const
{
	string pos = "a1";
	pos[0] = 'a' + m_y;
	pos[1] = '1' + (N_FILES - 1 - m_x);
	return pos;
}


bool Posicio::estaDins(const Posicio p[], int nPosicions) const
{
	int i = 0;
	bool trobat = false;
	while (i < nPosicions && !trobat)
	{
		if (p[i].getX() == m_x && p[i].getY() == m_y)
		{
			trobat = true;
		}
		else
			i++;
	}
	return trobat;
}

bool Posicio::operator==(const Posicio& pos) const
{
	return m_x == pos.m_x && m_y == pos.m_y;
}

ostream& operator<<(ostream& out, const Posicio& pos)
{
	out << pos.toString();
	return out;
}