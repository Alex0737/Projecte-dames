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


Posicio Joc::converteixAPosicio(int mouseX, int mouseY) {
    Posicio posicio;
    int casellaX = (mouseY - POS_X_TAULER) / 80; // fila
    int casellaY = (mouseX - POS_Y_TAULER) / 80; // columna
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
    // Solo inicializar el tablero al principio (no cada frame)
    if (!iniciat)
    {
        //m_tauler.inicialitza("tauler_inicial.txt");
        inicialitza(m_mode, "tauler_inicial.txt", "moviments.txt");
        m_tauler.actualitzaMovimentsValids();

        iniciat = true;
        m_finalPartida = false;

    }

    // 1. Dibuja el fondo y tablero
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER - 52, POS_Y_TAULER - 66);

    // 2. Dibuja todas las fichas
    for (int fila = 0; fila < N_FILES; ++fila)
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

    // 3. Dibuja posiciones válidas (casillas verdes) si hay ficha seleccionada
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



    // 4. Gestión de clicks de ratón:
    // Solo ejecuta la selección cuando el usuario SUELTA el botón del ratón (no mientras lo mantiene pulsado)
    bool moureFitxa = false;
    static bool lastMouseStatus = false;   //NO SE COMO QUITARLO, HAY Q MIRAR
    if (m_mode == MODE_JOC_NORMAL)
    {
        if (!mouseStatus && lastMouseStatus) // Se ha soltado el botón
        {
            int col = (mousePosX - POS_X_TAULER) / AMPLADA_CASELLA;
            int fila = (mousePosY - POS_Y_TAULER) / ALCADA_CASELLA;
            // 4.A: Si hay una ficha seleccionada y has hecho click en una posición válida, mueve la ficha:
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
                    // 1. Mueve la ficha
                    m_tauler.mouFitxa(m_posFitxaSeleccionada, destino);

                    // 2. Guarda el movimiento
                    Moviments mov(m_posFitxaSeleccionada, false, false);
                    mov.afegirPosicio(destino);
                    m_cua.afegirMoviment(mov);

                    // 3. Deselecciona ficha
                    m_fitxaSeleccionada = false;
                    m_posicionsValides.clear();

                    // 4. Cambia turno
                    m_jugadorTorn = (m_jugadorTorn == COLOR_BLANC) ? COLOR_NEGRE : COLOR_BLANC;

                    // 5. Actualiza movimientos válidos
                    m_tauler.actualitzaMovimentsValids();

                    if (haAcabat())
                    {
                        m_finalPartida = true;
                        // Aquí ya se habrá actualizado m_guanyador dentro de haAcabat()
                    }

                    moureFitxa = true;
                }
            }

            if (!moureFitxa && fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES)
            {
                Fitxa f = m_tauler.getFitxa(fila, col);

                // Si clicas en ficha propia
                if (f.getTipus() != TIPUS_EMPTY && f.getColor() == m_jugadorTorn)
                {
                    m_fitxaSeleccionada = true;
                    m_posFitxaSeleccionada = Posicio(fila, col);

                    m_posicionsValides.clear();
                    Posicio posicionsPossibles[20];
                    m_tauler.getPosicionsPossibles(m_posFitxaSeleccionada, m_nPosicionsValides, posicionsPossibles);

                    // --- LOG PARA DIAGNÓSTICO ---
                    std::cout << "Movimientos válidos para (" << fila << "," << col << "): " << m_nPosicionsValides << std::endl;
                    for (int i = 0; i < m_nPosicionsValides; ++i) {
                        m_posicionsValides.push_back(posicionsPossibles[i]);
                        std::cout << "  (" << posicionsPossibles[i].getX() << "," << posicionsPossibles[i].getY() << ")" << std::endl;
                    }
                    // --- FIN LOG ---
                }

            }

        }
    }
    else
    {
        if (!mouseStatus && lastMouseStatus && !m_finalPartida)
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
    lastMouseStatus = mouseStatus; // Recuerda el estado para la próxima iteración




    if (m_finalPartida)
    {
        std::string textoGanador;
        if (m_guanyador == COLOR_BLANC)
            textoGanador = "¡GANA EL JUGADOR BLANCO!";
        else if (m_guanyador == COLOR_NEGRE)
            textoGanador = "¡GANA EL JUGADOR NEGRO!";
        else
            textoGanador = "¡EMPATE!";

        int posTextX = POS_X_TAULER;
        int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * N_FILES) + 100;
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, textoGanador);
    }


    // 5. Puedes mostrar la posición del ratón debajo del tablero (opcional)
    int posTextX = POS_X_TAULER;
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * N_FILES) + 120;
    std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);

    std::string turnoJugador = (m_jugadorTorn == COLOR_BLANC) ? "Jugador actual: Blanques" : "Jugador actual: Negres";
    int posTurnoY = posTextY + 30;
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTurnoY, 0.8, turnoJugador);

    std::string modeJocStr;
    if (m_mode == MODE_JOC_NORMAL)
        modeJocStr = "Mode joc: Normal";
    else if (m_mode == MODE_JOC_REPLAY)
        modeJocStr = "Mode joc: Replay";

    int posModeY = posTurnoY + 30;
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posModeY, 0.8, modeJocStr);
    return false;
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

    if (nNegres == 0 || !negrePotMoure)
        m_guanyador = COLOR_BLANC;
    else if (nBlancs == 0 || !blancPotMoure)
        m_guanyador = COLOR_NEGRE;
    else
        m_guanyador = COLOR_BUIT; // O valor para empate

    return (nNegres == 0 || !negrePotMoure || nBlancs == 0 || !blancPotMoure);
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

            fitxer << p1 << p2;
        }
        fitxer.close();
    }
}
