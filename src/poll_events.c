#include "poll_events.h"

int pollEvents(MainMenu* menu, SDL_Event* event, int* state){
    int running = 1;
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT)
            running = 0;  
            *state = 2;

        if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_RETURN) {
                MenuAction action = Menu_GetSelectedAction(menu);
                switch(action) {
                    case MENU_PLAY:
                        printf("Lancement du jeu !\n");
                        running = 0;
                        *state = 1;
                        break;
                    case MENU_SETTINGS:
                        printf("Ouverture des settings\n");
                        break;
                    case MENU_QUIT:
                        printf("Fermeture du jeu !\n");
                        running = 0;
                        *state = 2;
                        break;
                }
            }
    }
    //printf("running: %d\n", running);
    return running, state;
}