#include "ingame_menu.h"

void ingameMenu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings) {

    int running = 1;
    SDL_Event event;
    char font_full_path[2048];
    snprintf(font_full_path, sizeof(font_full_path), "%s/%s", getFontsPath(), settings->font);
    TTF_Font* font = TTF_OpenFont(font_full_path, 24);

    InGameMenu* menu = menuCreate(renderer, settings);
    if (!menu) {
        printf("Erreur création du menu\n");
        return;
    }

    FPSCounter fps_counter;
    fpsCounterInit(&fps_counter, settings->fps_limit);
    double dt;
    int state = 0;
    while (running) {
        //---------------- INPUT ----------------//
        running = pollEventsMenu(menu, &event, &state); 
        //---------------- Delta ----------------//
        dt = fpsCounterGetDeltaTime(&fps_counter);
        //---------------- RENDER ---------------//
        renderMainMenuUI(menu, &fps_counter, renderer, dt, font, settings);
        //---------------- FPS LIMIT ----------------//
        waitOrNot(&fps_counter, settings);
    }

}