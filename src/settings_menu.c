#include "settings_menu.h"

GameState settingsMenu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings) {

    SDL_Event event;
    char font_full_path[2048];
    snprintf(font_full_path, sizeof(font_full_path), "%s/%s", getFontsPath(), settings->font);
    TTF_Font* font = TTF_OpenFont(font_full_path, 24);
    if (!font) {
        printf("Erreur chargement police : %s\n", TTF_GetError());
        return MENU_QUIT;
    }
    
    SettingsMenu* menu = settingsMenuCreate(renderer, settings);
    if (!menu) {
        printf("Erreur création du menu\n");
        return MENU_QUIT;
    }

    FPSCounter fps_counter;
    fpsCounterInit(&fps_counter, settings->fps_limit);
    double dt;
    
    int running = 1;
    GameState state = STATE_SETTINGS;
    while (running) {
        // === INPUT ===
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                state = STATE_QUIT;
            }
            
            if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = 0;
                        state = STATE_MAIN_MENU;
                        break;
                }
            }
        }
        //---------------- Delta ----------------//
        dt = fpsCounterGetDeltaTime(&fps_counter);
        //---------------- RENDER ---------------//
        renderSettingsUI(menu, &fps_counter, renderer, dt, font, settings);
        //---------------- FPS LIMIT ----------------//
        waitOrNot(&fps_counter, settings);
    }

    TTF_CloseFont(font);
    destroySettingsMenu(menu);
    return state;
}