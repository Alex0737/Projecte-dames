#include "posicio.hpp"

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
	while (i < nPosicions && trobat)
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

void escriuFitxa(const string& nomFitxer, char tipusFitxa, const Posicio& posicio)
{
	ofstream fitxer(nomFitxer);
	fitxer << tipusFitxa << ' ' << posicio.toString();
	fitxer.close();
}

bool Posicio::estaDesti(const Fitxa& f)const
{
	int i = 0;
	int j = 0;
	bool trobat = false;
	while (j < f.getNumMoviments() && !trobat)
	{
		while (i < f.getMoviment(j).getNombre() && !trobat)
		{
			if (m_x == f.getMoviment(j).getPosicioIndex(i).getX() && m_y == f.getMoviment(j).getPosicioIndex(i).getY())
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
