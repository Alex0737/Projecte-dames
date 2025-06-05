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
	Joc() {};

	void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments);
	void actualitza(int mousePosX, int mousePosY, bool mouseStatus);  //se puede cambiar esto
	void finalitza();
	Posicio converteixAPosicio(int mouseX, int mouseY);


private:
	string m_nomArxiu;
	ColorFitxa m_guanyador;
	Tauler m_tauler;
	vector<CuaMoviments> m_cua;
	ModeJoc m_mode;
	int m_jugadorTorn;
	bool m_finalPartida;
	bool m_fitxaSeleccionada;
	Posicio m_posFitxaSeleccionada;
};

#endif 