#ifndef TAULER_H
#define TAULER_H

#include <string>
#include <fstream>
#include "posicio.h"
#include "fitxa.h"
using namespace std;

static const int N_FILES = 8;
static const int N_COLUMNES = 8;

class Tauler
{
public:
	Tauler() { netejaTauler(); }
	void netejaTauler();
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	string toString() const;
	Fitxa creaFitxa(char tipusChar, const Posicio& pos);
	//De aqui para arriba necesario para movimientos

	void mostraTauler();


	void netejaMovimentsValids();

	void veureMovimentsFitxaNormal(const Fitxa& fitxa);
	void veureMovimentsFitxaDama(const Fitxa& fitxa);

	TipusFitxa getTipusFitxa(int x, int y);
	ColorFitxa getColorFitxa(int x, int y);

	Posicio saltsFitxesEsquerra(int x, int y);

	void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);
	void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);

	void setPosBuida(const Posicio& pos);

private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif