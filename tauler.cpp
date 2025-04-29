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
	
}


void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPos, Posicio posicions[])
{
	nPos = 0;
	Fitxa& fitxa = m_tauler[origen.getX()][origen.getY()];


	if (fitxa.getTipus() == TIPUS_EMPTY)
	{
		
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

void Tauler::getPosicionsPossibles2(const Posicio& origen, int& nPos, Posicio posicions[])
{
	nPos = 0;
	Fitxa& fitxa = m_tauler[origen.getX()][origen.getY()];

	if (fitxa.getTipus() != TIPUS_EMPTY)
	{
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
}
void Tauler::getPosicionsPossibles3(
	const Posicio& origen,
	int& nPos,
	Posicio        posicions[]
) const
{
	nPos = 0;

	// 1) Agafem una còpia de la fitxa al tauler
	int x = origen.getX();
	int y = origen.getY();
	Fitxa fitxa = m_tauler[x][y];

	// 2) Si està buida, res a fer
	if (fitxa.getTipus() == TIPUS_EMPTY)
		return;

	// 3) Calculem tots els moviments amb un nou mètode de Tauler
	//    que ja no requereix passar-li *this
	Moviment movs[MAX_MOVS_FITXA];
	int      nMovs = calcularMovimentsValidsDeFitxa(fitxa, movs);

	// 4) Extraiem la última posició de cada moviment
	for (int i = 0; i < nMovs; ++i)
	{
		int len = movs[i].getNombre();
		if (len > 0)
			posicions[nPos++] = movs[i].getPosicio(len - 1);
	}
}

void Tauler::getPosicionsPossibles4(const Posicio& origen, int& nPos, Posicio posicions[]) //como si no tuviesemos array de moviments
{
	nPos = 0;
	Fitxa fitxa = m_tauler[origen.getX()][origen.getY()];

	if (fitxa.getTipus() != TIPUS_EMPTY)
	{
		fitxa.netejaMoviments();
		fitxa.calcularMovimentsValids(*this);
	
		for (int i = 0; i < fitxa.getMoviments().getNPosicionsValides(); ++i)
		{
			for (int k = 0; k < fitxa.getMoviment(i).getNombre();)
			{
				posicions[nPos] = fitxa.getMoviment(i).getPosicioIndex(i);
				nPos++;
			}
			//Moviments mov = fitxa.getMoviment();
			//int numPosMoviment = mov.getNombre();
	
			//if (numPosMoviment > 0)
			//{
			//	posicions[nPos] = mov.getPosicio(numPosMoviment - 1);
			//	nPos++;
			//}
		}
	}
}
TipusFitxa Tauler::toTipus(char s)
{
	TipusFitxa t;

	switch (s)
	{
	case 'O':
		t = TIPUS_NORMAL;
	case 'X':
		t = TIPUS_NORMAL;
	case 'D':
		t = TIPUS_DAMA;
	case 'R':
		t = TIPUS_DAMA;
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
	case 'X':
		c = COLOR_NEGRE;
	case 'D':
		c = COLOR_BLANC;
	case 'R':
		c = COLOR_NEGRE;
	}
	return c;
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

	if ((fitxa.getColor() == COLOR_BLANC && desti.getX() == 0) || (fitxa.getColor() == COLOR_NEGRE && desti.getX() == N_FILES - 1))
	{
		fitxa.convertirDama();
	}

	fitxa.setPosicio(desti);
	m_tauler[desti.getX()][desti.getY()] = fitxa;

	return true;
}

void Tauler::actualitzaMovimentsValids()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			if (m_tauler[i][j].getTipus() != TIPUS_EMPTY)
				m_tauler[i][j].netejaMoviments();
				m_tauler[i][j].calcularMovimentsValids(*this);
		}
	}
}

bool Tauler::mouFitxa2(const Posicio& origen, const Posicio& desti)
{
	int origenX = origen.getX();
	int origenY = origen.getY();
	TipusFitxa t = m_tauler[origenX - 1][origenY - 1].getTipus();
	ColorFitxa c = m_tauler[origenX - 1][origenY - 1].getColor();
	bool trobat = false;
	bool res = false;
	int i = 0;
	while (i < m_tauler[origenX][origenY].getNPosicionsValides() && !trobat)
	{
		if (desti == m_tauler[origenX][origenY].getMovimentsPossibles().getPosicioIndex(i))
		{
			int min = 0;
			for (int k = 0; k < m_tauler[origenX][origenY].getMovimentsPossibles().getPosicioIndex(i); k++)
			{
					
			}
			m_tauler[origenX][origenY].getMovimentsPossibles().g
			trobat = true;
			m_tauler[origenX - 1][origenY - 1].setPosicioBuida(origen);
			//tenemos q buscar el numero maximo que se tendria q comer
			//si no lo come bufamos la ficha
			//

			if ()
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
	}

	return res;
}
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

