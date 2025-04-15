#include "posicio.h"

const int N_FILES = 8;

Posicio::Posicio(const string& posicio) 
{ 
	fromString(posicio); 
}


void Posicio::fromString(const string& pos)
{
	m_x = (N_FILES - 1) - (pos[1] - '1');
	m_y = pos[0] - 'a';

}
string Posicio::toString() const
{
	string pos = "a1";
	pos[0] = 'a' + m_x;
	pos[1] = '1' + (N_FILES - 1) - m_y;
	return pos;
}

ifstream& operator>>(ifstream& fitxer, Posicio& posicio)
{
	string pos;
	fitxer >> pos;
	posicio.fromString(pos);
	return fitxer;
}

ofstream& operator<<(ofstream& fitxer, const Posicio& posicio)
{
	fitxer << posicio.toString();
	return fitxer;
}

void llegeixFitxa(const string& nomFitxer, char& tipusFitxa, Posicio& posicio)
{
	ifstream fitxer(nomFitxer);
	fitxer >> tipusFitxa;
	fitxer >> posicio;
	fitxer.close();
}

void escriuFitxa(const string& nomFitxer, char tipusFitxa, const Posicio& posicio)
{
	ofstream fitxer(nomFitxer);
	fitxer << tipusFitxa << ' ' << posicio.toString();
	fitxer.close();
}

