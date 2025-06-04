#ifndef TAULER_H
#define TAULER_H

#include <string>
#include <fstream>
#include "fitxa.h"
#include "moviments.h"
#include "posicio.h"
using namespace std;

const int N_COLUMNES = 8;
const int MAX_ITERACIONS = 7;

class Tauler
{
public:
	Tauler();
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;

	void netejaTauler();
	Fitxa creaFitxa(char tipusChar, const Posicio& pos);


	bool dinsTauler(int x, int y) const;


	void calcularMovimentsValids(const Fitxa& fitxa);


	TipusFitxa getTipusFitxa(int x, int y) const;
	ColorFitxa getColorFitxa(int x, int y) const;

	TipusFitxa toTipus(char s)const;
	int getMaxDamesJugador(ColorFitxa color) const;
	int getMaxMenjadesJugador(ColorFitxa color) const;
	Posicio getFitxaBufar(ColorFitxa color) const;


	void setPosBuida(const Posicio& pos);
	Fitxa getFitxa(int x, int y) const { return m_tauler[x][y]; }

private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif