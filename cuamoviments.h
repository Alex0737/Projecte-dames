
#include "tauler.hpp"

class CuaMoviments
{
private:
	Fitxa m_fitxa;
	Posicio m_posicioInicial;
	Posicio m_posicioFinal;
public:
	CuaMoviments(Fitxa f, Posicio p1, Posicio p2) { m_fitxa = f; m_posicioInicial = p1;  m_posicioFinal = p2; }

};