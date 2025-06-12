//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
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
        std::cout << "quin mode vols jugar:" << endl;
        std::cout << "  1. Mode normal" << endl;
        std::cout << "  2. Mode replay" << endl;
        std::cout << "  3. Mode un jugador" << endl;


        cin >> mode;
        if (mode == 1)
        {
            joc.setMode(MODE_JOC_NORMAL);
        }
        else
        {
            if (mode == 2)
            {
                joc.setMode(MODE_JOC_REPLAY);
            }
            else
            {
                if (mode == 3)
                {
                    joc.setMode(MODE_JOC_UN);
                }
            }
        }
    } while (mode != 1 && mode != 2 && mode != 3);

    int inici;
    if (joc.getMode() == MODE_JOC_NORMAL || joc.getMode() == MODE_JOC_UN)
    {
        do
        {
            std::cout << "Vols jugar amb tauler original o amb un tauler diferent?" << endl;
            std::cout << "  1. Original" << endl;
            std::cout << "  2. Diferent" << endl;
            cin >> inici;
        } while (inici != 1 && inici != 2);
        if (inici == 1)
        {
            joc.setTaulerInici("tauler_inicial.txt");
        }
        else
        {
            if (inici == 2)
                joc.setTaulerInici("opcional.txt");
        }
    }
    else
    {
        if (joc.getMode() == MODE_JOC_REPLAY)
            joc.setTaulerInici("tauler_inicial.txt");

    }

    joc.setTaulerMoviments("moviments.txt");

    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    bool guardar = true;
    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(TAMANY_PANTALLA_X, TAMANY_PANTALLA_Y);
    //Mostrem la finestra grafica
    pantalla.show();
    bool primera = false;
    do
    {

        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents();

        bool mouseStatus = Mouse_getBtnLeft();
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();
        bool final = joc.actualitza(mousePosX, mousePosY, mouseStatus);

        // Actualitza la pantalla
        pantalla.update();
        if (joc.getFinalPartida() && !primer)
        {
            primer = true;
            cout << "Ha acabat la partida" << endl;
            if (joc.getColorGuanyador() == COLOR_BLANC)
                cout << "guanyador: " << "Color Blanc" << endl;
            else
            {
                if (joc.getColorGuanyador() == COLOR_NEGRE)
                    cout << "guanyador: " << "Color Negre" << endl;
                else
                {
                    cout << "no hi ha guanyador" << endl;
                }
            }
            if (joc.getMode() == MODE_JOC_REPLAY|| (joc.getMode() == MODE_JOC_NORMAL && inici == 2)|| joc.getMode() == MODE_JOC_UN && inici == 2)
            {
                guardar = false;
                std::cout << "No es pot guardar la partida en aquest mode :(" << endl;
            }

            cout << "presiona esc per finalitzar tancar la finestra" << endl;

        }

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
    // Sortim del bucle si pressionem ESC


    int decisio;
    if ((joc.getMode() == MODE_JOC_NORMAL || joc.getMode() == MODE_JOC_UN) && guardar)
    {
        do
        {
            std::cout << "Vols guardar la partida en un arxiu de text?" << endl;
            std::cout << "  1. Si" << endl;
            std::cout << "  2. No" << endl;
            cin >> decisio;
        } while (decisio != 1 && decisio != 2);
        if (decisio == 1)
        {
            joc.guardaPartida("moviments.txt");
        }
    }
    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}