#include "ui.h"

static void render_fps(FPSCounter* fps_counter, SDL_Renderer* renderer, TTF_Font* font, GameSettings* settings, double delta_time) {
    char fpsText[50];
    int fpsAverage = FPSCounter_Update(fps_counter, delta_time);
    int target_fps = settings->vsync ? GetMonitorRefreshRate() : settings->fps_limit;
    snprintf(fpsText, sizeof(fpsText), "FPS: %d (target: %d)", fpsAverage, target_fps);
    drawText(renderer, font, fpsText, 10, 10);
}

void render_ui(FPSCounter* fps_counter, SDL_Renderer* renderer, double delta_time, TTF_Font* font, GameSettings* settings) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Afficher les FPS
    render_fps(fps_counter, renderer, font, settings, delta_time);
    
    // Présenter le rendu
    SDL_RenderPresent(renderer);
}