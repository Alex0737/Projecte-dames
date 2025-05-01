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

	//fitxa.netejaMoviments();
	//fitxa.calcularMovimentsValids(*this);

	for (int i = 0; i < fitxa.getNumMoviments(); ++i)
	{
		Moviments mov = fitxa.getMoviment(i);
		int numPosMoviment = mov.getNombre();
		for (int i < mov.g)
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
	Fitxa fitxa = m_tauler[origen.getX()][origen.getY()];

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

void Tauler::getPosicionsPossibles5deepseek(const Posicio& origen, int& nPos, Posicio posicions[]) {
    nPos = 0;
    int procesat = 1;
    
    while (procesat) {
        Fitxa& f = m_tauler[origen.getX()][origen.getY()];
        if (f.getTipus() == TIPUS_EMPTY) procesat = 0;
        
        Moviments movs[MAX_MOVS_FITXA];
        int nMovs = f.getNumMoviments();
        int i = 0;
        
        while (i < nMovs && procesat) {
            Moviment mov = f.getMoviment(i);
            if (mov.getNombre() > 0) {
                posicions[nPos] = mov.getPosicio(mov.getNombre() - 1);
                nPos++;
            }
            i++;
        }
        procesat = 0;
    }
}

void Tauler::verificaCapturesObligatorias(ColorFitxa torn) 
{
    int maxMenjades = 0;
    bool hiHaCaptures = false;

    for (int i = 0; i < N_FILES; i++) 
	{
        for (int j = 0; j < N_COLUMNES; j++) 
		{
            Fitxa& f = m_tauler[i][j];
            if (f.getColor() == torn && f.getMaxMenjades() > maxMenjades) 
			{
                maxMenjades = f.getMaxMenjades();
                hiHaCaptures = true;
            }
        }
    }

    if (hiHaCaptures) 
	{
        for (int i = 0; i < N_FILES; i++) 
		{
            for (int j = 0; j < N_COLUMNES; j++) 
			{
                Fitxa& f = m_tauler[i][j];
                if (f.getColor() == torn) 
				{
                    for (int k = 0; k < f.getNumMoviments(); k++) 
					{
                        if (f.getMoviment(k).getMenjades() < maxMenjades) 
						{
                            f.eliminarMoviment(k);
                            k--;
                        }
                    }
                }
            }
        }
    }
}

void Tauler::bufarFitxa(ColorFitxa jugador) 
{
    int i = 0, j = 0;
    bool trobat = false;
    
    while (i < N_FILES && !trobat) 
	{
        j = 0;
        while (j < N_COLUMNES && !trobat) 
		{
            Fitxa& f = m_tauler[i][j];
            if (f.getColor() == jugador && f.getMaxMenjades() > 0) 
			{
                f.setTipus(TIPUS_EMPTY);
                trobat = true;
            }
            j++;
        }
        i++;
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

//mou fitxa definitivo por deepseek
bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) 
{
    bool resultat = false;
    bool movimentValid = false;
    bool menjada = false;
    int maxMenjades = 0;
    int nPosValides = 0;
    Posicio posicionsValides[64];
    ColorFitxa tornActual = m_tauler[origen.getX()][origen.getY()].getColor();

    // 1. Verificar captures obligatòries
    for (int i = 0; i < N_FILES; i++) 
	{
        for (int j = 0; j < N_COLUMNES; j++) 
		{
            Fitxa& f = m_tauler[i][j];
            if (f.getColor() == tornActual && f.getMaxMenjades() > maxMenjades)
			{
                maxMenjades = f.getMaxMenjades();
            }
        }
    }

    // 2. Obtenir moviments vàlids
    getPosicionsPossibles(origen, nPosValides, posicionsValides);

    // 3. Validar destí
    int i = 0;
    while (i < nPosValides && !movimentValid) 
	{
        if (posicionsValides[i] == desti) 
		{
            movimentValid = true;
            int menjadesAquestMoviment = 0;

            // 4. Trobar quantes menjades té el moviment
            Fitxa& f = m_tauler[origen.getX()][origen.getY()];
            int m = 0;
            while (m < f.getNumMoviments()) 
			{
                if (f.getMoviment(m).getUltimaPosicio() == desti) 
				{
                    menjadesAquestMoviment = f.getMoviment(m).getMenjades();
                    m = f.getNumMoviments();
                }
                m++;
            }

            // 5. Verificar si fa la captura màxima
            if (maxMenjades > 0) 
			{
                if (menjadesAquestMoviment < maxMenjades) 
				{
                    bufarFitxa(tornActual);
                    return resultat;
                }
                menjada = true;
            }
        }
        i++;
    }

    // 6. Si el moviment és vàlid
    if (movimentValid) 
	{
        // 7. Moure fitxa
        Fitxa fitxa = m_tauler[origen.getX()][origen.getY()];
        m_tauler[origen.getX()][origen.getY()] = Fitxa();

        // 8. Eliminar fitxes menjades
        if (menjada) 
		{
            int deltaX, deltaY;
            int difX = desti.getX() - origen.getX();
            int difY = desti.getY() - origen.getY();

            // Calcular direcció sense operador ternari
            if (difX > 0) deltaX = 1;
            else deltaX = -1;
            
            if (difY > 0) deltaY = 1;
            else deltaY = -1;

            int x = origen.getX();
            int y = origen.getY();
            
            while (x != desti.getX() && y != desti.getY())
			{
                x += deltaX;
                y += deltaY;
                if (m_tauler[x][y].getColor() != tornActual) 
				{
                    m_tauler[x][y] = Fitxa();
                }
            }
        }

        // 9. Posar fitxa a destí
        m_tauler[desti.getX()][desti.getY()] = fitxa;
        m_tauler[desti.getX()][desti.getY()].setPosicio(desti);

        // 10. Convertir a dama si cal
        if ((tornActual == COLOR_BLANC && desti.getX() == 0) || (tornActual == COLOR_NEGRE && desti.getX() == 7)) 
		{
            m_tauler[desti.getX()][desti.getY()].convertirDama();
        }

        // 11. Verificar salts addicionals per dames
        if (menjada && m_tauler[desti.getX()][desti.getY()].getTipus() == TIPUS_DAMA) 
		{
            actualitzaMovimentsValids();
            Posicio novesPosicions[64];
            int nNovesPos = 0;
            getPosicionsPossibles(desti, nNovesPos, novesPosicions);

            bool potSaltar = false;
            int j = 0;
            while (j < nNovesPos && !potSaltar) 
			{
                int dif = abs(novesPosicions[j].getX() - desti.getX());
                if (dif > 1) potSaltar = true;
                j++;
            }

            if (potSaltar) resultat = true; // Permetre nou moviment
        }

        resultat = true;
    } 
    else 
	{
        bufarFitxa(tornActual);
    }

    // 12. Actualitzar estats
    actualitzaMovimentsValids();
    return resultat;
}

bool Tauler::mouFitxa7(const Posicio& origen, const Posicio& desti) //bueno
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
		//si no esta la ultima de su moviment && si tiene menos comidas q el max && si tiene mismas modias i menos reinas
		if (m_tauler[xO][yO].calBufar(desti, i))
		{
			m_tauler[xD][xD].setPosicioBuida();
		}

	}
	else
		resultat = false;
}


