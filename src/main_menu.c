#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#include "main_menu.h"
#include "drawing_function.h"
#include "settings.h"
#include "fps_utils.h"
#include "paths.h"
#include "poll_events.h"
#include "ui.h"

//---------------------- Boucle jeu -----------------------//

void main_menu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings) {


    int running = 1;
    SDL_Event event;
    char font_full_path[2048];
    snprintf(font_full_path, sizeof(font_full_path), "%s/%s", GetFontPath(), settings->font);
    TTF_Font* font = TTF_OpenFont(font_full_path, 24);
    if (!font) {
        printf("Erreur chargement police : %s\n", TTF_GetError());
        return;
    }

    FPSCounter fps_counter;
    FPSCounter_Init(&fps_counter, settings->fps_limit);
    double delta_time;

    while (running) {
        //---------------- INPUT ----------------//
        running = poll_events(&event);
        //---------------- Delta ----------------//
        delta_time = FPSCounter_GetDeltaTime(&fps_counter);
        //---------------- RENDER ---------------//
        render_ui(&fps_counter, renderer, delta_time, font, settings);
        //---------------- FPS LIMIT ----------------//
        if (!settings->vsync) {
            FPSCounter_WaitForNextFrame(&fps_counter);
        } else {
            SDL_Delay(1); // Petit délai pour éviter de surcharger le CPU
        }
    }

    TTF_CloseFont(font);
}