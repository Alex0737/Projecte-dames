#include "tauler.hpp"

Tauler::Tauler()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_tauler[i][j] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, Posicio(i, j));
		}
	}
}


void Tauler::netejaTauler()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_tauler[i][j] = Fitxa(TIPUS_EMPTY, COLOR_BLANC, Posicio(i, j));
			m_tauler[i][j].setMoviment(Moviments());
		}
	}
}

// la fitxa que es troba en origen a desti eliminant les fitxes menjades
bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	bool resultat = false;
	int xO = origen.getX();
	int yO = origen.getY();
	int xD = desti.getX();
	int yD = desti.getY();

	if (dinsTauler(xO, yO) && dinsTauler(xD, yD) && m_tauler[xO][yO].estaDesti(desti))
	{
		int i = m_tauler[xO][yO].getIndexMoviment(desti);
		if (i != -1)
		{
			// 1. Elimina las fichas comidas
			for (int j = 0; j < m_tauler[xO][yO].getMoviment(i).getMenjades(); j++)
			{
				Posicio p = m_tauler[xO][yO].getMoviment(i).getFitxaMatada(j);
				int x = p.getX();
				int y = p.getY();
				if (dinsTauler(x, y))
					m_tauler[x][y].setPosicioBuida();
			}
			// 2. Mueve la ficha a la posición destino
			m_tauler[xD][yD] = m_tauler[xO][yO];
			m_tauler[xO][yO].setPosicioBuida();
			// 3. Si toca, convierte en dama
			if (m_tauler[xD][yD].getTipus() == TIPUS_NORMAL)
			{
				if ((m_tauler[xD][yD].getColor() == COLOR_BLANC && xD == 0) ||
					(m_tauler[xD][yD].getColor() == COLOR_NEGRE && xD == N_FILES - 1))
				{
					m_tauler[xD][yD].convertirDama();
				}
			}

			// 4. Vacía la posición original

			// 5. Si hay que bufar la ficha (no ha hecho la captura máxima)
			if (m_tauler[xD][yD].calBufar(desti, i))
				m_tauler[xD][yD].setPosicioBuida();

			resultat = true;
		}
	}
	return resultat;
}
//afegeix totes les posicions posibles de la fitxa origen a l'array
void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
	nPosicions = 0; // Reiniciar contador
	Fitxa f = m_tauler[origen.getX()][origen.getY()];
	for (int i = 0; i < f.getNumMoviments(); i++)
	{
		Moviments mov = f.getMoviment(i);
		for (int j = 0; j < mov.getNombre(); j++)
		{
			if (nPosicions < 10)
			{
				Posicio pos = mov.getPosicioIndex(j);
				if (pos.getX() != -1 && pos.getY() != -1)
				{ // Filtrar inválidas
					int i = 0;
					bool trobat = false;
					while (i < nPosicions && !trobat)
					{
						if (posicionsPossibles[i] == pos)
							trobat = true;
						else
							i++;
					}
					if (!trobat)
						posicionsPossibles[nPosicions++] = pos;

				}
			}
		}
	}
}

// s'utilitza en inicialitza per transformar les O, X, D, R en fitxes
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

//a partir d'un archiu va creant afegint les fitxes al tauler
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

//representa el tauler
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
		c = COLOR_BLANC;
		break;
	}
	return c;
}

//actualitza els moviments valids de totes les fitxes
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

//l'ultilitzem en molts if per comprovar si la posicio està dins del tauler
bool Tauler::dinsTauler(int x, int y) const
{
	return (x >= 0 && x < N_FILES && y >= 0 && y < N_COLUMNES);
}

