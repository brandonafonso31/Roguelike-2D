#include "poll_events.h"

int pollEventsMenu(MainMenu* menu, SDL_Event* event, GameState* state){
    int running = 1;
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            running = 0;  
            *state = 3;
        }

        if (event->type == SDL_KEYDOWN){
            switch (event->key.keysym.sym) {
                case SDLK_RETURN:
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
                            // openSettingsEdit()
                            break;
                        case MENU_QUIT:
                            printf("Fermeture du jeu !\n");
                            running = 0;
                            *state = STATE_QUIT;
                            break;
                    }
                    break;

                case SDLK_UP:
                    menu->selected_index = (menu->selected_index - 1 + menu->button_count) % menu->button_count;
                    break;
                case SDLK_DOWN:
                    menu->selected_index = (menu->selected_index + 1) % menu->button_count;
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
                    break;                    
                case SDLK_ESCAPE:
                    running = 0;
                    *state = STATE_MAIN_MENU;
                    break;
                case SDLK_LEFT:
                    printf("%d", menu->selected_tab);
                    menu->selected_tab = (menu->selected_tab - 1 + menu->button_count) % menu->button_count;
                    break;
                case SDLK_RIGHT:
                    printf("%d", menu->selected_tab);
                    menu->selected_tab = (menu->selected_tab + 1) % menu->button_count;
                    break;
            }
        }
    }    
    return running;
}