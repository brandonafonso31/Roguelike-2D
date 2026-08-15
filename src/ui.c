#include "ui.h"

static void render_fps(FPSCounter* fps_counter, SDL_Renderer* renderer, TTF_Font* font, GameSettings* settings, double dt) {
    char fpsText[50];
    int average_fps = FPSCounter_Update(fps_counter, dt);
    int target_fps = settings->vsync ? GetMonitorRefreshRate() : settings->fps_limit;
    snprintf(fpsText, sizeof(fpsText), "FPS: %d (target: %d)", average_fps, target_fps);
    drawText(renderer, font, fpsText, 10, 10);
}

void render_ui(FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    // Afficher les FPS
    render_fps(fps_counter, renderer, font, settings, dt);
    
    // Présenter le rendu
    SDL_RenderPresent(renderer);
}