void Tauler::calcularMovimentsValids(const Fitxa& fitxa)
{
	int x = fitxa.getX();
	int y = fitxa.getY();
	Fitxa f = m_tauler[x][y];

	// Inicialización de estructuras
	int direccions[4][2];
	int nDireccions = 0;
	int MAX_PENDENTS = MAX_MOVS_FITXA * 4; // Por seguridad

	// Determinar dirección y tipo de movimientos según la ficha
	if (f.getTipus() == TIPUS_NORMAL)
	{
		nDireccions = 2;
		if (f.getColor() == COLOR_BLANC)
		{
			direccions[0][0] = -1; direccions[0][1] = -1;
			direccions[1][0] = -1; direccions[1][1] = 1;
		}
		else
		{
			direccions[0][0] = 1; direccions[0][1] = -1;
			direccions[1][0] = 1; direccions[1][1] = 1;
		}

		// --- MOVIMIENTOS SIMPLES ---
		for (int i = 0; i < nDireccions; i++)
		{
			int nx = x + direccions[i][0];
			int ny = y + direccions[i][1];
			if (dinsTauler(nx, ny) && m_tauler[nx][ny].getTipus() == TIPUS_EMPTY)
			{
				Posicio p(nx, ny);
				m_tauler[x][y].afegirMoviment(Moviments(p, false, false));
			}
		}

		// --- MOVIMIENTOS DE CAPTURA ---
		struct Pendent {
			Moviments mov;
		};
		Pendent pendents[100];
		int nPendents = 0;

		// Capturas iniciales
		for (int i = 0; i < nDireccions; i++)
		{
			int nx = x + direccions[i][0];
			int ny = y + direccions[i][1];
			int nx2 = x + 2 * direccions[i][0];
			int ny2 = y + 2 * direccions[i][1];
			if (
				dinsTauler(nx, ny) &&
				dinsTauler(nx2, ny2) &&
				m_tauler[nx][ny].getTipus() != TIPUS_EMPTY &&
				m_tauler[nx][ny].getColor() != f.getColor() &&
				m_tauler[nx2][ny2].getTipus() == TIPUS_EMPTY)
			{
				Moviments mov(Posicio(nx2, ny2), true, false);
				mov.afegirMort(Posicio(nx, ny));
				pendents[nPendents++].mov = mov;
			}
		}

		// Cadenas de saltos (multi-jump)
		int idx = 0;
		while (idx < nPendents)
		{
			Moviments actual = pendents[idx].mov;
			Posicio ultima = actual.getUltimaPosicio();
			int ux = ultima.getX();
			int uy = ultima.getY();
			bool found = false;

			for (int i = 0; i < nDireccions; i++)
			{
				int nx = ux + direccions[i][0];
				int ny = uy + direccions[i][1];
				int nx2 = ux + 2 * direccions[i][0];
				int ny2 = uy + 2 * direccions[i][1];
				// Si salto es posible y la ficha a saltar no está ya comida
				bool yaComida = false;
				for (int j = 0; j < actual.getMenjades(); j++)
				{
					if (Posicio(nx, ny) == actual.getFitxaMatada(j))
						yaComida = true;
				}
				if (
					dinsTauler(nx, ny) &&
					dinsTauler(nx2, ny2) &&
					m_tauler[nx][ny].getTipus() != TIPUS_EMPTY &&
					m_tauler[nx][ny].getColor() != f.getColor() &&
					m_tauler[nx2][ny2].getTipus() == TIPUS_EMPTY &&
					!yaComida)
				{
					Moviments nouMov = actual;
					nouMov.afegirPosicio(Posicio(nx2, ny2));
					nouMov.afegirMort(Posicio(nx, ny));
					if (nPendents < MAX_PENDENTS)
						pendents[nPendents++].mov = nouMov;
					found = true;
				}
			}
			// Si no hay más saltos posibles, guarda como movimiento válido
			if (!found)
				m_tauler[x][y].afegirMoviment(actual);

			idx++;
		}
	}
	else if (f.getTipus() == TIPUS_DAMA)
	{
		nDireccions = 4;
		direccions[0][0] = 1;  direccions[0][1] = 1;
		direccions[1][0] = 1;  direccions[1][1] = -1;
		direccions[2][0] = -1; direccions[2][1] = 1;
		direccions[3][0] = -1; direccions[3][1] = -1;

		// --- MOVIMIENTOS SIMPLES ---
		for (int i = 0; i < nDireccions; i++)
		{
			int nx = x + direccions[i][0];
			int ny = y + direccions[i][1];
			while (dinsTauler(nx, ny) && m_tauler[nx][ny].getTipus() == TIPUS_EMPTY)
			{
				Posicio p(nx, ny);
				m_tauler[x][y].afegirMoviment(Moviments(p, false, false));
				nx += direccions[i][0];
				ny += direccions[i][1];
			}
		}

		// --- MOVIMIENTOS DE CAPTURA (MULTI-JUMP DAMA) ---
		struct PendentDama {
			Moviments mov;
			Posicio comidas[POSICIONS_MAXIMES];
			int nComidas;
			};
		PendentDama pendents[100];
		int nPendents = 0;

		// Capturas iniciales
		for (int dir = 0; dir < nDireccions; dir++)
		{
			int dx = direccions[dir][0];
			int dy = direccions[dir][1];
			int nx = x + dx;
			int ny = y + dy;
			// Avanza hasta ficha rival o fuera de tablero
			while (dinsTauler(nx, ny) && m_tauler[nx][ny].getTipus() == TIPUS_EMPTY)
			{
				nx += dx;
				ny += dy;
			}
			if (dinsTauler(nx, ny) && m_tauler[nx][ny].getColor() != f.getColor() && m_tauler[nx][ny].getTipus() != TIPUS_EMPTY)
			{
				int ex = nx + dx;
				int ey = ny + dy;
				while (dinsTauler(ex, ey) && m_tauler[ex][ey].getTipus() == TIPUS_EMPTY)
				{
					Moviments mov(Posicio(ex, ey), true, true);
					mov.afegirMort(Posicio(nx, ny));
					pendents[nPendents].mov = mov;
					pendents[nPendents].comidas[0] = Posicio(nx, ny);
					pendents[nPendents].nComidas = 1;
					nPendents++;
					ex += dx;
					ey += dy;
				}
			}
		}

		// Multi-jump DAMA
		int p = 0;
		while (p < nPendents)
		{
			Moviments actual = pendents[p].mov;
			Posicio comidas[POSICIONS_MAXIMES];
			int nComidas = pendents[p].nComidas;
			for (int i = 0; i < nComidas; i++)
				comidas[i] = pendents[p].comidas[i];

			Posicio ultima = actual.getUltimaPosicio();
			int ux = ultima.getX();
			int uy = ultima.getY();
			bool found = false;

			for (int dir = 0; dir < nDireccions; dir++)
			{
				int dx = direccions[dir][0];
				int dy = direccions[dir][1];
				int nx = ux + dx;
				int ny = uy + dy;
				// Avanza hasta encontrar ficha rival o fuera de tablero
				while (dinsTauler(nx, ny) && m_tauler[nx][ny].getTipus() == TIPUS_EMPTY)
				{
					nx += dx;
					ny += dy;
				}
				// ¿Rival, no vacía, y no comida antes?
				bool yaComida = false;
				for (int v = 0; v < nComidas; v++)
					if (comidas[v] == Posicio(nx, ny))
						yaComida = true;
				if (
					dinsTauler(nx, ny) &&
					m_tauler[nx][ny].getColor() != f.getColor() &&
					m_tauler[nx][ny].getTipus() != TIPUS_EMPTY &&
					!yaComida)
				{
					int ex = nx + dx;
					int ey = ny + dy;
					while (dinsTauler(ex, ey) && m_tauler[ex][ey].getTipus() == TIPUS_EMPTY)
					{
						Moviments mov2 = actual;
						mov2.afegirPosicio(Posicio(ex, ey));
						mov2.afegirMort(Posicio(nx, ny));
						pendents[nPendents].mov = mov2;
						// Copia comidas anteriores y añade la nueva
						for (int vv = 0; vv < nComidas; vv++)
							pendents[nPendents].comidas[vv] = comidas[vv];
						pendents[nPendents].comidas[nComidas] = Posicio(nx, ny);
						pendents[nPendents].nComidas = nComidas + 1;
						nPendents++;
						found = true;
						ex += dx;
						ey += dy;
					}
				}
			}
			if (!found)
				m_tauler[x][y].afegirMoviment(actual);

			p++;
		}
	}
}

int Tauler::getMaxMenjadesJugador(ColorFitxa color) const
{
    int max = 0;
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            if (m_tauler[i][j].getColor() == color && m_tauler[i][j].getTipus() != TIPUS_EMPTY)
            {
                int fitxaMax = m_tauler[i][j].getMaxMenjades();
                if (fitxaMax > max)
                    max = fitxaMax;
            }
        }
    }
    return max;
}