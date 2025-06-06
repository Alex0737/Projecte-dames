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
    int casellaY = (mouseX -POS_Y_TAULER)/ 80; // columna
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
    if (m_jugadorTorn == COLOR_BLANC)
    {
        m_jugadorTorn = COLOR_NEGRE;
    }
    else
    {
        m_jugadorTorn = COLOR_BLANC;
    }
    if (!iniciat)
    {
        m_tauler.inicialitza("tauler_inicial.txt");
        iniciat = true;
        // 1. Dibuja el fondo
    }
    
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);

    // 2. Dibuja el tablero
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER - 52, POS_Y_TAULER - 66);

    // 3. Dibuja todas las fichas en su posición (sin interacción, solo tablero inicial)

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

    if (mouseStatus) {
        int col = (mousePosX - POS_X_TAULER) / AMPLADA_CASELLA;
        int fila = (mousePosY - POS_Y_TAULER) / ALCADA_CASELLA;

        if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES) {
            Fitxa f = m_tauler.getFitxa(fila, col);
            if (f.getTipus() != TIPUS_EMPTY && f.getColor() == m_jugadorTorn) {
                m_fitxaSeleccionada = true;
                m_posFitxaSeleccionada = Posicio(fila, col);
            }
            std::cout << m_posFitxaSeleccionada.getX() << m_posFitxaSeleccionada.getY();

        }
    }

    if (m_fitxaSeleccionada)
    {

    }

    // 4. Puedes mostrar la posición del ratón debajo del tablero (opcional)
    int posTextX = POS_X_TAULER;
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * N_FILES) + 120;
    std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);

    // 5. No hace nada más, solo muestra el tablero y las fichas iniciales

    return false;
}




//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//
//
//
//bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
//{
//    bool acabat = false;
//    Posicio PosClick = converteixAPosicio(mousePosX, mousePosY);
//
//    // 1. Comprobación de fin de partida
//    if (m_finalPartida)
//    {
//        // mostraGuanyador(); // Aquí iría tu función para mostrar el ganador
//        acabat = true;
//    }
//    else
//    {
//        // 2. Gestión del modo normal
//        if (m_mode == MODE_JOC_NORMAL)
//        {
//            if (!mouseStatus) // Si NO se está pulsando el ratón (mouseStatus==false)
//            {
//                if (!m_fitxaSeleccionada)
//                {
//                    // Si no hay ficha seleccionada y se ha soltado el ratón
//                    // Puedes comprobar si el click está sobre una ficha del jugador actual
//                    Fitxa f = m_tauler.getFitxa(PosClick.getX(), PosClick.getY());
//                    if (f.getColor() == m_jugadorTorn && f.getTipus() != TIPUS_EMPTY)
//                    {
//                        m_fitxaSeleccionada = true;
//                        m_fitxaSeleccionada = PosClick;
//                        // Aquí podrías guardar los movimientos válidos, etc.
//                    }
//                }
//                else
//                {
//                    // Si ya hay una ficha seleccionada y se suelta el ratón
//                    // Intenta moverla si el click es a una casilla válida
//                    int nPosicions = 0;
//                    Posicio posicionsPossibles[10];
//                    m_tauler.getPosicionsPossibles(m_posicioFitxaSeleccionada, nPosicions, posicionsPossibles);
//                    for (int i = 0; i < nPosicions; ++i)
//                    {
//                        if (PosClick == posicionsPossibles[i])
//                        {
//                            // Movimiento válido, lo ejecutamos
//                            m_tauler.mouFitxa(m_posicioFitxaSeleccionada, PosClick);
//
//                            // Guardar en la CuaMoviments (ejemplo)
//                            m_cua.afegirMoviment(m_tauler.getFitxa(PosClick.getX(), PosClick.getY()), m_posicioFitxaSeleccionada, PosClick);
//
//                            // Cambiar turno, deseleccionar ficha, etc.
//                            m_fitxaSeleccionada = false;
//                            m_jugadorTorn = (m_jugadorTorn == COLOR_BLANC) ? COLOR_NEGRE : COLOR_BLANC;
//
//                            // Comprobar si la partida ha terminado, etc.
//                            // m_finalPartida = ... 
//
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//        // Puedes añadir lógica para MODE_JOC_REPLAY aquí si lo necesitas
//    }
//
//    // 3. DIBUJO DEL TABLERO Y GRÁFICOS
//    // --------------------------------
//
//    // 3.1 Dibuja el fondo
//    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
//
//    // 3.2 Dibuja el tablero
//    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
//
//    // 3.3 Dibuja todas las fichas del tablero
//    for (int i = 0; i < N_FILES; ++i) {
//        for (int j = 0; j < N_COLUMNES; ++j) {
//            Fitxa f = m_tauler.getFitxa(i, j);
//            if (f.getTipus() != TIPUS_EMPTY) {
//                int posX = POS_X_TAULER + j * MIDA_CASELLA;
//                int posY = POS_Y_TAULER + i * MIDA_CASELLA;
//                // Elige sprite según color/tipo
//                int sprite = (f.getColor() == COLOR_BLANC)
//                    ? (f.getTipus() == TIPUS_DAMA ? GRAFIC_DAMA_BLANCA : GRAFIC_FITXA_BLANCA)
//                    : (f.getTipus() == TIPUS_DAMA ? GRAFIC_DAMA_NEGRA : GRAFIC_FITXA_NEGRA);
//                GraphicManager::getInstance()->drawSprite(sprite, posX, posY);
//            }
//        }
//    }
//
//    // 3.4 Dibuja las casillas válidas si hay ficha seleccionada
//    if (m_fitxaSeleccionada) {
//        int nPosicions = 0;
//        Posicio posicionsPossibles[10];
//        m_tauler.getPosicionsPossibles(m_posicioFitxaSeleccionada, nPosicions, posicionsPossibles);
//        for (int i = 0; i < nPosicions; ++i) {
//            int posX = POS_X_TAULER + posicionsPossibles[i].getY() * MIDA_CASELLA;
//            int posY = POS_Y_TAULER + posicionsPossibles[i].getX() * MIDA_CASELLA;
//            GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
//        }
//    }
//
//    // 4. DIBUJA LA FICHA BLANCA donde esté el ratón SI está presionando (solo para debug/demostración)
//    if (mouseStatus) {
//        if (PosClick.getX() >= 0 && PosClick.getX() < N_FILES &&
//            PosClick.getY() >= 0 && PosClick.getY() < N_COLUMNES) {
//            int posX = POS_X_TAULER + PosClick.getY() * MIDA_CASELLA;
//            int posY = POS_Y_TAULER + PosClick.getX() * MIDA_CASELLA;
//            GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posX, posY);
//        }
//    }
//
//    // 5. IMPRIME TEXTO: Posición del ratón
//    std::string txt = "Posicio: fila " + std::to_string(PosClick.getX() + 1) +
//        " columna " + char('a' + PosClick.getY());
//    GraphicManager::getInstance()->drawText(txt, 50, POS_Y_TAULER + N_FILES * MIDA_CASELLA + 30);
//
//    // Devuelve si la partida ha acabado
//    return acabat;
//}





