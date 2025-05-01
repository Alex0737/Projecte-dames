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
    Posicio mValids[100];
    int nValids = 0;
    Posicio mPendents[100];
    int nPendents = 0;

    int nPosicions = 0;
    int x = m_posicio.getX();
    int y = m_posicio.getY();
    if (m_color == COLOR_BLANC)
    {
        if (tauler.getTipusFitxa(x + 1, y + 1) == TIPUS_EMPTY) // mirar hacia la derecha
        {
            Posicio p(x + 1, y + 1);
            m_moviments[nPosicions].afegirPosicio(p);
        }
        else
        {
            if (tauler.getFitxa(x+1,y+1).getColor() == COLOR_NEGRE && tauler[x + 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
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
                    nPendents--;
                    if (tauler.getColorFitxa(x + 1, y + 1) == COLOR_NEGRE && tauler[x + 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
                    {
                        if (nPendents > 0) //si no está repetido)
                            mValids[nValids++] = Posicio(x + 2, x + 2);
                            mPendents[nPendents++] = Posicio(x + 2, x + 2);
                    }
                    if (tauler.getColorFitxa(x-1, y+1) == COLOR_NEGRE && tauler[x - 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
                    {
                        mValids[nValids++] = Posicio(x - 2, y + 2);
                        mPendents[nPendents++] = Posicio(x - 2, y + 2);
                    }
                    mPendents[nPendents++] = Posicio(x + 2, x + 2);
                } while (nPendents > 0);
            }
        }
        
        if (tauler.getTipusFitxa(x - 1, y + 1) == TIPUS_EMPTY) //mirar hacia la izquierda
        {
            Posicio p(x - 1, y + 1);
            m_moviments[nPosicions].afegirPosicio(p);
        }
        else //Ficha negra
        {
            if (tauler.getFitxa(x - 1, y + 1).getColor() == COLOR_NEGRE && tauler[x - 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
            {
                mValids[nPendents++] = Posicio(x - 2, y + 2);
                mPendents[nPendents++] = Posicio(x - 2, y + 2);
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
                    nPendents--;
                    if (tauler.getColorFitxa(x + 1, y + 1) == COLOR_NEGRE && tauler[x + 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
                    {
                        if (nPendents > 0) //si no está repetido)
                        {
                            mValids[nValids++] = Posicio(x + 2, x + 2);
                            mPendents[nPendents++] = Posicio(x + 2, x + 2);
                        }
                    }
                    if (tauler.getColorFitxa(x - 1, y + 1) == COLOR_NEGRE && tauler[x - 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
                    {
                        if (nPendents > 0) //si no está repetido)
                        {
                            mValids[nValids++] = Posicio(x - 2, y - 2);
                            mPendents[nPendents++] = Posicio(x - 2, y - 2);
                        }
                    }
                } while (mPendents != []);
            }
        }
    }
    else
    {
        if (tauler.getTipusFitxa(x, y) == TIPUS_DAMA) //dreta
        {

            if (tauler.getColorFitxa(x,y) == COLOR_BLANC)
            {
                Posicio p(x, y);
                bool trobat = false;
                int i = 1;
                int j = 1;
                while (x < 8 && y < 8 && !trobat) //mirar hacia la derecha
                {
                    if (tauler.getTipusFitxa(x + i, y + i) == TIPUS_EMPTY)
                    {
                        mValids[nPendents++] = p.setPosicio(x + i, y + i);
                        i++;
                    }
                    else
                        trobat = true;

                    if (trobat)
                    {

                    }
                }

                while (x < 8 && y < 8 && !trobat) //mirar hacia la izquierda
                {
                    if ()
                }
            }
            else
            {
                if (tauler.getColorFitxa(x, y) == COLOR_NEGRE)
            }
        }


    }
}