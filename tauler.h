int const N_FITXES = 24;
#include <string>
#include <fstream>
#include "moviments.h"
#include "posicio.h"
#include "fitxa.h"
using namespace std;

class Tauler
{
public:
	Tauler() { netejaTauler(); }

	void inicialitza(const string& nomFitxer);
	void mostraTauler();

	void actualitzaMovimentsValids();

	void netejaMovimentsValids();

	void veureMovimentsFitxaNormal(const Fitxa& fitxa);
	void veureMovimentsFitxaDama(const Fitxa& fitxa);

	TipusFitxa getTipusFitxa(int x, int y);
	ColorFitxa getColorFitxa(int x, int y);

	Posicio saltsFitxesEsquerra(int x, int y);

	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);
	void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);

	bool mouFitxa(const Posicio& origen, const Posicio& desti);


	string toString() const;

	void setPosBuida(const Posicio& pos);

	void netejaTauler();
	Fitxa creaFitxa(char tipusChar, const Posicio& pos);

private:
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};
