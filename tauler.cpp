#include "tauler.hpp"

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

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	bool resultat = false;
	bool menjada = false;
	int xO = origen.getX();
	int yO = origen.getY();
	int xD = desti.getX();
	int yD = desti.getY();
	if (m_tauler[xD][yD].estaDesti(desti))
	{
		int i = m_tauler[xO][xO].getIndexMoviment(desti);
		for (int j = 0; i < m_tauler[xO][xO].getMoviment(i).getMenjades(); i++)
		{
			Posicio p = m_tauler[xO][xO].getMoviment(i).getFitxaMatada(j);
			int x = p.getX();
			int y = p.getY();
			m_tauler[x][y].setPosicioBuida();
		}
		m_tauler[xD][yD] = m_tauler[xO][yO];
		m_tauler[xO][yO].setPosicioBuida();
		if (m_tauler[xO][yO].calBufar(desti, i))
		{
			m_tauler[xD][xD].setPosicioBuida();
		}

	}
	else
		resultat = false;
	return resultat;
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
	Fitxa f = m_tauler[origen.getX()][origen.getY()];
	for (int i = 0; i < f.getNumMoviments(); i++)
	{
		for (int j = 0; j < f.getMoviment(i).getNombre(); j++)
		{
			if (!f.getMoviment(i).getPosicioIndex(j).estaDins(posicionsPossibles, nPosicions))
			{
				posicionsPossibles[nPosicions++] = f.getMoviment(i).getPosicioIndex(j);
			}
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
	netejaTauler();

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
	return s;
}



TipusFitxa Tauler::toTipus(char s)const
{
	TipusFitxa t;

	switch (s)
	{
	case 'O':
		t = TIPUS_NORMAL;
		break;
	case 'X':
		t = TIPUS_NORMAL;
		break;
	case 'D':
		t = TIPUS_DAMA;
		break;
	case 'R':
		t = TIPUS_DAMA;
		break;
	}
	return t;
}

ColorFitxa toColor(char s)
{
	ColorFitxa c;

	switch (s)
	{
	case 'O':
		c = COLOR_BLANC;
		break;
	case 'X':
		c = COLOR_NEGRE;
		break;
	case 'D':
		c = COLOR_BLANC;
		break;
	case 'R':
		c = COLOR_NEGRE;
		break;
	}
	return c;
}


void Tauler::actualitzaMovimentsValids()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_tauler[i][j].netejaMoviments();
			m_tauler[i][j].calcularMovimentsValids(*this);
		}
	}
}


TipusFitxa Tauler::getTipusFitxa(int x, int y)const
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

ColorFitxa Tauler::getColorFitxa(int x, int y) const
{
	ColorFitxa res;
	bool trobat = false;
	res = m_tauler[x][y].getColor();
	return res;
}

void Tauler::setPosBuida(const Posicio& pos)
{
	int x = pos.getX();
	int y = pos.getY();
	m_tauler[x - 1][y - 1].setTipus(TIPUS_EMPTY);
}

bool Tauler::dinsTauler(int x, int y) const
{
	return ((x < N_FILES) && (y < N_COLUMNES));
}