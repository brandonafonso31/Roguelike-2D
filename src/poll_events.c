#include "poll_events.h"

int pollEventsMenu(MainMenu* menu, SDL_Event* event, GameState* state){
    int running = 1;
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            running = 0;  
            *state = MENU_QUIT;
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
                            running = 0;
                            *state = STATE_SETTINGS;
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

    int* selected = &menu->selected_tab;
    int* last = &menu->last_tab_id;
    int nb = menu->nb_tabs;
    
    const int TAB_PLAY = nb;      // Bouton PLAY (5)
    const int TAB_RETURN = nb + 1;    // Bouton RETOUR au menu principal (6)
    
    int running = 1;
    int is_on_special = (*selected == TAB_PLAY || *selected == TAB_RETURN);
    
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            running = 0;
            *state = STATE_QUIT;
        }
        
        if (event->type == SDL_KEYDOWN) {
            switch(event->key.keysym.sym) {
                case SDLK_RETURN:
                    if (*selected == TAB_PLAY) {
                        running = 0;
                        *state = STATE_GAME_PLAY;
                        printf("Lancement du jeu !\n");
                    } else if (*selected == TAB_RETURN) {
                        running = 0;
                        *state = STATE_MAIN_MENU;  
                        printf("Retour au menu principal\n");
                    }
                    break;
                    
                case SDLK_ESCAPE:
                    running = 0;
                    *state = STATE_MAIN_MENU;
                    break;
                    
                case SDLK_LEFT:
                    *last = *selected;
                    if (is_on_special) {
                        *selected = 0;
                    } else {
                        *selected = (*selected - 1 + nb) % nb;
                    }
                    printf("Onglet: %d\n", *selected);
                    break;
                    
                case SDLK_RIGHT:
                    *last = *selected;
                    if (is_on_special) {
                        *selected = nb - 1;
                    } else {
                        *selected = (*selected + 1) % nb;
                    }
                    printf("Onglet: %d\n", *selected);
                    break;

                case SDLK_UP:
                    if (!is_on_special) {
                        *last = *selected;
                        *selected = TAB_PLAY;
                    } else if (*selected == TAB_PLAY) {
                        *selected = TAB_RETURN;
                    }
                    printf("Onglet: %d\n", *selected);
                    break;

                case SDLK_DOWN:
                    if (is_on_special) {
                        if (*selected == TAB_RETURN) {
                            *selected = TAB_PLAY;
                        } else if (*selected == TAB_PLAY) {
                            *selected = *last;
                        }
                        printf("Onglet: %d\n", *selected);
                    }
                    break;
            }
        }
    }    
    return running;
}