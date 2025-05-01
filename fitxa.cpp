#include "fitxa.h"


void Fitxa::convertirDama()
{
    m_tipus = TIPUS_DAMA;
}

bool Fitxa::operator==(const Fitxa& f) const
{
    return (m_posicio == f.m_posicio && m_color == f.m_color && m_tipus == f.m_tipus);
}


void Fitxa::netejaMoviments()
{
    for (int i = 0; i < m_nMoviments; i++)
    {
        m_moviments[i].neteja();
    }
}

void Fitxa::setPosicioBuida()
{
    m_tipus = TIPUS_EMPTY;
}

bool Fitxa::operator==(const Fitxa& f) const
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

//string Fitxa::posicionsMoviment()
//{
//    string s;
//    for (int i = 0; i < m_nMoviments - 2; i++)
//    {
 //       s += m_movimentsPossibles.getPosicioIndex(i).toString();
//        s += " ,";
//    }
//    s += m_movimentsPossibles.getPosicioIndex(m_nPosicionsValides - 1).toString();
 //   return s;
//}

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
    Moviments     movimentsValids[],
    int& nValid
) const
{
    const int MAX_PENDENTS = 512;
    Moviments movimentsPendents[MAX_PENDENTS];
    int inici = 0;
    int final = 0;

    // Inicialment, afegim moviment buit
    movimentsPendents[final++] = Moviments();

    nValid = 0;

    while (inici < final)
    {
        // Agafem el primer moviment pendent
        Moviments movimentActual = movimentsPendents[inici++];
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
    Moviments mValids[100];
    int nValids = 0;
    Moviments mPendents[100];
    int nPendents = 0;
    Moviments MovimentsActuals[100];
    int nActuals = 0;

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
            if (tauler.getFitxa(x + 1, y + 1).getColor() == COLOR_NEGRE && tauler[x + 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
            {
                mValids[nPendents++] = Posicio(x + 2, x + 2);
                mPendents[nPendents++] = Posicio(x + 2, x + 2);
                Posicio p;
                do
                {
                    p = mPendents[nPendents-1];
                    x = p.getX();
                    y = p.getY();
                    mPendents[nPendents - 1].setPosicio(10, 10);
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
                    if (tauler.getColorFitxa(x - 1, y + 1) == COLOR_NEGRE && tauler[x - 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
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
                } while (nPendents<0);
            }
        }
    }
    else
    {
        if (tauler.getTipusFitxa(x, y) == TIPUS_DAMA) //dreta
        {

            if (tauler.getColorFitxa(x, y) == COLOR_BLANC)
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

bool posicionsValidesDreta(Moviments pendents[], int& nPendents, const Tauler& tauler, const Posicio& p)
{
    int x = p.getX();
    int y = p.getY();
    Moviments m;
    if (tauler.getTipusFitxa(x + 1, y + 1) == TIPUS_EMPTY) // mirar hacia la derecha
    {
        Posicio p(x + 1, y + 1);
        pendents[nPendents].afegirPosicio(p);
        nPendents++;
    }
    else
    {
        if (tauler.getFitxa(x + 1, y + 1).getColor() == COLOR_NEGRE && tauler[x + 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
        {
            pendents[nPendents++] = m.afegirMoviment(Posicio(x+2,y+2), );
            mPendents[nPendents++] = Posicio(x + 2, x + 2);
            Posicio p;
            do
            {
                p = mPendents[nPendents - 1];
                x = p.getX();
                y = p.getY();
                mPendents[nPendents - 1].setPosicio(10, 10);
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
                if (tauler.getColorFitxa(x - 1, y + 1) == COLOR_NEGRE && tauler[x - 2][y + 2].getTipusFitxa() == TIPUS_EMPTY)
                {
                    mValids[nValids++] = Posicio(x - 2, y + 2);
                    mPendents[nPendents++] = Posicio(x - 2, y + 2);
                }
                mPendents[nPendents++] = Posicio(x + 2, x + 2);
            } while (nPendents > 0);
        }
    }
}
bool posicionsValidesEsquerra(Moviments pendents[], const Tauler& tauler, const Posicio& p)
{
    int x = p.getX();
    int y = p.getY();
    if (tauler.getTipusFitxa(x + 1, y + 1) == TIPUS_EMPTY) // mirar hacia la derecha
    {
        Posicio p(x + 1, y + 1);
        m_moviments[nPosicions].afegirPosicio(p);
    }
    else
    {

    }
}
void Fitxa::movimentNormal2(const Tauler& tauler)
{
    Moviments mValids[100];
    int nValids = 0;
    Moviments mPendents[100];
    int nPendents = 0;
    Moviments MovimentsActuals[100];
    int nActuals = 0;

    

    
    do
    {
        Moviments movimentActual = mPendents[0];

    }


}

int Fitxa::getMaxMenjades() const 
{
    int max = 0;
    for (int i = 0; i < m_nMoviments; i++) 
    {
        if (m_moviments[i].getMenjades() > max)
        {
            max = m_moviments[i].getMenjades();
        }
    }
    return max;
}

int Fitxa::getDamesMaximes() const
{
    int max = 0;
    for (int i = 0; i < m_nMoviments; i++)
    {
        if (m_moviments[i].getMenjades() > max)
        {
            max = m_moviments[i].getDamesMenjades();
        }
    }
    return max;
}


void Fitxa::calcularMovimentsValids(const Tauler& tauler) {
    netejaMoviments();
    
    Moviments pendents[MAX_MOVS_FITXA];
    int inici = 0, final = 0;
    pendents[final++] = Moviment();
    bool acabat = false;
    int direccions[4][2];
    int nDireccions = 0;
    
    // Configurar direcciones
    if (m_tipus == TIPUS_NORMAL) {
        nDireccions = 2;
        direccions[0][0] = (m_color == COLOR_BLANC) ? 1 : -1;
        direccions[0][1] = 1;
        direccions[1][0] = (m_color == COLOR_BLANC) ? 1 : -1;
        direccions[1][1] = -1;
    } else if (m_tipus == TIPUS_DAMA) {
        nDireccions = 4;
        direccions[0][0] = 1; direccions[0][1] = 1;
        direccions[1][0] = 1; direccions[1][1] = -1;
        direccions[2][0] = -1; direccions[2][1] = 1;
        direccions[3][0] = -1; direccions[3][1] = -1;
    }
    
    while (inici < final && procesat) {
        Moviment actual = pendents[inici++];
        Posicio posActual = actual.getUltimaPosicio(m_posicio);
        
        int contadorDireccions = 0;
        while (contadorDireccions < nDireccions) {
            int dx = direccions[contadorDireccions][0];
            int dy = direccions[contadorDireccions][1];
            int x = posActual.getX();
            int y = posActual.getY();
            bool trobat = false;
            bool menjada = false;
            Moviments nouMov = actual;
            
            int iteracions = 0;
            int maxIter = (m_tipus == TIPUS_DAMA) ? 7 : 1;
            
            while (iteracions <= maxIter) {//cambiar este bucle
                x += dx;
                y += dy;
                iteracions++;
                
                if (tauler.dinsTauler(x, y)) {
                    Fitxa casella = tauler.getFitxa(x, y);
                    
                    if (casella.getTipus() == TIPUS_EMPTY && !menjada) {
                        if (actual.getMenjades() == 0) {
                            nouMov.afegirPosicio(Posicio(x, y));
                            afegirMoviment(nouMov);
                        }
                    } else if (casella.getColor() != m_color && !menjada) {
                        int xSalt = x + dx;
                        int ySalt = y + dy;
                        if (tauler.dinsTauler(xSalt, ySalt) && tauler.getFitxa(xSalt, ySalt).getTipus() == TIPUS_EMPTY) 
                        {
                            nouMov.afegirPosicio(Posicio(xSalt, ySalt));
                            nouMov.incrementaMenjades();
                            menjada = true;
                            pendents[final++] = nouMov;
                            trobat = true;
                        }
                    }
                    
                    if (casella.getTipus() != TIPUS_EMPTY) 
                    {
                        iteracions = maxIter + 1; // Forzar salida
                    }
                } 
                else 
                {
                    iteracions = maxIter + 1; // Forzar salida
                }
            }
            contadorDireccions++;
        }
    }
}


void Fitxa::calcularMovimentsValids7(const Tauler& tauler) //buena
{
    netejaMoviments();
    bool acabat = false;
    Moviments pendents[MAX_MOVS_FITXA];
    int inici = 0, final = 0;
    pendents[final++] = Moviments();

    int direccions[4][2];
    int nDireccions = 0;

    // Configurar direcciones
    if (m_tipus == TIPUS_NORMAL) 
    {
        nDireccions = 2;
        if (m_color == COLOR_BLANC)
        {
            direccions[0][0] = -1;
            direccions[0][1] = 1;
        }
        else
        {
            direccions[1][0] = -1;
            direccions[1][1] = -1;

        }
    }
    else
    {
        if (m_tipus == TIPUS_DAMA)
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


    while (inici < final && acabat) 
    { //cambiar bucle
        Moviments actual = pendents[inici++]; //ver esto pq
        Posicio posActual = actual.getUltimaPosicio();
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
            if (m_tipus == TIPUS_DAMA) 
            {
                maxIter = 7;  // Dames poden moure's fins a 7 caselles (màxim tauler 8x8)
            } 
            else 
            {
                maxIter = 1;  // Fitxes normals només 1 casella
            }

            while (iteracions < maxIter && !acabat) //cambiar este bucle
            {
                x += dx;
                y += dy;
                iteracions++;

                if (tauler.dinsTauler(x, y)) 
                {
                    Fitxa casella = tauler.getFitxa(x, y);

                    if (casella.getTipus() == TIPUS_EMPTY && !menjada) 
                    {
                        if (actual.getMenjades() == 0) 
                        {
                            nouMov.afegirPosicio(Posicio(x, y));
                            afegirMoviment(nouMov);
                        }
                    }
                    else 
                    {
                        if (casella.getColor() != m_color)
                        {
                            int xSalt = x + dx;
                            int ySalt = y + dy;
                            if (tauler.dinsTauler(xSalt, ySalt) && tauler.getFitxa(xSalt, ySalt).getTipus() == TIPUS_EMPTY)
                            {
                                nouMov.afegirPosicio(Posicio(xSalt, ySalt));
                                nouMov.incrementarMenjades();
                                if (tauler.getTipusFitxa(x, y) == TIPUS_DAMA)
                                {
                                    nouMov.incremetarMenjadesDames();
                                }
                                nouMov.setMenjat();
                                pendents[final++] = nouMov;
                                trobat = true;

                            }
                        }
                    }

                }
                else 
                {
                    acabat = true;
                }
            }
            nDireccions++;
        }
    }
}

bool Fitxa::calBufar(const Posicio& p, int i) const
{
    bool res = false;
    int x = p.getX();
    int y = p.getY();
    if (!getMoviment(i).estaFinal(p) || getMaxMenjades() < getMoviment(i).getMenjades() || (getMaxMenjades() == getMoviment(i).getMenjades() && getMoviment(i).getDamesMenjades() < getDamesMaximes()))
    {
        res = true;
    }

    return res;
}

bool Fitxa::estaDesti(const Posicio& p)const
{
    int i = 0;
    int j = 0;
    bool trobat = false;
    while (j < m_nMoviments && trobat)
    {
        while (i < getMoviment(j).getNombre() && !trobat)
        {
            if (p == getMoviment(j).getPosicio(i))
            {
                trobat = true;
            }
            else
                i++;
        }
        j++;
    }
    return trobat;
}

int Fitxa::getIndexMoviment(const Posicio& p)const
{
    int i = 0;
    int res =-1;
    int j = 0;
    bool trobat = false;
    while (j < m_nMoviments && trobat)
    {
        while (i < getMoviment(j).getNombre() && !trobat)
        {
            if (p == getMoviment(j).getPosicio(i))
            {
                trobat = true;
                res = j;
            }
            else
                i++;
        }
        if (!trobat)
            j++;
    }
    return res;
}
