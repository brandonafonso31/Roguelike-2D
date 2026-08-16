#include "main.h"

//---------------------- MAIN -----------------------//
int main(int argc, char* argv[]) {

    InitPaths();

    GameSettings settings;
    loadSettings(&settings);        


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }
    
    if (TTF_Init() == -1) {
        printf("Erreur TTF : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Erreur IMG_Init: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Roguelike",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        settings.width,
        settings.height,
        settings.fullscreen ? SDL_WINDOW_FULLSCREEN : 0
    );

    if (!window) {
        printf("Erreur fenêtre : %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    Uint32 renderer_flags = SDL_RENDERER_ACCELERATED;
    if (settings.vsync) {
        renderer_flags |= SDL_RENDERER_PRESENTVSYNC;
        printf("VSYNC active\n");
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, renderer_flags);

    if (!renderer) {
        printf("Erreur renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    char icon_path[2048];
    snprintf(icon_path, sizeof(icon_path), "%s/%s", getSystemPath(), "icon.png");
    SDL_Surface* icon = IMG_Load(icon_path);
    if (!icon) {
        printf("Erreur chargement icône: %s\n", IMG_GetError());
    } else {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }


    GameState current_state = STATE_MAIN_MENU;
    int running = 1;
    
    while (running) {
        switch (current_state) {
            case STATE_MAIN_MENU:
                current_state = mainMenu(window, renderer, &settings);
                break;
                
            case STATE_INGAME_MENU:
                current_state = inGameMenu(window, renderer, &settings);
                break;
                
            case STATE_GAME_PLAY:
                //current_state = gamePlay(window, renderer, &settings);
                current_state = STATE_MAIN_MENU;
                break;
                
            case STATE_SETTINGS:
                //current_state = settingsMenu(window, renderer, &settings);
                break;
                
            case STATE_QUIT:
                printf("Fermeture du jeu !\n");
                running = 0;    
                break;
                
            default:    
                printf("État inconnu !\n");
                running = 0;
                break;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}