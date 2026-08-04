#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define FPS 30

void main_menu(SDL_Window* window, SDL_Renderer* renderer){

    int running = 1, current_time = 0;
    Uint64 lastCounter = SDL_GetPerformanceCounter(), currentCounter;
    double delta_time;
    SDL_Event event;

    while (running){

        currentCounter = SDL_GetPerformanceCounter();
        delta_time =(double)(currentCounter - lastCounter) /  SDL_GetPerformanceFrequency();
        lastCounter = currentCounter;

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
                running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

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
