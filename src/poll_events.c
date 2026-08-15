#include "poll_events.h"

int pollEventsMenu(MainMenu* menu, SDL_Event* event, int* state){
    int running = 1;
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            running = 0;  
            *state = 3;
        }

        if (event->type == SDL_KEYDOWN){
            if (event->key.keysym.sym == SDLK_RETURN) {
                MenuAction action = getSelectedActionMenu(menu);
                switch(action) {
                    case MENU_NEW_GAME:
                        printf("Lancement du jeu !\n");
                        running = 0;
                        *state = 1;
                        break;
                    case MENU_LOAD_GAME:
                        printf("Chargement du jeu !\n");
                        running = 0;
                        *state = 2;
                        break;
                    case MENU_SETTINGS:
                        printf("Ouverture des settings\n");
                        break;
                    case MENU_QUIT:
                        printf("Fermeture du jeu !\n");
                        running = 0;
                        *state = 3;
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