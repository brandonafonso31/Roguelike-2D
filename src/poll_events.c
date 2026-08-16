#include "poll_events.h"

int pollEventsMenu(MainMenu* menu, SDL_Event* event, GameState* state){
    int running = 1;
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            running = 0;  
            *state = 3;
        }

        if (event->type == SDL_KEYDOWN){
            if (event->key.keysym.sym == SDLK_RETURN) {
                MainMenuAction action = getSelectedActionMenu(menu);
                switch(action) {
                    case MENU_NEW_GAME:
                        printf("Lancement du jeu !\n");
                        running = 0;
                        *state = STATE_INGAME_MENU;
                        break;
                    case MENU_LOAD_GAME:
                        printf("Chargement du jeu !\n");
                        running = 0;
                        *state = STATE_INGAME_MENU;
                        break;
                    case MENU_SETTINGS:
                        printf("Ouverture des settings\n");
                        break;
                    case MENU_QUIT:
                        printf("Fermeture du jeu !\n");
                        running = 0;
                        *state = STATE_QUIT;
                        break;
                }
            }

            switch(event->key.keysym.sym) {
                case SDLK_UP:
                    menu->selected_index = (menu->selected_index - 1 + menu->button_count) % menu->button_count;
                    break;
                case SDLK_DOWN:
                    menu->selected_index = (menu->selected_index + 1) % menu->button_count;
                    break;
                case SDLK_RETURN:
                case SDLK_SPACE:
                    menu->selected_index = 1;
                    break;
            }
        }
    }
    //printf("running: %d\n", running);
    return running;
}

int pollEventsInGameMenu(InGameMenu* menu, SDL_Event* event, GameState* state) {
    int running = 1;
    
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            running = 0;
            *state = STATE_QUIT;
        }
        
        if (event->type == SDL_KEYDOWN) {
            switch(event->key.keysym.sym) {
                case SDLK_RETURN:
                    InGameMenuAction action = getSelectedActionInGameMenu(menu);
                    switch(action) {
                        case INGAME_PLAY:
                            running = 0;
                            *state = STATE_GAME_PLAY;
                            break;
                        case INGAME_BACK:
                            running = 0;
                            *state = STATE_MAIN_MENU;
                            break;
                        case INGAME_QUIT:
                            running = 0;
                            *state = STATE_QUIT;
                            break;
                    }
                    break;
                    
                case SDLK_ESCAPE:
                    running = 0;
                    *state = STATE_MAIN_MENU;
                    break;
            }
        }
    }    
    return running;
}