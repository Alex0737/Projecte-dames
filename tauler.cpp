#include "tauler.h"

void Tauler::netejaTauler() 
{
	for (int i = 0; i < N_FILES; i++) 
	{
		for (int j = 0; j < N_COLUMNES; j++) 
		{
			m_tauler[i][j] = Fitxa();
		}
	}
}

void Tauler::inicialitza(const string& nomFitxer) 
{
	ifstream fitxer;
	fitxer.open(nomFitxer);

	if (fitxer.is_open()) 
	{
		char tipus;
		string posicioStr;

		fitxer >> tipus >> posicioStr;

		while (!fitxer.eof()) 
		{
			Posicio pos(posicioStr);
			int fila = pos.getX();
			int col = pos.getY();

			Fitxa novaFitxa = creaFitxa(tipus, pos);

			m_tauler[fila][col] = novaFitxa;

			fitxer >> tipus >> posicioStr;
		}

		fitxer.close();
	}
}

Fitxa Tauler::creaFitxa(char tipusChar, const Posicio& pos) 
{
	TipusFitxa tipus;
	ColorFitxa color;

	switch (tipusChar) 
	{
	case 'O':
		tipus = TIPUS_NORMAL;
		color = COLOR_BLANC;
		break;
	case 'X':
		tipus = TIPUS_NORMAL;
		color = COLOR_NEGRE;
		break;
	case 'D':
		tipus = TIPUS_DAMA;
		color = COLOR_BLANC;
		break;
	case 'R':
		tipus = TIPUS_DAMA;
		color = COLOR_NEGRE;
		break;
	default:
	}

	return Fitxa(tipus, color, pos);
}

void llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES])
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{

		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				tauler[i][j] = ' ';
			}
		}
		char tipusFitxa;
		Posicio posicio;
		while (fitxer >> tipusFitxa)
		{
			fitxer >> posicio;
			tauler[posicio.getX()][posicio.getY()] = tipusFitxa;
		}
		fitxer.close();

	}

}

void escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES])
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			if (tauler[i][j] != ' ')
			{
				Posicio posicio(i, j);
				fitxer << tauler[i][j] << ' ';
				fitxer << posicio << endl;
			}
		}
	}
	fitxer.close();

}

string Posicio::toString() const
{
	
}