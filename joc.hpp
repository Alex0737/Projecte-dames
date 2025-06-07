#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "info_joc.hpp"
#include "tauler.hpp"
#include "cuamoviments.h"
using namespace std;


class Joc
{

public:
	Joc() : m_tauler(),m_cua(),m_mode(MODE_JOC_NONE),m_jugadorTorn(COLOR_BLANC),m_finalPartida(false),m_fitxaSeleccionada(false),m_posFitxaSeleccionada(-1, -1),m_nPosicionsValides(0),m_nomArxiuMoviments(""),
		iniciat(false), m_guanyador(COLOR_BLANC) { m_posicionsValides.clear(); };

	void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments);
	bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
	void finalitza();
	Posicio converteixAPosicio(int mouseX, int mouseY);
	bool haAcabat();
	bool getFinalPartida() { return m_finalPartida; }
	void setMode(const ModeJoc& mode) { m_mode = mode; }
	ColorFitxa getColorGuanyador() { return m_guanyador; }
	void guardaPartida(const string& nomFitxer);
private:
	std::vector<Posicio> m_posicionsValides;
	int m_nPosicionsValides;

	bool iniciat;
	string m_nomArxiuMoviments;
	string m_nomArxiuTauler;
	ColorFitxa m_guanyador;
	Tauler m_tauler;
	CuaMoviments m_cua;
	ModeJoc m_mode;
	ColorFitxa m_jugadorTorn;
	bool m_finalPartida;
	bool m_fitxaSeleccionada;
	Posicio m_posFitxaSeleccionada;
};

#endif 