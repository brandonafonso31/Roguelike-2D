#include "main.h"

//---------------------- MAIN -----------------------//
int main(int argc, char* argv[]) {

    InitPaths();

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

    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED;
    if (settings.vsync) {
        renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
        printf("VSYNC active\n");
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, renderer_flags);

    if (!renderer) {
        printf("Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    mainMenu(window, renderer, &settings);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
    return 0;
}