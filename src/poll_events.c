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
                    /*InGameMenuAction action = getSelectedActionInGameMenu(menu);
                    switch(action) {
                        case SHOP:
                            //enter sub-menu shop
                            break;
                        case INVENTORY:
                            //enter sub-menu inventory
                            break;
                        case WORLD:
                            //enter sub-menu world
                            break;
                        case UPGRADES:
                            //enter sub-menu upgrades
                            break;
                        case WIP:
                            //enter sub-menu wip
                            break;
                        case INGAME_PLAY:
                            *state = STATE_GAME_PLAY;
                            break;
                        case INGAME_BACK:
                            //get out of a sub menu
                            break;
                        case INGAME_QUIT:
                            running = 0;
                            *state = STATE_QUIT;
                            break;
                    }*/
                    break;                    
                case SDLK_ESCAPE:
                    running = 0;
                    *state = STATE_MAIN_MENU;
                    break;
                case SDLK_LEFT:
                    menu->selected_tab = (menu->selected_tab - 1 + menu->button_count) % menu->button_count;
                    break;
                case SDLK_RIGHT:
                    menu->selected_tab = (menu->selected_tab + 1) % menu->button_count;
                    break;
            }
        }
    }    
    return running;
}