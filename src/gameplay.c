#include "gameplay.h"

GameState gameplay(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings, Entity* player, EntityDatabase* db_entities){

    SDL_Event event;
    char font_full_path[2048];
    snprintf(font_full_path, sizeof(font_full_path), "%s/%s", getFontsPath(), settings->font);
    TTF_Font* font = TTF_OpenFont(font_full_path, 24);
    if (!font) {
        printf("Erreur chargement police : %s\n", TTF_GetError());
        return MENU_QUIT;
    }
    
    Interface* interface = interfaceInit(renderer, player);
    if (!interface) {
        printf("Erreur création interface\n");
        return MENU_QUIT;
    }

    FPSCounter fps_counter;
    fpsCounterInit(&fps_counter, settings->fps_limit);
    double dt;
    
    int running = 1;
    GameState state = STATE_GAME_PLAY;
    while (running) {
        //---------------- INPUT ----------------//
        running = pollEventsGameplay(interface, &event, &state); 
        //---------------- Delta ----------------//
        dt = fpsCounterGetDeltaTime(&fps_counter);
        //---------------- RENDER ---------------//
        renderInterfaceInGame(interface, &fps_counter, renderer, dt, font, settings, db_entities);
        //---------------- FPS LIMIT ----------------//
        waitOrNot(&fps_counter, settings);
    }

    TTF_CloseFont(font);
    destroyInterface(interface);
    return state;
}