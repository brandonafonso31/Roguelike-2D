#include "ui.h"

#define nb_options 4

const char* txt_main_menu[nb_options] = {"New Game",
                            "Load Game",
                            "Options",
                            "Quit"};

static void renderFps(FPSCounter* fps_counter, SDL_Renderer* renderer, TTF_Font* font, GameSettings* settings, double dt) {
    char fps_text[50];
    int average_fps = fpsCounterUpdate(fps_counter, dt);
    int target_fps = settings->vsync ? getMonitorRefreshRate() : settings->fps_limit;
    snprintf(fps_text, sizeof(fps_text), "FPS: %d (target: %d)", average_fps, target_fps);
    drawTextWhite(renderer, font, fps_text, 10, 10);
}

void renderMainMenuUI(MainMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    int height = settings->height;
    int width = settings->width;

    renderScaledImageOrigin(renderer, menu->background, width, height);

    renderFps(fps_counter, renderer, font, settings, dt);

    int i = 0;
    while(i++, i <= nb_options){
        drawTextWhite(renderer, font, txt_main_menu[i-1], (width-150), height-50*(nb_options+1-i));
    }  

    if (menu->selected_index != -1)
        renderImage(renderer,menu->cursor, (width-210), height-50*(nb_options-menu->selected_index));

    SDL_RenderPresent(renderer);
}

void renderUI(FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Afficher les FPS
    renderFps(fps_counter, renderer, font, settings, dt);
    //render_hp
    //render_mana
    //render_inventorys
    // Présenter le rendu
    SDL_RenderPresent(renderer);
}