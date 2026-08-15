#include "ui.h"

#define nb_options 4

const char* txt_main_menu[nb_options] = {"New Game",
                            "Load Game",
                            "Options",
                            "Quit"};

static void render_fps(FPSCounter* fps_counter, SDL_Renderer* renderer, TTF_Font* font, GameSettings* settings, double dt) {
    char fps_text[50];
    int average_fps = FPSCounter_Update(fps_counter, dt);
    int target_fps = settings->vsync ? GetMonitorRefreshRate() : settings->fps_limit;
    snprintf(fps_text, sizeof(fps_text), "FPS: %d (target: %d)", average_fps, target_fps);
    drawText(renderer, font, fps_text, 10, 10);
}

void render_main_menu_ui(FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    int height = settings->height;
    int width = settings->width;

    Image* backgound = LoadImage(renderer,"chamber.jpg");
    RenderScaledImageOrigin(renderer, backgound, width, height);

    render_fps(fps_counter, renderer, font, settings, dt);

    int i = 0;
    while(i++, i <= nb_options){
        drawText(renderer, font, txt_main_menu[i-1], (width-150), height-50*(nb_options+1-i));
    }  
    
    SDL_RenderPresent(renderer);
}

void render_ui(FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Afficher les FPS
    render_fps(fps_counter, renderer, font, settings, dt);
    //render_hp
    //render_mana
    //render_inventorys
    // Présenter le rendu
    SDL_RenderPresent(renderer);
}