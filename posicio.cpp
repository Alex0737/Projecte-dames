#include "posicio.h"

const int N_FILES = 8;

string Posicio::toString() const
{
	string pos = "a1";
	pos[0] = 'a' + m_y;
	pos[1] = '1' + (N_FILES - 1 - m_x);
	return pos;
}

bool Posicio::operator==(const Posicio& pos) const
{
	return m_x == pos.m_x && m_y == pos.m_y;
}

ostream& operator<<(ostream& out, const Posicio& pos) {
	out << pos.toString();
	return out;
}

void escriuFitxa(const string& nomFitxer, char tipusFitxa, const Posicio& posicio)
{
	ofstream fitxer(nomFitxer);
	fitxer << tipusFitxa << ' ' << posicio.toString();
	fitxer.close();
}


string Fitxa::posicionsMoviment()
{
	string s;
	for (int i = 0; i < m_nPosicionsValides - 2; i++)
	{
		s += m_moviments.getPosicioIndex(i).toString();
		s += " ,";
	}
	s += m_moviments.getPosicioIndex(m_nPosicionsValides - 1).toString();
	return s;
}

Posicio Fitxa::movimentsValids(int n)
{
	m_movimentsPossibles.getPosicioIndex(n);
}



void Fitxa::movimentNormal(const Tauler& tauler)
{
    Posicions mValids[100];
    int nValids = 0
    Posicions mPendents[100];
    int nPendents = 0;

    int nPosicions = 0;
    int x = m_posicio.getX();
    int y = m_posicio.getY();
    if (m_color == COLOR_BLANC)
    {
        if (tauler.getTipusFitxa(x + 1, y + 1) == TIPUS_EMPTY)
        {
            Posicio p(x + 1, y + 1);
            m_moviments[nPosicions].afegirPosicio(p);
        }
        else
        {
            if (tauler[x + 1][y + 1].getColor() == COLOR_NEGRE && tauler[x + 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
            {
                mValids[nPendents++] = Posicio(x + 2, x + 2);
                mPendents[nPendents++] = Posicio(x + 2, x + 2);
                Posicio p;
                do
                {
                    p = mPendents[0];
                    x = p.getX();
                    y = p.getY();
                    for (int i = 0; i > nPendents - 1; i++)
                    {
                        mPendents[i] = mPendents[i + 1];
                    }
                    nPentdents--;
                    if (tauler[x + 1][y + 1].getColor() == COLOR_NEGRE && tauler[x + 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
                    {
                        if (//esta dentro de alguno q no lo repita)
                        mValids[nValids++] = Posicio(x + 2, x + 2);
                        mPendents[nPendents++] = Posicio(x + 2, x + 2);
                    }
                    if (tauler[x - 1][y + 1].getColor() == COLOR_NEGRE && tauler[x - 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
                    {
                        mValids[nValids++] = Posicio(x + 2, x - 2);
                        mPendents[nPendents++] = Posicio(x + 2, x - 2);
                    }
                    mPendents[nPendents++] = Posicio(x+2, x+2)
                }while (mPendents != []);
            }
        }
        if (getTipusFitxa(x - 1, y + 1) == TIPUS_EMPTY)
        {
            Posicio p(x - 1, y + 1);
            m_moviments[nPosicions].afegirPosicio(p);
        }
    }
    else
    {

    }
}
