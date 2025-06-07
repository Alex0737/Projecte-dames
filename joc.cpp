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
    if(m_mode == MODE_JOC_NORMAL)
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
        if(!mouseStatus && lastMouseStatus && !m_finalPartida)
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
    for(int i = 0; i < N_FILES; i++)
    {
        for(int j = 0; j < N_COLUMNES; j++)
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
    if(fitxer.is_open())
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





//bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
//{
//    if (m_jugadorTorn == COLOR_BLANC)
//    {
//        m_jugadorTorn = COLOR_NEGRE;
//    }
//    else
//    {
//        m_jugadorTorn = COLOR_BLANC;
//    }
//    if (!iniciat)
//    {
//        m_tauler.inicialitza("tauler_inicial.txt");
//        iniciat = true;
//        // 1. Dibuja el fondo
//    }
//
//    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
//
//    // 2. Dibuja el tablero
//    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER - 52, POS_Y_TAULER - 66);
//
//    // 3. Dibuja todas las fichas en su posición (sin interacción, solo tablero inicial)
//
//    for (int fila = 0; fila < N_FILES; ++fila)
//    {
//        for (int col = 0; col < N_COLUMNES; ++col)
//        {
//            Fitxa f = m_tauler.getFitxa(fila, col);
//            if (f.getTipus() != TIPUS_EMPTY)
//            {
//
//                int posX = POS_X_TAULER + col * AMPLADA_CASELLA;
//                int posY = POS_Y_TAULER + fila * ALCADA_CASELLA;
//                f.visualitza(posX, posY);
//
//            }
//        }
//    }
//
//    if (m_fitxaSeleccionada) 
//    {
//        for (const Posicio& p : m_posicionsValides) 
//        {
//            int posX = POS_X_TAULER + p.getY() * AMPLADA_CASELLA;
//            int posY = POS_Y_TAULER + p.getX() * ALCADA_CASELLA;
//            GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
//        }
//    }
//
//    if (mouseStatus) {
//        int col = (mousePosX - POS_X_TAULER) / AMPLADA_CASELLA;
//        int fila = (mousePosY - POS_Y_TAULER) / ALCADA_CASELLA;
//
//        if (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES)
//        {
//            Fitxa f = m_tauler.getFitxa(fila, col);
//            if (f.getTipus() != TIPUS_EMPTY && f.getColor() == m_jugadorTorn)
//            {
//                m_fitxaSeleccionada = true;
//                m_posFitxaSeleccionada = Posicio(fila, col);
//
//                // Ahora SÍ puedes llamar a getPosicionsPossibles:
//                m_posicionsValides.clear();
//                Posicio posicionsPossibles[20];
//                m_tauler.getPosicionsPossibles(m_posFitxaSeleccionada, m_nPosicionsValides, posicionsPossibles);
//
//                for (int i = 0; i < m_nPosicionsValides; ++i)
//                    m_posicionsValides.push_back(posicionsPossibles[i]);
//
//            }
//            std::cout << m_posFitxaSeleccionada.getX() << m_posFitxaSeleccionada.getY();
//
//        }
//    }
//
//    //if (m_fitxaSeleccionada)
//    //{
//    //    Posicio posicionsPossibles[20];
//    //    m_tauler.getPosicionsPossibles(m_posFitxaSeleccionada, m_nPosicionsValides, posicionsPossibles);
//    //    for (int i= 0; i < m_nPosicionsValides; i++)
//    //    {
//    //        m_posicionsValides.push_back(posicionsPossibles[i]);
//    //    }
//    //}
//
//    // 4. Puedes mostrar la posición del ratón debajo del tablero (opcional)
//    int posTextX = POS_X_TAULER;
//    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * N_FILES) + 120;
//    std::string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
//    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, msg);
//
//    // 5. No hace nada más, solo muestra el tablero y las fichas iniciales
//
//    return false;
//}



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

