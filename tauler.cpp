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

string Tauler::toString() const
{
	string s;	
	for (int i = 0; i < 8; i++)
	{
		int t = 8 - i;
		s += "t:";
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
		}
		s += "/n";
	}
	s += " abcdefgh";
	
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) 
{
	int origenX = origen.getX();
	int origenY = origen.getY();

	if (getTipusFitxa(origenX - 1, origenY + 1) == TIPUS_EMPTY)
	{
		posicionsPossibles[nPosicions++] = Posicio(origenX - 1, origenY + 1);
	}
	else
	{
		if (getColorFitxa(origenX - 1, origenY + 1) != getColorFitxa(origenX, origenY))
		{
			
		} 
	}

	if (getTipusFitxa(origenX + 1, origenY + 1) == TIPUS_EMPTY)
	{
		posicionsPossibles[nPosicions++] = Posicio(origenX + 1, origenY + 1);

	}
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

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	int origenX = origen.getX();
	int origenY = origen.getY();
	TipusFitxa t = m_tauler[origenX - 1][origenY - 1].getTipus();
	ColorFitxa c = m_tauler[origenX - 1][origenY - 1].getColor();

	bool res = false;
	if (m_tauler[desti.getX() - 1][desti.getY() - 1].getTipus() == TIPUS_EMPTY)
	{
		m_tauler[origenX - 1][origenY - 1].setPosicioBuida(origen);


		if ()//eliminar las que es mengen
		{

		}
		if (desti.getY() == 7)
		{
			t = TIPUS_DAMA;
		}
		if ()//no menja))
		{
			//bufar la fitxa

		}
		m_tauler[desti.getX() - 1][desti.getY() - 1].setPosNova(desti, c, t);

	}

	return res;
}
void Tauler::setPosBuida(const Posicio& pos)
{
	int x = pos.getX();
	int y = pos.getY();
	m_tauler[x - 1][y - 1].setTipus(TIPUS_EMPTY);
}

void Tauler::actualitzaMovimentsValids()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_tauler[i][j].posicionsMoviment()
		}
	}
}
