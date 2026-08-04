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
    TTF_Font* font = TTF_OpenFont("pokemon_BW2.otf", 24);
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
            // En vsync, on attend le prochain vsync (géré par SDL_RenderPresent)
            // Mais on peut ajouter une petite pause si besoin
            SDL_Delay(1); // Petit délai pour éviter de surcharger le CPU
        }
    }

    TTF_CloseFont(font);
}

//---------------------- MAIN -----------------------//
int main(int argc, char* argv[]) {

    InitPaths();
    char font_path[2048];
    snprintf(font_path, sizeof(font_path), "%s/fonts/pokemon_BW2.otf", GetAssetsPath());

    GameSettings settings;
    loadSettings(&settings);        


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }
    
    if (TTF_Init() == -1) {
        printf("Erreur TTF : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Roguelike",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        settings.width,
        settings.height,
        settings.fullscreen ? SDL_WINDOW_FULLSCREEN : 0
    );

    if (!window) {
        printf("Erreur fenêtre : %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
    if (settings.vsync) {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
        printf("VSYNC active\n");
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    if (!renderer) {
        printf("Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    main_menu(window, renderer, &settings);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}