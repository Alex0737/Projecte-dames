
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
	Fitxa(const TipusFitxa& tipus, const ColorFitxa& color, const Posicio& pos) { m_tipus = tipus;  m_posicio = pos; m_color = color; }

	void afegirMoviment();
	void netejaMoviments();

	void movimentsValids(const Tauler& t);
	void convertirDama();
	ColorFitxa getColor() const { return m_color; }
	TipusFitxa getTipus() const { return m_tipus; }
	Posicio getPosicio() const { return m_posicio; }

	bool operator==(const Fitxa& f);


private:
	Posicio m_posicio;
	ColorFitxa m_color;
	Moviments m_movimentsPossibles; //array aqui? o dintre de moviments
	TipusFitxa m_tipus;

};