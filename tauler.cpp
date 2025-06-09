#include "tauler.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include "GraphicManager.h"
#include "info_joc.hpp"
const int MIDA_CASELLA = 80;


Tauler::Tauler()
{
    m_tauler = std::vector<std::vector<Fitxa>>(N_FILES, std::vector<Fitxa>(N_COLUMNES));
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
            m_tauler[i][j].netejaMoviments();
        }
    }
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;
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
                {
                    int k = 0;
                    bool trobat = false;
                    while (k < nPosicions && !trobat)
                    {
                        if (posicionsPossibles[k] == pos)
                            trobat = true;
                        else
                            k++;
                    }
                    if (!trobat)
                        posicionsPossibles[nPosicions++] = pos;
                }
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

bool Tauler::dinsTauler(int x, int y) const
{
    return (x >= 0 && x < N_FILES && y >= 0 && y < N_COLUMNES);
}

void Tauler::inicialitza(const std::string& nomFitxer)
{
    std::ifstream fitxer(nomFitxer);
    netejaTauler();

    if (fitxer.is_open())
    {
        char tipus;
        std::string posicioStr;

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

std::string Tauler::toString() const
{
    std::string s;
    for (int i = 0; i < 8; i++)
    {
        int t = 8 - i;
        s += std::to_string(t);
        s += ": ";
        for (int j = 0; j < 8; j++)
        {
            if (m_tauler[i][j].getColor() == COLOR_BLANC && m_tauler[i][j].getTipus() == TIPUS_DAMA)
            {
                s += "D";
            }
            else if (m_tauler[i][j].getTipus() == TIPUS_EMPTY)
            {
                s += "_";
            }
            else if (m_tauler[i][j].getColor() == COLOR_BLANC && m_tauler[i][j].getTipus() == TIPUS_NORMAL)
            {
                s += "O";
            }
            else if (m_tauler[i][j].getColor() == COLOR_NEGRE && m_tauler[i][j].getTipus() == TIPUS_NORMAL)
            {
                s += "X";
            }
            else if (m_tauler[i][j].getColor() == COLOR_NEGRE && m_tauler[i][j].getTipus() == TIPUS_DAMA)
            {
                s += "R";
            }
            s += " ";
        }
        s += "\n";
    }
    s += "   a b c d e f g h";
    return s;
}

TipusFitxa Tauler::toTipus(char s) const
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

TipusFitxa Tauler::getTipusFitxa(int x, int y) const
{
    TipusFitxa resultat;
    if (x >= 0 && x < N_FILES && y >= 0 && y < N_COLUMNES)
        resultat = m_tauler[x][y].getTipus();
    else
        resultat = TIPUS_EMPTY;
    return resultat;
}


ColorFitxa Tauler::getColorFitxa(int x, int y) const
{
    return m_tauler[x][y].getColor();
}

void Tauler::setPosBuida(const Posicio& pos)
{
    int x = pos.getX();
    int y = pos.getY();
    if (dinsTauler(x, y))
        m_tauler[x][y].setTipus(TIPUS_EMPTY);
}

void Tauler::calcularMovimentsValids(const Fitxa& fitxa)
{
    int x = fitxa.getX();
    int y = fitxa.getY();
    Fitxa& f = m_tauler[x][y];

    int direccions[4][2];
    int nDireccions = 0;

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

        std::vector<Moviments> pendents;

        for (int i = 0; i < nDireccions; i++)
        {
            int nx = x + direccions[i][0];
            int ny = y + direccions[i][1];
            int nx2 = x + 2 * direccions[i][0];
            int ny2 = y + 2 * direccions[i][1];

            if (dinsTauler(nx, ny) && dinsTauler(nx2, ny2) &&
                m_tauler[nx][ny].getTipus() != TIPUS_EMPTY &&
                m_tauler[nx][ny].getColor() != f.getColor() &&
                m_tauler[nx2][ny2].getTipus() == TIPUS_EMPTY)
            {
                Moviments mov(Posicio(nx2, ny2), false, false);
                mov.afegirMort(Posicio(nx, ny));
                pendents.push_back(mov);
                f.setMoviment(mov);
            }
        }

        int idx = 0;
        while (idx < pendents.size())
        {
            Moviments actual = pendents[idx];
            Posicio ultima = actual.getUltimaPosicio();
            int ux = ultima.getX();
            int uy = ultima.getY();
            bool trobat = false;

            for (int i = 0; i < nDireccions; i++)
            {
                int nx = ux + direccions[i][0];
                int ny = uy + direccions[i][1];
                int nx2 = ux + 2 * direccions[i][0];
                int ny2 = uy + 2 * direccions[i][1];
                bool yaComida = false;
                for (int j = 0; j < actual.getMenjades(); j++)
                    if (Posicio(nx, ny) == actual.getFitxaMatada(j))
                        yaComida = true;

                if (dinsTauler(nx, ny) && dinsTauler(nx2, ny2) &&
                    m_tauler[nx][ny].getTipus() != TIPUS_EMPTY &&
                    m_tauler[nx][ny].getColor() != f.getColor() &&
                    m_tauler[nx2][ny2].getTipus() == TIPUS_EMPTY && !yaComida)
                {
                    Moviments nouMov = actual;
                    nouMov.afegirPosicio(Posicio(nx2, ny2));
                    nouMov.afegirMort(Posicio(nx, ny));
                    pendents.push_back(nouMov);
                    trobat = true;
                    f.setMoviment(nouMov);
                }
            }
            if (!trobat)
                f.afegirMoviment(actual);

            idx++;
        }

        for (int i = 0; i < nDireccions; i++)
        {
            int nx = x + direccions[i][0];
            int ny = y + direccions[i][1];
            if (dinsTauler(nx, ny) && m_tauler[nx][ny].getTipus() == TIPUS_EMPTY)
            {
                Posicio p(nx, ny);
                f.afegirMoviment(Moviments(p, false, false));
            }
        }
    }
    else
    {
        if (f.getTipus() == TIPUS_DAMA)
        {
            nDireccions = 4;
            direccions[0][0] = 1;  direccions[0][1] = 1;
            direccions[1][0] = 1;  direccions[1][1] = -1;
            direccions[2][0] = -1; direccions[2][1] = 1;
            direccions[3][0] = -1; direccions[3][1] = -1;
        }

        for (int i = 0; i < nDireccions; i++)
        {
            int nx = x + direccions[i][0];
            int ny = y + direccions[i][1];
            while (dinsTauler(nx, ny) && m_tauler[nx][ny].getTipus() == TIPUS_EMPTY)
            {
                Posicio p(nx, ny);
                f.afegirMoviment(Moviments(p, false, false));
                nx += direccions[i][0];
                ny += direccions[i][1];
            }
        }

        std::vector<Moviments> pendentsMov;
        std::vector<std::vector<Posicio>> pendentsComidas;

        for (int dir = 0; dir < nDireccions; dir++)
        {
            int dx = direccions[dir][0];
            int dy = direccions[dir][1];
            int nx = x + dx;
            int ny = y + dy;
            while (dinsTauler(nx, ny) && m_tauler[nx][ny].getTipus() == TIPUS_EMPTY)
            {
                nx += dx;
                ny += dy;
            }
            if (dinsTauler(nx, ny) && m_tauler[nx][ny].getColor() != f.getColor() && m_tauler[nx][ny].getTipus() != TIPUS_EMPTY)
            {
                int ex = nx + dx;
                int ey = ny + dy;
                if (dinsTauler(ex, ey) && m_tauler[ex][ey].getTipus() == TIPUS_EMPTY)
                {
                    Moviments mov(Posicio(ex, ey), true, true);
                    mov.afegirMort(Posicio(nx, ny));
                    std::vector<Posicio> comidas;
                    comidas.push_back(Posicio(nx, ny));
                    pendentsMov.push_back(mov);
                    pendentsComidas.push_back(comidas);
                    // NO SIGAS AVANZANDO con ex += dx, ey += dy;
                }
            }
        }

        int p = 0;
        while (p < pendentsMov.size())
        {
            Moviments actual = pendentsMov[p];
            std::vector<Posicio> comidas = pendentsComidas[p];
            Posicio ultima = actual.getUltimaPosicio();
            int ux = ultima.getX();
            int uy = ultima.getY();
            bool trobat = false;

            for (int dir = 0; dir < nDireccions; dir++)
            {
                int dx = direccions[dir][0];
                int dy = direccions[dir][1];
                int nx = ux + dx;
                int ny = uy + dy;
                while (dinsTauler(nx, ny) && m_tauler[nx][ny].getTipus() == TIPUS_EMPTY)
                {
                    nx += dx;
                    ny += dy;
                }
                bool yaComida = false;
                for (const auto& c : comidas)
                    if (c == Posicio(nx, ny))
                        yaComida = true;
                if (dinsTauler(nx, ny) && m_tauler[nx][ny].getColor() != f.getColor() &&
                    m_tauler[nx][ny].getTipus() != TIPUS_EMPTY && !yaComida)
                {
                    int ex = nx + dx;
                    int ey = ny + dy;
                    if (dinsTauler(ex, ey) && m_tauler[ex][ey].getTipus() == TIPUS_EMPTY)
                    {
                        Moviments mov2 = actual;
                        mov2.afegirPosicio(Posicio(ex, ey));
                        mov2.afegirMort(Posicio(nx, ny));
                        std::vector<Posicio> comidas2 = comidas;
                        comidas2.push_back(Posicio(nx, ny));
                        pendentsMov.push_back(mov2);
                        pendentsComidas.push_back(comidas2);
                        trobat = true;
                    }
                }
            }
            if (!trobat)
                f.afegirMoviment(actual);

            p++;
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

    if (dinsTauler(xO, yO) && dinsTauler(xD, yD) && m_tauler[xO][yO].estaDesti(desti))
    {
        int i = m_tauler[xO][yO].getIndexMoviment(desti);
        if (i != -1)
        {
            int k = 0;
            bool trobat = false;
            while (k < m_tauler[xO][yO].getNumMoviments() && !trobat)
            {
                if (m_tauler[xO][yO].getMoviment(k).getUltimaPosicio() == desti)
                    trobat = true;
                else
                    k++;
            }
            for (int j = 0; j < m_tauler[xO][yO].getMoviment(k).getMenjades(); j++)
            {
                Posicio p = m_tauler[xO][yO].getMoviment(k).getFitxaMatada(j);
                int x = p.getX();
                int y = p.getY();
                if (dinsTauler(x, y))
                    m_tauler[x][y].setPosicioBuida();
            }
            bool calBufar = false;
            if (m_tauler[xO][yO].getMoviment(k).getMenjades() < getMaxMenjadesJugador(m_tauler[xO][yO].getColor())
                || !(m_tauler[xO][yO].getMoviment(k).getMenjades() == getMaxMenjadesJugador(m_tauler[xO][yO].getColor()))
                && m_tauler[xO][yO].getMoviment(k).getDamesMenjades() == getMaxDamesJugador(m_tauler[xO][yO].getColor()))
            {
                calBufar = true;
            } 
            m_tauler[xD][yD] = m_tauler[xO][yO];
            m_tauler[xD][yD].setPosicio(Posicio(xD, yD));
            m_tauler[xO][yO].setPosicioBuida();
            if (m_tauler[xD][yD].getTipus() == TIPUS_NORMAL)
            {
                if ((m_tauler[xD][yD].getColor() == COLOR_BLANC && xD == 0) ||
                    (m_tauler[xD][yD].getColor() == COLOR_NEGRE && xD == N_FILES - 1) && m_tauler[xD][yD].getTipus() != TIPUS_DAMA)
                {
                    m_tauler[xD][yD].convertirDama();
                }
            }
            if (calBufar)
            {
                Posicio pBufar = getFitxaBufar(m_tauler[xD][yD].getColor());
                if (m_tauler[pBufar.getX()][pBufar.getY()].getTipus() != TIPUS_EMPTY)
                    m_tauler[pBufar.getX()][pBufar.getY()].setPosicioBuida();
            }

            resultat = true;
        }
    }
    actualitzaMovimentsValids();
    return resultat;
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
                {
                    max = fitxaMax;
                }
            }
        }
    }
    return max;
}

