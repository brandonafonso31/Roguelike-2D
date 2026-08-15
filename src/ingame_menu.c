#include "ingame_menu.h"

void ingameMenu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings) {

    int running = 1;
    char font_full_path[2048];
    snprintf(font_full_path, sizeof(font_full_path), "%s/%s", getFontsPath(), settings->font);
    TTF_Font* font = TTF_OpenFont(font_full_path, 24);

    while (running) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        drawTextWhite(renderer, font, "In Game Menu", 200, 200);
        SDL_RenderPresent(renderer);
    }

}