bool resultat = false;
bool movimentValid = false;
bool menjada = false;
int maxMenjades = 0;
int nPosValides = 0;
Posicio posicionsValides[64];
ColorFitxa tornActual = m_tauler[origen.getX()][origen.getY()].getColor();

// 1. Verificar captures obligatòries
for (int i = 0; i < N_FILES; i++)
{
	for (int j = 0; j < N_COLUMNES; j++)
	{
		Fitxa& f = m_tauler[i][j];
		if (f.getColor() == tornActual && f.getMaxMenjades() > maxMenjades)
		{
			maxMenjades = f.getMaxMenjades();
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

	if ((fitxa.getColor() == COLOR_BLANC && desti.getX() == 0) || (fitxa.getColor() == COLOR_NEGRE && desti.getX() == N_FILES - 1))
	{
		fitxa.convertirDama();
	}

	fitxa.setPosicio(desti);
	m_tauler[desti.getX()][desti.getY()] = fitxa;

	//de aqui pa abajo gestio moviments multiples hecho por deep
	if (fitxa.getMenjades() > 0) 
	{
        Posicio novaPos = desti;
        bool potContinuar = true;
        
        while (potContinuar) {
            actualitzaMovimentsValids();
            int nPos;
            Posicio posicions[64];
            getPosicionsPossibles(novaPos, nPos, posicions);
            
            potContinuar = false;
            int i = 0;
            while (i < nPos && !potContinuar) {
                if (posicions[i].distancia(novaPos) > 1) {
                    mouFitxa(novaPos, posicions[i]);
                    novaPos = posicions[i];
                    potContinuar = true;
                }
                i++;
            }
        }
    }
	//hasta aqui
	return true;
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
