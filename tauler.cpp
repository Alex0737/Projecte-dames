#include "tauler.hpp"

void Tauler::netejaTauler()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_tauler[i][j] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, Posicio(i, j));
		}
	}
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	bool resultat = false;
	int xO = origen.getX();
	int yO = origen.getY();
	int xD = desti.getX();
	int yD = desti.getY();

	if (dinsTauler(xO, yO) && dinsTauler(xD, yD) && m_tauler[xD][yD].estaDesti(desti))
	{
		int i = m_tauler[xO][yO].getIndexMoviment(desti);
		if (i != -1)
		{
			for (int j = 0; j < m_tauler[xO][yO].getMoviment(i).getMenjades() - 1; j++)
			{
				Posicio p = m_tauler[xO][yO].getMoviment(i).getFitxaMatada(j);
				int x = p.getX();
				int y = p.getY();
				if (dinsTauler(x, y))
					m_tauler[x][y].setPosicioBuida();
			}
			m_tauler[xD][yD] = m_tauler[xO][yO];
			m_tauler[xO][yO].setPosicioBuida();
			if (m_tauler[xD][yD].calBufar(desti, i))
				m_tauler[xD][yD].setPosicioBuida();
			resultat = true;
		}
	}
	return resultat;
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
	Fitxa f = m_tauler[origen.getX()][origen.getY()];
	for (int i = 0; i < f.getNumMoviments(); i++)
	{
		for (int j = 0; j < f.getMoviment(i).getNombre(); j++)
		{
			posicionsPossibles[nPosicions++] = f.getMoviment(i).getPosicioIndex(j);
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
		color = COLOR_EMPTY;
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


		while (fitxer >> tipus)
		{
			fitxer >> posicioStr;
			Posicio pos(posicioStr);
			int fila = pos.getX();
			int col = pos.getY();

			Fitxa novaFitxa = creaFitxa(tipus, pos);

			m_tauler[fila][col] = novaFitxa;

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
		s += to_string(t);
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
		s += "\n";
	}
	s += "   a b c d e f g h";
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
	default:
		t = TIPUS_EMPTY;
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
	default:
		c = COLOR_EMPTY;
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
			calcularMovimentsValids(m_tauler[i][j]);
		}
	}
}


TipusFitxa Tauler::getTipusFitxa(int x, int y)const
{
	if (x >= 0 && x < N_FILES && y >= 0 && y < N_COLUMNES)
		return m_tauler[x][y].getTipus();
	else
		return TIPUS_EMPTY;
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
	if (dinsTauler(x, y))
		m_tauler[x][y].setTipus(TIPUS_EMPTY);
}

bool Tauler::dinsTauler(int x, int y) const
{
	return ((x < N_FILES) && (y < N_COLUMNES) && x > 0 && y > 0);
}

void Tauler::calcularMovimentsValids(const Fitxa& fitxa) const
{
	int x = fitxa.getX();
	int y = fitxa.getY();
	bool acabat = false;
	Fitxa f = m_tauler[x][y];
	Moviments pendents[MAX_MOVS_FITXA];
	int inici = 0, final = 0;
	pendents[final++] = Moviments();

	int direccions[4][2];
	int nDireccions = 0;

	if (f.getTipus() == TIPUS_NORMAL)
	{
		nDireccions = 2;
		if (f.getColor() == COLOR_BLANC)
		{
			direccions[0][0] = -1;
			direccions[0][1] = -1;
			direccions[1][0] = -1;
			direccions[1][1] = 1;
		}
		else
		{
			direccions[0][0] = 1;
			direccions[0][1] = -1;
			direccions[1][0] = 1;
			direccions[1][1] = 1;
		}
	}
	else
	{
		if (f.getTipus() == TIPUS_DAMA)
		{
			nDireccions = 4;
			direccions[0][0] = 1;
			direccions[0][1] = 1;
			direccions[1][0] = 1;
			direccions[1][1] = -1;
			direccions[2][0] = -1;
			direccions[2][1] = 1;
			direccions[3][0] = -1;
			direccions[3][1] = -1;
		}
	}


	while (inici < final)
	{
		Moviments actual = pendents[inici++];
		Posicio  posActual = actual.getUltimaPosicio();
		int contadorDireccions = 0;
		while (contadorDireccions < nDireccions)
		{
			int dx = direccions[contadorDireccions][0];
			int dy = direccions[contadorDireccions][1];
			int x = posActual.getX();
			int y = posActual.getY();
			bool trobat = false;
			bool menjada = false;

			Moviments nouMov = actual;

			int iteracions = 0;
			int maxIter;
			if (f.getTipus() == TIPUS_DAMA)
			{
				maxIter = 7;
			}
			else
			{
				maxIter = 1;
			}

			while (iteracions < maxIter && !acabat)
			{
				x += dx;
				y += dy;
				iteracions++;

				if (dinsTauler(x, y))
				{
					Fitxa casella = getFitxa(x, y);

					if (casella.getTipus() == TIPUS_EMPTY && !menjada)
					{
						if (actual.getMenjades() == 0)
						{
							nouMov.afegirPosicio(Posicio(x, y));
							f.afegirMoviment(nouMov);
						}
					}
					else
					{
						if (casella.getColor() != f.getColor())
						{
							int xSalt = x + dx;
							int ySalt = y + dy;
							if (dinsTauler(xSalt, ySalt) && getFitxa(xSalt, ySalt).getTipus() == TIPUS_EMPTY)
							{
								nouMov.afegirPosicio(Posicio(xSalt, ySalt));
								nouMov.incrementarMenjades();
								if (getTipusFitxa(x, y) == TIPUS_DAMA)
								{
									nouMov.incrementarMenjadesDames();
								}
								nouMov.setMenjat();
								pendents[final++] = nouMov;
								trobat = true;

							}
						}
					}

				}

			}
			contadorDireccions++;
		}
	}
}