

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
	void inicialitza(const string& nomFitxer);
	void mostraTauler();

	void actualitzaMovimentsValids();

	void netejaMovimentsValids();

	void veureMovimentsFitxaNormal(const Fitxa& fitxa);
	void veureMovimentsFitxaDama(const Fitxa& fitxa);


	void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
	void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);
	void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES]);

	bool mouFitxa(const Posicio& origen, const Posicio& desti);

	bool operator==(const Tauler&);
	
	string toString() const;


private:
	int tauler[N_FILES][N_COLUMNES];
	Fitxa m_fitxes[N_FITXES];
	int m_nFitxesBlanques;
	int m_nFitxesNegres;
};