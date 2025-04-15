
#include <string.h>
#include "moviments.h"
#include "posicio.h"

using namespace std;

int const N_FILES = 8;
int const N_COLUMNES = 8;

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_DAMA,
	TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC,
} ColorFitxa;


class Fitxa
{
public:
	Fitxa() {}
	Fitxa(const string& color, const Posicio& pos) { m_posicio = pos; m_color = color; }

	void afegirMoviment();
	void netejaMoviments();

	void movimentsValids(const Tauler& t);
	void convertirDama();
	string getColor() const { return m_color; }
	bool operator==(const Fitxa& f);


private:
	Posicio m_posicio;
	string m_color;
	Moviments m_movimentsPossibles; //array aqui? o dintre de moviments
	TipusFitxa m_tipus;

};