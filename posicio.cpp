#include "posicio.h"

const int N_FILES = 8;

string Posicio::toString() const
{
	string pos = "a1";
	pos[0] = 'a' + m_y;
	pos[1] = '1' + (N_FILES - 1 - m_x);
	return pos;
}

bool Posicio::operator==(const Posicio& pos) const
{
	return m_x == pos.m_x && m_y == pos.m_y;
}

ostream& operator<<(ostream& out, const Posicio& pos) {
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
	while (j < f.getNumMoviments() && trobat)
	{
		while (i < f.getMoviment(i).getNombre() && !trobat)
		{
			if (m_x == m_posicions[i])
			{
				trobat = true;
			}
		}
	}

	return trobat;
}

Posicio Fitxa::getFitxaMatada(int j) const
{
	m_posicionsMenjades
}