void Joc::finalitza()
{
    if (m_mode == MODE_JOC_NORMAL && haAcabat())
    {
        m_cua.guardarMoviments(m_nomArxiuMoviments);
    }
}

bool Joc::haAcabat()
{
    bool acabat = true;
    int i = 0;
    int j = 0;
    int nBlancs = 0;
    int nNegres = 0;
    bool blanc = false;
    bool negres = false;
    while (!blanc && !negres && i < N_COLUMNES)
    {
        while (!blanc && !negres && i < N_FILES)
        {
            if (m_tauler.getFitxa(i, j).getTipus() != TIPUS_EMPTY)
            {
                if (m_tauler.getFitxa(i, j).getColor() == COLOR_BLANC)
                {
                    nBlancs++;
                    if (m_tauler.getFitxa(i, j).getNPosicions() > 0)
                        blanc = true;

                }
                if (m_tauler.getFitxa(i, j).getColor() == COLOR_NEGRE)
                {
                    nNegres++;
                    if (m_tauler.getFitxa(i, j).getNPosicions() > 0)
                        negres = true;

                }
            }

        }
    }
    if (nNegres == 0)
    {
        m_guanyador = COLOR_BLANC;
        negres = true;
    }
    if (nBlancs == 0)
    {
        blanc = true;
        m_guanyador = COLOR_NEGRE;
    }

    return (negres && blanc);
}

//MOSTRAR SI ESTÀ ENCIMA EL RATON
//if ((mouseStatus) &&
//    (mousePosX >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
//    (mousePosY >= (POS_Y_TAULER + CASELLA_INICIAL_Y)) &&
//    (mousePosX <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
//    (mousePosY <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER)))
//{
//    // Calcula en qué casilla está el ratón
//    int col = (mousePosX - POS_X_TAULER - CASELLA_INICIAL_X) / AMPLADA_CASELLA;
//    int fila = (mousePosY - POS_Y_TAULER - CASELLA_INICIAL_Y) / ALCADA_CASELLA;
//
//    // Comprueba que la casilla es válida
//    if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES) {
//        Fitxa f = m_tauler.getFitxa(fila, col);
//        if (f.getTipus() != TIPUS_EMPTY) {
//            int posX = POS_X_TAULER + 52 + col * AMPLADA_CASELLA;
//            int posY = POS_Y_TAULER + 66 + fila * ALCADA_CASELLA;
//            f.visualitza(posX, posY);
//        }
//    }
//}