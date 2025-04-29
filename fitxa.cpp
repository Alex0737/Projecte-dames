#include "fitxa.h"


void Fitxa::convertirDama()
{
    m_tipus = TIPUS_DAMA;
}

bool Fitxa::operator==(const Fitxa& f) const
{
    return (m_posicio == f.m_posicio && m_color == f.m_color && m_tipus == f.m_tipus);
}

void Fitxa::afegirMoviment(const Moviments& moviment)
{
    m_movimentsPossibles.afegirMoviment(moviment);
}

void Fitxa::netejaMoviments()
{
    m_movimentsPossibles.neteja();
}

void Fitxa::setPosicioBuida(const Posicio& p)
{
	m_tipus = TIPUS_EMPTY;
}

bool Fitxa::operator==(const Fitxa& f)
{
	return (m_posicio == f.m_posicio && m_color == f.m_color && m_tipus == f.m_tipus);
}
void Fitxa::setPosNova(const Posicio& pos, ColorFitxa c, TipusFitxa t)
{
	int x = pos.getX();
	int y = pos.getY();
	m_color = c;
	m_tipus = t;

}

string Fitxa::posicionsMoviment()
{
	string s;
	for (int i = 0; i < m_nPosicionsValides - 2; i++)
	{
		s += m_movimentsPossibles.getPosicioIndex(i).toString();
		s += " ,";
	}
	s += m_movimentsPossibles.getPosicioIndex(m_nPosicionsValides - 1).toString();
	return s;
}

Posicio Fitxa::movimentsValids(int n)
{
	m_movimentsPossibles.getPosicioIndex(n);
}


void calcularMovimentsValids(const Tauler& tauler)
{
	m_nMoviments = 0;
	Moviments pendents[];
	int princpi = 0;
	int final = 0;

}

void Fitxa::calcularMovimentsValids2(
    const Tauler& tauler,
    Moviment      movimentsValids[],
    int& nValid
) const
{
    const int MAX_PENDENTS = 512;
    Moviment movimentsPendents[MAX_PENDENTS];
    int inici = 0;
    int final = 0;

    // Inicialment, afegim moviment buit
    movimentsPendents[final++] = Moviment();

    nValid = 0;

    while (inici < final)
    {
        // Agafem el primer moviment pendent
        Moviment movimentActual = movimentsPendents[inici++];
        Posicio  posicioActual = movimentActual.ultimPosicio(m_posicio);

        // Calculem les posicions valides des d’aquesta posicio
        Posicio posValides[8];
        int     nPosValides = 0;

        tauler.getPosicionsValides(
            posicioActual,
            m_color,
            m_tipus,
            nPosValides,
            posValides);

        // Mentre hi hagi posicions valides, continuem
        while (nPosValides > 0)
        {
            // Afegim la primera posicio valida al moviment actual
            movimentActual.afegirPosicio(posValides[0]);

            // Per la resta de posicions valides, clonem el moviment
            for (int i = 1; i < nPosValides; ++i)
            {
                Moviment nouMov = movimentActual;
                nouMov.afegirPosicio(posValides[i]);

                if (final < MAX_PENDENTS)
                    movimentsPendents[final++] = nouMov;
            }

            // Continuem el bucle des de la nova posició
            posicioActual = posValides[0];
            tauler.getPosicionsValides(
                posicioActual,
                m_color,
                m_tipus,
                nPosValides,
                posValides);
        }

        // Si el moviment final no és buit, el guardem
        if (movimentActual.getNombre() > 0
            && nValid < MAX_MOVIMENTS)
        {
            movimentsValids[nValid++] = movimentActual;
        }
    }
}
