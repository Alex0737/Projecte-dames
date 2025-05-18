#include "posicio.h"
//constructor a partir d'un string per ex "c3"
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

//serveix per comprobar si la m_x i m_y estan dins de l'array de posicions
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

//ostream& operator<<(ostream& out, const Posicio& pos)
//{
//	out << pos.toString();
//	return out;
//}

ostream& operator<<(ostream& os, const Posicio& pos) {
	os << pos.toString();
	return os;
}