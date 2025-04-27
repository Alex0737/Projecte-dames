
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

	void convertirDama();
	int getX() { m_posicio.getX(); }
	int getY() { m_posicio.getY(); }
	ColorFitxa getColor() const { return m_color; }
	TipusFitxa getTipus() const { return m_tipus; }
	Posicio getPosicio() const { return m_posicio; }

	void setColor(ColorFitxa c) { m_color = c; }
	void setTipus(TipusFitxa t) { m_tipus = t; }

	void setPosicioBuida(const Posicio& p);

	int getTipusFitxa();

	bool operator==(const Fitxa& f);
	void setPosNova(const Posicio& pos, ColorFitxa c, TipusFitxa t);

	void posicionsMoviment();

private:
	Posicio m_posicio;
	ColorFitxa m_color;
	Moviments m_movimentsPossibles; //array aqui? o dintre de moviments
	TipusFitxa m_tipus;

};
