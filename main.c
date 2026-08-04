#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "drawing_function.h"
#include "settings.h"

#define FPS_HISTORY 30

//--------------------- Gestion FPS ---------------------//

int GetMonitorRefreshRate() {
    SDL_DisplayMode mode;
    if (SDL_GetCurrentDisplayMode(0, &mode) == 0) {
        return mode.refresh_rate;
    }
    return -1; // Valeur par défaut si on ne peut pas récupérer
}

typedef struct {
    double history[FPS_HISTORY];
    int index;
    double targetFrameTime;
    Uint64 lastFrameTime;
} FPSCounter;

void FPSCounter_Init(FPSCounter* counter, int fps_limit) {
    counter->targetFrameTime = 1.0 / fps_limit;
    for (int i = 0; i < FPS_HISTORY; i++)
        counter->history[i] = counter->targetFrameTime;
    counter->index = 0;
    counter->lastFrameTime = 0;
}

double FPSCounter_GetDeltaTime(FPSCounter* counter) {
    Uint64 currentTime = SDL_GetPerformanceCounter();
    double deltaTime;
    
    if (counter->lastFrameTime == 0) {
        deltaTime = counter->targetFrameTime; // Premier frame
    } else {
        deltaTime = (double)(currentTime - counter->lastFrameTime) / SDL_GetPerformanceFrequency();
        // Limiter le deltaTime pour éviter les sauts trop grands (ex: après une pause)
        if (deltaTime > 0.1) deltaTime = counter->targetFrameTime;
    }
    
    counter->lastFrameTime = currentTime;
    return deltaTime;
}

int FPSCounter_Update(FPSCounter* counter, double deltaTime) {
    counter->history[counter->index] = deltaTime;
    counter->index = (counter->index + 1) % FPS_HISTORY;
    
    double sum = 0;
    for (int i = 0; i < FPS_HISTORY; i++)
        sum += counter->history[i];
    
    double averageDelta = sum / FPS_HISTORY;
    return (int)(0.5 + 1.0 / averageDelta);
}

void FPSCounter_WaitForNextFrame(FPSCounter* counter) {
    if (counter->targetFrameTime <= 0) return;
    
    Uint64 currentTime = SDL_GetPerformanceCounter();
    double elapsed = (double)(currentTime - counter->lastFrameTime) / SDL_GetPerformanceFrequency();
    
    if (elapsed < counter->targetFrameTime) {
        Uint32 waitMs = (Uint32)((counter->targetFrameTime - elapsed) * 1000);
        if (waitMs > 1) {
            SDL_Delay(waitMs - 1); // -1 pour éviter de dépasser
        }
        
        while (elapsed < counter->targetFrameTime) {
            currentTime = SDL_GetPerformanceCounter();
            elapsed = (double)(currentTime - counter->lastFrameTime) / SDL_GetPerformanceFrequency();
        }
    }
}

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