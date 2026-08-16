#include "main_menu.h"

GameState mainMenu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings) {

    SDL_Event event;
    char font_full_path[2048];
    snprintf(font_full_path, sizeof(font_full_path), "%s/%s", getFontsPath(), settings->font);
    TTF_Font* font = TTF_OpenFont(font_full_path, 24);
    if (!font) {
        printf("Erreur chargement police : %s\n", TTF_GetError());
        return MENU_QUIT;
    }
    
    MainMenu* menu = menuCreate(renderer, settings);
    if (!menu) {
        printf("Erreur création du menu\n");
        return MENU_QUIT;
    }

    FPSCounter fps_counter;
    fpsCounterInit(&fps_counter, settings->fps_limit);
    double dt;
    
    int running = 1;
    GameState state = STATE_MAIN_MENU;
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

    TTF_CloseFont(font);
    destroyMenu(menu);
    return state;
}