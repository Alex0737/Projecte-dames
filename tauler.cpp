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
		tipus = TIPUS_EMPTY;
		color = COLOR_BLANC;
		break;
	}

	return Fitxa(tipus, color, pos);
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

string Tauler::toString() const
{
	string s;	
	for (int i = 0; i < 8; i++)
	{
		int t = 8 - i;
		s += t;
		s += ": ";
		for (int j = 0; j < 8; j++)
		{
			if (m_tauler[i][j].getColor() == COLOR_BLANC && m_tauler[i][j].getTipus() == TIPUS_DAMA)
			{
				s += "D";
			}
			else
			{
				if (m_tauler[i][j].getTipus() == TIPUS_EMPTY)
				{
					s += "_";
				}
				else
				{
					if (m_tauler[i][j].getColor() == COLOR_BLANC && m_tauler[i][j].getTipus() == TIPUS_NORMAL)
					{
						s += "O";
					}
					else
					{
						if (m_tauler[i][j].getColor() == COLOR_NEGRE && m_tauler[i][j].getTipus() == TIPUS_NORMAL)
						{
							s += "X";
						}
						else
						{
							if (m_tauler[i][j].getColor() == COLOR_NEGRE && m_tauler[i][j].getTipus() == TIPUS_DAMA)
							{
								s += "R";
							}
						}
					}
				}

			}
			s += " ";
		}
		s += "/n";
	}
	s += " a b c d e f g h";
	
}


void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPos, Posicio posicions[])
{
	nPos = 0;
	Fitxa& fitxa = m_tauler[origen.getX()][origen.getY()];

	if (fitxa.getTipus() == TIPUS_EMPTY)
	{
		return;
	}

	fitxa.netejaMoviments();
	fitxa.calcularMovimentsValids(*this);

	for (int i = 0; i < fitxa.getNumMoviments(); ++i)
	{
		Moviments mov = fitxa.getMoviment(i);
		int numPosMoviment = mov.getNombre();

		if (numPosMoviment > 0)
		{
			posicions[nPos] = mov.getPosicio(numPosMoviment - 1);
			nPos++;
		}
	}
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	int      nPos;
	Posicio  llista[64];
	bool     movValid;
	int      ind;

	getPosicionsPossibles(origen, nPos, llista);

	movValid = false;
	ind = 0;

	while (ind < nPos && !movValid)
	{
		if (llista[ind] == desti)
		{
			movValid = true;
		}

		ind++;
	}

	if (!movValid)
	{
		return false;
	}

	Fitxa fitxa = m_tauler[origen.getX()][origen.getY()];
	m_tauler[origen.getX()][origen.getY()] = Fitxa();

	if ((fitxa.getColor() == COLOR_BLANC
		&& desti.getX() == 0)
		|| (fitxa.getColor() == COLOR_NEGRE
			&& desti.getX() == N_FILES - 1))
	{
		fitxa.convertirDama();
	}

	fitxa.setPosicio(desti);
	m_tauler[desti.getX()][desti.getY()] = fitxa;

	return true;
}

void Tauler::actualitzaMovimentsValids()
{
	int numPosicionsValides;
	Posicio posicionsValidesPila[64];

	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int columna = 0; columna < N_COLUMNES; columna++)
		{
			getPosicionsPossibles(Posicio(fila, columna), numPosicionsValides, posicionsValidesPila);
		}
	}
}

//de aqui para arriba para los movimientos

void Tauler::llegeixTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES])
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

void Tauler::escriuTauler(const string& nomFitxer, char tauler[N_FILES][N_COLUMNES])
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

Posicio Tauler::saltsFitxesEsquerra(int x, int y)
{
	Posicio res;
	int origenX = x;
	int origenY = y;
	if (getTipusFitxa(origenX - 2, origenY + 2) == TIPUS_EMPTY)
		res = Posicio(origenX - 2, origenY + 2);

	return res;


}

TipusFitxa Tauler::getTipusFitxa(int x, int y)
{
	int i = 0;
	int j = 0;
	TipusFitxa res;
	bool trobat = false;
	while (i < 8 && !trobat)
	{
		while (j < 8 && !trobat)
		{
			if (m_tauler[i][j].getX() == x && m_tauler[i][j].getY() == y)
			{
				trobat = true;
				if (m_tauler[i][j].getTipus() == TIPUS_EMPTY)
					res = TIPUS_EMPTY;
				else
				{
					if (m_tauler[i][j].getTipus() == TIPUS_NORMAL)
					{
						res = TIPUS_NORMAL;
					}
					else
						res = TIPUS_DAMA;
				}
			}
		}
	}
	return res;
}

ColorFitxa Tauler::getColorFitxa(int x, int y)
{
	int i = 0;
	int j = 0;
	ColorFitxa res;
	bool trobat = false;
	while (i < 8 && !trobat)
	{
		while (j < 8 && !trobat)
		{
			if (m_tauler[i][j].getX() == x && m_tauler[i][j].getY() == y)
			{
				trobat = true;
				if (m_tauler[i][j].getColor() == COLOR_BLANC)
					res = COLOR_BLANC;
				else
				{
					res = COLOR_NEGRE;

				}
			}
		}
	}
	return res;
}

void Tauler::setPosBuida(const Posicio& pos)
{
	int x = pos.getX();
	int y = pos.getY();
	m_tauler[x - 1][y - 1].setTipus(TIPUS_EMPTY);
}

