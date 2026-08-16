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
    // Presenter le rendu
    SDL_RenderPresent(renderer);
}

void renderInGameMenuUI(InGameMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings) {
    int width = settings->width;
    int height = settings->height;
    
    // Fond
    renderScaledImageOrigin(renderer, menu->background, width, height);
    
    // Inside Tab ===
    switch(menu->selected_tab) {
        case 0: // Shop
            renderShopTab(renderer, font, width, height, dt);
            break;
        case 1: // Inventaire
            renderInventoryTab(renderer, font, width, height, dt);
            break;
        case 2: // Monde
            renderWorldTab(renderer, font, width, height, dt);
            break;
        case 3: // Upgrades
            renderUpgradesTab(renderer, font, width, height, dt);
            break;
        case 4: // En travaux
            renderWipTab(renderer, font, width, height, dt);
            break;
    }
    
    // TAB : Shop, Inventaire, Monde, Upgrades, En travaux
    const char* tabs[] = {"Shop", "Inventaire", "Monde", "Upgrades", "En travaux"};
    int tab_count = 5;
    int tab_height = 50;
    int tab_width = width / tab_count;
    int y_offset = height - tab_height;
    
    for (int i = 0; i < tab_count; i++) {
        int x = i * tab_width;
        SDL_Rect tab_rect = {x, y_offset, tab_width, tab_height};
        
        // Fond de l'onglet
        if (i == menu->selected_tab) {
            // Animation de pulsation pour l'onglet selectionne
            float pulse = 0.8 + 0.2 * sin(dt * 2.0);
            SDL_SetRenderDrawColor(renderer, 
                60 * pulse, 60 * pulse, 120 * pulse, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 30, 30, 50, 200);
        }
        SDL_RenderFillRect(renderer, &tab_rect);
        
        // Bordure superieure de l'onglet
        SDL_SetRenderDrawColor(renderer, 80, 80, 120, 255);
        SDL_RenderDrawLine(renderer, x, y_offset, x + tab_width, y_offset);
        
        // Bordure complete
        SDL_RenderDrawRect(renderer, &tab_rect);
        
        // Petit indicateur pour l'onglet selectionne (triangle en haut)
        if (i == menu->selected_tab) {
            SDL_SetRenderDrawColor(renderer, 100, 150, 255, 255);
            int tri_x = x + tab_width / 2;
            int tri_y = y_offset;
            for (int j = 0; j < 8; j++) {
                SDL_RenderDrawPoint(renderer, tri_x - j, tri_y - j);
                SDL_RenderDrawPoint(renderer, tri_x + j, tri_y - j);
            }
        }
        
        // Texte de l'onglet (centre)
        int text_w = strlen(tabs[i]) * 12;
        int text_x = x + (tab_width - text_w) / 2;
        int text_y = y_offset + (tab_height - 24) / 2;
        
        if (i == menu->selected_tab) {
            drawTextWhite(renderer, font, tabs[i], text_x, text_y);
        } else {
            drawTextBlack(renderer, font, tabs[i], text_x, text_y);
        }
    }
    
    // === FPS en haut à droite ===
    renderFps(fps_counter, renderer, font, settings, dt);
    
    // === BOUTON RETOUR en haut à droite ===
    int btn_w = 100;
    int btn_h = 35;
    int btn_x = width - btn_w - 20;
    int btn_y = 20;
    
    float pulse = 0.9 + 0.1 * sin(dt * 1.5);
    SDL_SetRenderDrawColor(renderer, 
        60 * pulse, 50 * pulse, 50 * pulse, 255);
    SDL_Rect btn_rect = {btn_x, btn_y, btn_w, btn_h};
    SDL_RenderFillRect(renderer, &btn_rect);
    SDL_SetRenderDrawColor(renderer, 150, 80, 80, 255);
    SDL_RenderDrawRect(renderer, &btn_rect);
    
    drawTextWhite(renderer, font, "Retour", btn_x + 15, btn_y + 8);
    
    SDL_RenderPresent(renderer);
}

void renderWorldTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt) {
    drawTextWhite(renderer, font, "MONDE", 50, 80);
    drawTextBlack(renderer, font, "Explorez le monde et partez à l'aventure !", 50, 120);
}

void renderInventoryTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt) {
    drawTextWhite(renderer, font, "INVENTAIRE", 50, 80);
    drawTextBlack(renderer, font, "Vos objets et equipements", 50, 120);
}

void renderShopTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt) {
    drawTextWhite(renderer, font, "SHOP", 50, 80);
    drawTextBlack(renderer, font, "Achetez des objets pour vos aventures !", 50, 120);
}

void renderUpgradesTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt) {
    drawTextWhite(renderer, font, "UPGRADES", 50, 80);
    drawTextBlack(renderer, font, "Ameliorez votre personnage !", 50, 120);
}

void renderWipTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt) {
    drawTextWhite(renderer, font, "EN TRAVAUX", width/2 - 100, 150);
}