#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "drawing_function.c"


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define FPS 30
#define FPS_HISTORY 30

//--------------------- Gestion FPS ---------------------//
typedef struct {
    double history[FPS_HISTORY];
    int index;
} FPSCounter;

void FPSCounter_Init(FPSCounter* counter) {
    for (int i = 0; i < FPS_HISTORY; i++) counter->history[i] = 1.0 / FPS; // init à 165 FPS
    counter->index = 0;
}

int FPSCounter_Update(FPSCounter* counter, double deltaTime) {
    counter->history[counter->index] = deltaTime;
    counter->index = (counter->index + 1) % FPS_HISTORY;

    double sum = 0;
    for (int i = 0; i < FPS_HISTORY; i++) sum += counter->history[i];
    double averageDelta = sum / FPS_HISTORY;

    return (int)(0.5 + 1.0 / averageDelta);
}

//---------------------- Dessin -----------------------//
void main_menu(SDL_Window* window, SDL_Renderer* renderer){

    int running = 1;
    Uint64 lastCounter = SDL_GetPerformanceCounter(), currentCounter;
    double delta_time;
    SDL_Event event;

    FPSCounter fpsCounter;
    FPSCounter_Init(&fpsCounter);
    char fpsText[50];

    TTF_Font* font = TTF_OpenFont("pokemon_BW2.otf", 24);
    if (!font) {
        printf("Erreur chargement police: %s\n", TTF_GetError());
        TTF_Quit();
        return;
    }

    while (running){

        currentCounter = SDL_GetPerformanceCounter();
        delta_time =(double)(currentCounter - lastCounter) /  SDL_GetPerformanceFrequency();
        lastCounter = currentCounter;

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        // Afficher FPS
        int fpsAverage = FPSCounter_Update(&fpsCounter, delta_time);
        snprintf(fpsText, sizeof(fpsText), "FPS: %d", fpsAverage);
        drawText(renderer, font, fpsText, 10, 10);

        SDL_RenderPresent(renderer);
    }

    TTF_Quit();
}

int main(int argc, char* argv[]) {

    SDL_Window* window = SDL_CreateWindow("Roguelike",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    main_menu(window, renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
