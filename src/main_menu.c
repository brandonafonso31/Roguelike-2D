#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "drawing_function.h"
#include "settings.h"
#include "fps_utils.h"
#include "paths.h"


//---------------------- Boucle jeu -----------------------//

void main_menu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings) {


    int running = 1;
    SDL_Event event;
    char font_full_path[2048];
    snprintf(font_full_path, sizeof(font_full_path), "%s/%s", GetFontPath(), settings->font);
    TTF_Font* font = TTF_OpenFont(font_full_path, 24);
    if (!font) {
        printf("Erreur chargement police : %s\n", TTF_GetError());
        return;
    }

    FPSCounter fpsCounter;
    FPSCounter_Init(&fpsCounter, settings->fps_limit);
    char fpsText[50];
    double delta_time;

    while (running) {
        //---------------- INPUT ----------------//
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
        }

        //---------------- UPDATE ----------------//
        // Récupérer le delta_time ici pour l'utiliser dans les updates
        delta_time = FPSCounter_GetDeltaTime(&fpsCounter);

        //---------------- RENDER ----------------//
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        int fpsAverage = FPSCounter_Update(&fpsCounter, delta_time);
        snprintf(fpsText, sizeof(fpsText), "FPS: %d (target: %d)", fpsAverage, (!settings->vsync)? settings->fps_limit : GetMonitorRefreshRate());
        drawText(renderer, font, fpsText, 10, 10);

        /*printf("delta : %f FPS : %f\n", delta_time, 1.0 / delta_time);
        printf("frequency : %llu\n", SDL_GetPerformanceFrequency());*/

        SDL_RenderPresent(renderer);

        //---------------- FPS LIMIT ----------------//
        if (!settings->vsync) {
            FPSCounter_WaitForNextFrame(&fpsCounter);
        } else {
            SDL_Delay(1); // Petit délai pour éviter de surcharger le CPU
        }
    }

    TTF_CloseFont(font);
}