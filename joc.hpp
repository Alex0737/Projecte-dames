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
	Joc() { iniciat = false; m_jugadorTorn = COLOR_BLANC; };

	void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments);
	bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
	void finalitza();
	Posicio converteixAPosicio(int mouseX, int mouseY);
	bool haAcabat();


private:
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
	int m_nPosicionsValides;
};

#endif 