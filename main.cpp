//
//  main.cpp
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined(_WIN64)

#include <iostream>
#define SDL_MAIN_HANDLED
#include <windows.h>
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include "GraphicManager.h"
#include <conio.h>

#elif __APPLE__
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop
#endif

#include "./joc.hpp"
#include "./info_joc.hpp"

int main(int argc, const char* argv[])
{
    Joc joc;
    bool primer = false;

    int mode;
    do
    {
        std::cout << "quin mode vols jugar:" << std::endl;
        std::cout << "  1. Mode normal" << std::endl;
        std::cout << "  2. Mode replay" << std::endl;
        std::cout << "  3. Mode un jugador" << std::endl;
        std::cin >> mode;
        if (mode == 1) joc.setMode(MODE_JOC_NORMAL);
        else if (mode == 2) joc.setMode(MODE_JOC_REPLAY);
        else if (mode == 3) joc.setMode(MODE_JOC_UN);
    } while (mode != 1 && mode != 2 && mode != 3);

    int inici = 0;
    if (joc.getMode() == MODE_JOC_NORMAL || joc.getMode() == MODE_JOC_UN)
    {
        do
        {
            std::cout << "Vols jugar amb tauler original o amb un tauler diferent?" << std::endl;
            std::cout << "  1. Original" << std::endl;
            std::cout << "  2. Diferent" << std::endl;
            std::cin >> inici;
        } while (inici != 1 && inici != 2);

        if (inici == 1)
        {
            joc.setTaulerInici("tauler_inicial.txt");
        }
        else
        {
            joc.setTaulerInici("opcional.txt");
        }
    }
    else
    {
        joc.setTaulerInici("tauler_inicial.txt");
    }
    joc.setTaulerMoviments("moviments.txt");

    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    Screen pantalla(TAMANY_PANTALLA_X, TAMANY_PANTALLA_Y);
    pantalla.show();

    bool continua = true;
    bool preguntar = false;
    bool guardar = false;

    while (continua)
    {
        pantalla.processEvents();

        if (Keyboard_GetKeyTrg(KEYBOARD_ESCAPE))
        {
            continua = false;
        }

        if (continua)
        {
            bool mouseStatus = Mouse_getBtnLeft();
            int  mousePosX = Mouse_getX();
            int  mousePosY = Mouse_getY();

            bool final = joc.actualitza(mousePosX, mousePosY, mouseStatus);

            if (joc.getFinalPartida() && !primer)
            {
                primer = true;
                std::cout << "Ha acabat la partida" << std::endl;
                if (joc.getColorGuanyador() == COLOR_BLANC)
                    std::cout << "guanyador: Color Blanc" << std::endl;
                else 
                {
                    if (joc.getColorGuanyador() == COLOR_NEGRE)
                        std::cout << "guanyador: Color Negre" << std::endl;
                    else
                        std::cout << "no hi ha guanyador" << std::endl;
                }

                preguntar = true;
            }

            if (preguntar && joc.getMode() != MODE_JOC_REPLAY && inici == 1)
            {
                float px = 50.0f, py = 630.0f;
                GraphicManager::getInstance()
                    ->drawFont(FONT_WHITE_30, px, py, 0.8f, "Vols guardar partida? (Si: 1 / No: 2 o Esc)");

                if (Keyboard_GetKeyTrg('1'))
                {
                    guardar = true;
                    continua = false;
                }
                else if (Keyboard_GetKeyTrg('2'))
                {
                    guardar = false;
                    continua = false;
                }
            }

            pantalla.update();
        }
    }

    if (guardar && (joc.getMode() == MODE_JOC_NORMAL || joc.getMode() == MODE_JOC_UN))
    {
        joc.guardaPartida("moviments.txt");
    }

    SDL_Quit();
    return 0;
}