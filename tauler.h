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

	void verificaCapturesObligatorias(ColorFitxa torn);
    void bufarFitxa(ColorFitxa jugador);

	void mostraTauler();

	bool dinsTauler(int x, int y) const;
	bool dinsTauler(int x, int y) const;

	bool mouFitxa7(const Posicio& origen, const Posicio& desti);

	bool calBufar(const Posicio& p, int i)const;

	void netejaMovimentsValids();

	void veureMovimentsFitxaNormal(const Fitxa& fitxa);
	void veureMovimentsFitxaDama(const Fitxa& fitxa);

	TipusFitxa getTipusFitxa(int x, int y) const;
	ColorFitxa getColorFitxa(int x, int y) const;

	Posicio saltsFitxesEsquerra(int x, int y);

	void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);
	void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]) const;

	void setPosBuida(const Posicio& pos);
	Fitxa getFitxa(int x, int y) const { return m_tauler[x][y]; }

private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

#endif