int Tauler::getMaxDamesJugador(ColorFitxa color) const
{
    int max = 0;
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            if (m_tauler[i][j].getColor() == color && m_tauler[i][j].getTipus() != TIPUS_EMPTY)
            {
                int fitxaMax = m_tauler[i][j].getDamesMaximes();
                if (fitxaMax > max)
                {
                    max = fitxaMax;
                }
            }
        }
    }
    return max;
}

Posicio Tauler::getFitxaBufar(ColorFitxa color) const
{
    int maxMenjades = 0;
    Posicio pBufar(-1, -1);

    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            const Fitxa& f = m_tauler[i][j];
            if (f.getColor() == color && f.getTipus() != TIPUS_EMPTY)
            {
                int fitxaMax = f.getMaxMenjades();
                if (fitxaMax > maxMenjades)
                {
                    maxMenjades = fitxaMax;
                    pBufar.setX(i);
                    pBufar.setY(j);
                }
                else if (fitxaMax == maxMenjades && maxMenjades > 0)
                {
                    if (i < pBufar.getX() || (i == pBufar.getX() && j < pBufar.getY()))
                    {
                        pBufar.setX(i);
                        pBufar.setY(j);
                    }
                }
            }
        }
    }
    return pBufar;
}

void Tauler::visualitza() 
{
    for (int x = 0; x < N_FILES; ++x) 
    {
        for (int y = 0; y < N_COLUMNES; ++y) 
        {
            Fitxa* f = &m_tauler[x][y];
            if (f != nullptr && f->getTipus() != TIPUS_EMPTY)
                f->visualitza(POS_X_TAULER + x * MIDA_CASELLA, POS_Y_TAULER + y * MIDA_CASELLA);
        }
    }
}