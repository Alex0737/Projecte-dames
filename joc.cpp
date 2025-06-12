//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"



#include "GraphicManager.h"
#include "Joc.hpp" // O el header donde tienes la clase Joc



void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments)
{
    m_nPosicionsValides = 0;
    m_mode = mode;
    m_tauler.inicialitza(nomFitxerTauler);
    m_jugadorTorn = COLOR_BLANC;
    m_finalPartida = false;
    m_fitxaSeleccionada = false;
    if (mode == MODE_JOC_REPLAY)
    {
        m_cua.carregaMoviments(nomFitxerMoviments);
    }
    else
    {
        if (mode == MODE_JOC_NORMAL)
        {
            m_nomArxiuMoviments = nomFitxerMoviments;
            CuaMoviments m_cua();
        }
    }
}


Posicio Joc::converteixAPosicio(int mouseX, int mouseY)
{
    Posicio posicio;
    int casellaX = (mouseY - POS_X_TAULER) / 80;
    int casellaY = (mouseX - POS_Y_TAULER) / 80;
    if (casellaX >= 0 && casellaX < 8 && casellaY >= 0 && casellaY < 8)
    {
        posicio.setX(casellaX);
        posicio.setY(casellaY);

    }
    else
    {
        posicio.setX(-1);
        posicio.setY(-1);
    }
    return posicio;
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
    bool resultado = false;
    if (haAcabat())
    {
        m_finalPartida = true;
    }
    if (!iniciat)
    {
        inicialitza(m_mode, m_nomArxiuTauler, m_nomArxiuMoviments);
        m_tauler.actualitzaMovimentsValids();

        iniciat = true;
        m_finalPartida = false;

    }

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER - 52, POS_Y_TAULER - 66);

    for (int fila = 0; fila < N_FILES; fila++)
    {
        for (int col = 0; col < N_COLUMNES; ++col)
        {
            Fitxa f = m_tauler.getFitxa(fila, col);
            if (f.getTipus() != TIPUS_EMPTY)
            {
                int posX = POS_X_TAULER + col * AMPLADA_CASELLA;
                int posY = POS_Y_TAULER + fila * ALCADA_CASELLA;
                f.visualitza(posX, posY);
            }
        }
    }

    if (m_fitxaSeleccionada)
    {
        for (int i = 0; i < m_posicionsValides.size(); i++)
        {
            Posicio p = m_posicionsValides[i];
            int posX = POS_X_TAULER + p.getY() * AMPLADA_CASELLA;
            int posY = POS_Y_TAULER + p.getX() * ALCADA_CASELLA;
            GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
        }
    }

    bool moureFitxa = false;

    if (!m_finalPartida)
    {
        if (m_mode == MODE_JOC_NORMAL || m_mode == MODE_JOC_UN && m_jugadorTorn == COLOR_BLANC)
        {
            if (!mouseStatus && m_ultimEstatRatoli)
            {
                int col = (mousePosX - POS_X_TAULER) / AMPLADA_CASELLA;
                int fila = (mousePosY - POS_Y_TAULER) / ALCADA_CASELLA;

                if (m_fitxaSeleccionada)
                {
                    Posicio destino(fila, col);
                    bool esValida = false;
                    for (int i = 0; i < m_posicionsValides.size(); i++)
                    {
                        Posicio pos = m_posicionsValides[i];
                        if (pos == destino)
                        {
                            esValida = true;
                        }
                    }

                    if (esValida)
                    {
                        m_tauler.mouFitxa(m_posFitxaSeleccionada, destino);

                        Moviments mov(m_posFitxaSeleccionada, false, false);
                        mov.afegirPosicio(destino);
                        m_cua.afegirMoviment(mov);

                        m_fitxaSeleccionada = false;
                        m_posicionsValides.clear();

                        if (m_jugadorTorn == COLOR_BLANC)
                        {
                            m_jugadorTorn = COLOR_NEGRE;
                        }
                        else
                        {
                            m_jugadorTorn = COLOR_BLANC;
                        }

                        m_tauler.actualitzaMovimentsValids();

                        moureFitxa = true;
                    }
                }

                if (!moureFitxa && fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES)
                {
                    Fitxa f = m_tauler.getFitxa(fila, col);

                    if (f.getTipus() != TIPUS_EMPTY && f.getColor() == m_jugadorTorn)
                    {
                        m_fitxaSeleccionada = true;
                        m_posFitxaSeleccionada = Posicio(fila, col);

                        m_posicionsValides.clear();
                        Posicio posicionsPossibles[20];
                        m_tauler.getPosicionsPossibles(m_posFitxaSeleccionada, m_nPosicionsValides, posicionsPossibles);

                        std::cout << "Moviments validos per (" << fila << "," << col << "): " << m_nPosicionsValides << std::endl;
                        for (int i = 0; i < m_nPosicionsValides; ++i)
                        {
                            m_posicionsValides.push_back(posicionsPossibles[i]);
                            std::cout << "  (" << posicionsPossibles[i].getX() << "," << posicionsPossibles[i].getY() << ")" << std::endl;
                        }
                    }

                }

            }
        }
        else
        {
            if (m_mode == MODE_JOC_REPLAY)
            {
                if (!mouseStatus && m_ultimEstatRatoli && !m_finalPartida)
                {
                    if (!m_cua.buida())
                    {
                        Moviments m = m_cua.treuPrimerMoviment();
                        if (m.getNombre() >= 2)
                        {
                            Posicio origen = m.getPosicioIndex(0);
                            Posicio desti = m.getUltimaPosicio();
                            m_tauler.mouFitxa(origen, desti);
                        }

                    }
                    else
                    {
                        m_finalPartida = true;
                    }
                }
            }
            else
            {
                if (m_mode == MODE_JOC_UN && m_jugadorTorn == COLOR_NEGRE && !m_finalPartida)
                {
                    bool haComido = false;

                    for (int fila = 0; fila < N_FILES && !haComido; fila++)
                    {
                        for (int col = 0; col < N_COLUMNES && !haComido; col++)
                        {
                            Fitxa f = m_tauler.getFitxa(fila, col);
                            if (f.getTipus() != TIPUS_EMPTY && f.getColor() == COLOR_NEGRE)
                            {
                                int nMov = f.getNPosicions();
                                for (int k = 0; k < nMov; k++)
                                {
                                    Moviments mov = f.getMoviment(k);
                                    if (mov.esCaptura())
                                    {
                                        m_tauler.mouFitxa(Posicio(fila, col), mov.getUltimaPosicio());

                                        Posicio origen(fila, col);
                                        Posicio destino = mov.getUltimaPosicio();
                                        Moviments movGuardar(origen, false, false);
                                        movGuardar.afegirPosicio(destino);
                                        m_cua.afegirMoviment(movGuardar);

                                        m_jugadorTorn = COLOR_BLANC;
                                        m_tauler.actualitzaMovimentsValids();
                                        if (haAcabat()) 
                                            m_finalPartida = true;
                                        haComido = true;
                                    }
                                }
                            }
                        }
                    }

                    // 2. Si NO ha comido, hace el primer movimiento normal que encuentre
                    if (!haComido)
                    {
                        for (int fila = 0; fila < N_FILES; ++fila)
                        {
                            for (int col = 0; col < N_COLUMNES; ++col)
                            {
                                Fitxa f = m_tauler.getFitxa(fila, col);
                                if (f.getTipus() != TIPUS_EMPTY && f.getColor() == COLOR_NEGRE)
                                {
                                    int nMov = f.getNPosicions();
                                    if (nMov > 0)
                                    {
                                        Moviments mov = f.getMoviment(0);
                                        m_tauler.mouFitxa(Posicio(fila, col), mov.getUltimaPosicio());

                                        m_jugadorTorn = COLOR_BLANC;
                                        Posicio origen(fila, col);
                                        Posicio destino = mov.getUltimaPosicio();
                                        Moviments movGuardar(origen, false, false);
                                        movGuardar.afegirPosicio(destino);
                                        m_cua.afegirMoviment(movGuardar);
                                        m_tauler.actualitzaMovimentsValids();
                                        if (haAcabat())
                                            m_finalPartida = true;
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    m_ultimEstatRatoli = mouseStatus;

    if (m_finalPartida)
    {
        std::string textoGanador;
        if (m_guanyador == COLOR_BLANC)
            textoGanador = "GUANYA EL JUGADOR BLANC!";
        else if (m_guanyador == COLOR_NEGRE)
            textoGanador = "GUANYA EL JUGADOR NEGRE!";
        else
            textoGanador = "EMPAT!";

        int posTextX = POS_X_TAULER;
        int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * N_FILES) + 100;
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, textoGanador);
    }

    int posTextX = POS_X_TAULER;
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * N_FILES) + 120;
    std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);

    std::string turnoJugador;
    if (m_jugadorTorn == COLOR_BLANC)
    {
        turnoJugador = "Jugador actual: Blanques";
    }
    else
    {
        turnoJugador = "Jugador actual: Negres";
    }
    int posTurnoY = posTextY + 30;
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTurnoY, 0.8, turnoJugador);

    std::string modeJocStr;

    if (m_mode == MODE_JOC_NORMAL)
    {
        modeJocStr = "Mode joc: Normal";
    }
    if (m_mode == MODE_JOC_REPLAY)
    {
        modeJocStr = "Mode joc: Replay";
    }
    if (m_mode == MODE_JOC_UN)
    {
        modeJocStr = "Mode joc: Un jugador";
    }

    int posModeY = posTurnoY + 30;
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posModeY, 0.8, modeJocStr);


    return resultado;
}




void Joc::finalitza()
{
    if (m_mode == MODE_JOC_NORMAL && haAcabat())
    {
        m_cua.guardarMoviments(m_nomArxiuMoviments);
    }
}

bool Joc::haAcabat()
{
    int nBlancs = 0;
    int nNegres = 0;
    bool blancPotMoure = false;
    bool negrePotMoure = false;
    bool acaba = false;
    int i = 0;
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            Fitxa f = m_tauler.getFitxa(i, j);
            if (f.getTipus() != TIPUS_EMPTY)
            {
                if (f.getColor() == COLOR_BLANC)
                {
                    nBlancs++;
                    if (f.getNPosicions() > 0)
                        blancPotMoure = true;
                }
                else if (f.getColor() == COLOR_NEGRE)
                {
                    nNegres++;
                    if (f.getNPosicions() > 0)
                        negrePotMoure = true;
                }
            }
        }
    }

    if (nNegres == 0 || !negrePotMoure || nBlancs == 0 || !blancPotMoure)
    {
        if (nNegres == 0 || !negrePotMoure)
            m_guanyador = COLOR_BLANC;
        else if (nBlancs == 0 || !blancPotMoure)
            m_guanyador = COLOR_NEGRE;
        else
            m_guanyador = COLOR_BUIT;

        acaba = true;

    }
    return acaba;
}

void Joc::guardaPartida(const string& nomFitxer)
{
    ofstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
    {
        Posicio pos1, pos2;
        while (!m_cua.buida())
        {
            Moviments m = m_cua.treuPrimerMoviment();
            pos1 = m.getPosicioIndex(0);
            pos2 = m.getUltimaPosicio();
            string p1 = pos1.toString();
            string p2 = pos2.toString();

            fitxer << p1 << " " << p2;
            fitxer << endl;
        }
        fitxer.close();
    }
}