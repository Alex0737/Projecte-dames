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

    int mode;
    do
    {
        std::cout << "quin mode vols jugar:" << endl;
        std::cout << "  1. Mode normal" << endl;
        std::cout << "  2. Mode replay" << endl;

        
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
        }
    } while (mode != 1 && mode != 2);

    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

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

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !joc.getFinalPartida());
    // Sortim del bucle si pressionem ESC

    joc.guardaPartida("moviments.txt");

    do
    {

        if (!joc.getFinalPartida() && !primera)
        {
            cout << endl;
            cout << "guanyador: " << joc.getColorGuanyador() << endl;
            cout << "presiona esc per finalitzar tancar la finestra" << endl;

        }
        primera = true;

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
    
    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}