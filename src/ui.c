#include "ui.h"

static void renderFps(FPSCounter* fps_counter, SDL_Renderer* renderer, TTF_Font* font, GameSettings* settings, double dt) {
    char fps_text[50];
    int average_fps = fpsCounterUpdate(fps_counter, dt);
    int target_fps = settings->vsync ? getMonitorRefreshRate() : settings->fps_limit;
    snprintf(fps_text, sizeof(fps_text), "FPS: %d (target: %d)", average_fps, target_fps);
    drawTextWhite(renderer, font, fps_text, 10, 10);
}

// MainMenu

void renderMainMenuButtons(MainMenu* menu, SDL_Renderer* renderer) {
    if (!menu || !menu->buttons) return;
    Button** current = (Button**)menu->buttons;
    for (int i = 0; i < NUMBER_OF_MAINMENU_BUTTONS; i++) {
        Button* button = current[i];
        if (button) drawButton(renderer, button);
    }
}

void renderMainMenuUI(MainMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    int height = settings->height;
    int width = settings->width;
    int index = menu->selected_index;
    int spacing = settings->spacing;

    renderScaledImageOrigin(renderer, menu->background, width, height);

    renderFps(fps_counter, renderer, font, settings, dt);

    Button* newgame = menu->buttons->newgame;

    renderMainMenuButtons(menu, renderer);

    if (index != -1)
        renderImage(renderer,menu->cursor, width - getButtonWidth(newgame) - 6*spacing, 
                                            height - (NUMBER_OF_MAINMENU_BUTTONS-1-index) * (spacing + getButtonHeight(newgame)) - 7*spacing);
    changeButtonFromIndex(menu, index);

    SDL_RenderPresent(renderer);
}

// InGameMenu

void renderInGameMenuUI(InGameMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings) {
    int width = settings->width;
    int height = settings->height;
    
    renderScaledImageOrigin(renderer, menu->background, width, height);
    
    switch(menu->selected_tab) {
        case 0:
            renderShopTab(renderer, font, width, height, dt);
            break;
        case 1:
            renderInventoryTab(renderer, font, width, height, dt);
            break;
        case 2:
            renderWorldTab(renderer, font, width, height, dt);
            break;
        case 3:
            renderUpgradesTab(renderer, font, width, height, dt);
            break;
        case 4:
            renderWipTab(renderer, font, width, height, dt);
            break;
    }
    
    const char* tabs[] = {"Shop", "Inventaire", "Monde", "Upgrades", "En travaux"};
    int tab_count = 5;
    int tab_height = 50;
    int tab_width = width / tab_count;
    int y_offset = height - tab_height;
    
    for (int i = 0; i < tab_count; i++) {
        int x = i * tab_width;
        SDL_Rect tab_rect = {x, y_offset, tab_width, tab_height};
        
        if (i == menu->selected_tab) {
            float pulse = 0.8 + 0.2 * sin(dt * 2.0);
            SDL_SetRenderDrawColor(renderer, 
                60 * pulse, 60 * pulse, 120 * pulse, 255);
        } else {
            SDL_SetRenderDrawColor(renderer, 30, 30, 50, 200);
        }
        SDL_RenderFillRect(renderer, &tab_rect);
        
        SDL_SetRenderDrawColor(renderer, 80, 80, 120, 255);
        SDL_RenderDrawLine(renderer, x, y_offset, x + tab_width, y_offset);
        
        SDL_RenderDrawRect(renderer, &tab_rect);
        
        if (i == menu->selected_tab) {
            drawColoredTriangle(x,y_offset,renderer,tab_width,"BLACK");
        }
        
        int text_w = strlen(tabs[i]) * 12;
        int text_x = x + (tab_width - text_w) / 2;
        int text_y = y_offset + (tab_height - 24) / 2;
        
        if (i == menu->selected_tab) {
            drawTextWhite(renderer, font, tabs[i], text_x, text_y);
        } else {
            drawTextBlack(renderer, font, tabs[i], text_x, text_y);
        }
    }
    
    renderFps(fps_counter, renderer, font, settings, dt);
    
    // Play
    int btn_w = 100;
    int btn_h = 35;
    int btn_x = width/2 - btn_w/2;
    int btn_y = height/2 - btn_h/2;
    float pulse = 0.9 + 0.1 * sin(dt * 1.5);
    SDL_SetRenderDrawColor(renderer, 60 * pulse, 50 * pulse, 50 * pulse, 255);
    SDL_Rect btn_rect = {btn_x, btn_y, btn_w, btn_h};
    SDL_RenderFillRect(renderer, &btn_rect);
    SDL_SetRenderDrawColor(renderer, 150, 80, 80, 255);
    SDL_RenderDrawRect(renderer, &btn_rect);
    if (menu->selected_tab == menu->nb_tabs)
        drawColoredTriangle(btn_x,btn_y,renderer,btn_w,"BLACK");
    drawTextWhite(renderer, font, "Play", btn_x + 15, btn_y + 8);

    // Retour
    btn_w = 100;
    btn_h = 35;
    btn_x = width - btn_w - 20;
    btn_y = 20;    
    pulse = 0.9 + 0.1 * sin(dt * 1.5);
    SDL_SetRenderDrawColor(renderer, 60 * pulse, 50 * pulse, 50 * pulse, 255);
    btn_rect = (SDL_Rect){btn_x, btn_y, btn_w, btn_h};
    SDL_RenderFillRect(renderer, &btn_rect);
    SDL_SetRenderDrawColor(renderer, 150, 80, 80, 255);
    SDL_RenderDrawRect(renderer, &btn_rect);
    if (menu->selected_tab == menu->nb_tabs+1)
        drawColoredTriangle(btn_x,btn_y,renderer,btn_w,"BLACK");
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

// SettingsMenu

void switchSettings(int id, SettingsMenu* menu, SDL_Renderer* renderer, double dt, TTF_Font* font, int width, int height, int content_x, int content_y, int line_spacing, int label_width, int value_x){
    switch(id) {
        case 0:
            renderMainSettingsTab(renderer, font, width, height, dt, content_x, content_y, line_spacing, label_width, value_x);
            break;
        case 1:
            renderGraphicSettingsTab(renderer, font, width, height, dt, content_x, content_y, line_spacing, label_width, value_x);
            break;
        case 2:
            renderSoundSettingsTab(renderer, font, width, height, dt, content_x, content_y, line_spacing, label_width, value_x);
            break;
        case 3:
            switchSettings(menu->last_tab_id, menu, renderer, dt, font, width, height, content_x, content_y, line_spacing, label_width, value_x);
    }
}

void renderSettingsUI(SettingsMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings) {
    int width = settings->width;
    int height = settings->height;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 180);
    SDL_RenderClear(renderer);
    //renderScaledImageOrigin(renderer, menu->background, width, height);
    
    const char* tabs[] = {"Main", "Graphic", "Sound"};
    int tab_count = 3;
    int tab_height = 45;
    int tab_width = width / tab_count;
    int y_offset = 0;
    
    for (int i = 0; i < tab_count; i++) {
        int x = i * tab_width;
        SDL_Rect tab_rect = {x, y_offset, tab_width, tab_height};
        
        if (i == menu->selected_tab) {
            float pulse = 0.8 + 0.2 * sin(dt * 2.0);
            SDL_SetRenderDrawColor(renderer, 60 * pulse, 60 * pulse, 120 * pulse, 220);
        } else {
            SDL_SetRenderDrawColor(renderer, 30, 30, 50, 180);
        }
        SDL_RenderFillRect(renderer, &tab_rect);

        SDL_SetRenderDrawColor(renderer, 80, 80, 120, 255);
        SDL_RenderDrawLine(renderer, x, y_offset + tab_height, x + tab_width, y_offset + tab_height);
        SDL_RenderDrawRect(renderer, &tab_rect);
        
        int text_w = strlen(tabs[i]) * 12;
        int text_x = x + (tab_width - text_w) / 2;
        int text_y = y_offset + (tab_height - 24) / 2;
        
        if (i == menu->selected_tab) {
            drawTextWhite(renderer, font, tabs[i], text_x, text_y);
        } else {
            drawTextGray(renderer, font, tabs[i], text_x, text_y);
        }
    }
    
    int content_y = tab_height + 20;
    int content_x = 30;
    int line_spacing = 35;
    int label_width = 150;
    int value_x = content_x + label_width + 20;
    
    switchSettings(menu->selected_tab, menu, renderer, dt, font, width, height, content_x, content_y, line_spacing, label_width, value_x);
    
    int btn_w = 100;
    int btn_h = 35;
    int btn_x = width - btn_w - 30;
    int btn_y = height - 60;
    
    float pulse = 0.9 + 0.1 * sin(dt * 1.5);
    SDL_SetRenderDrawColor(renderer, 60 * pulse, 50 * pulse, 50 * pulse, 220);
    SDL_Rect btn_rect = {btn_x, btn_y, btn_w, btn_h};
    SDL_RenderFillRect(renderer, &btn_rect);
    SDL_SetRenderDrawColor(renderer, 150, 80, 80, 255);
    SDL_RenderDrawRect(renderer, &btn_rect);
    drawTextWhite(renderer, font, "Retour", btn_x + 15, btn_y + 8);
    
    SDL_RenderPresent(renderer);
}

void renderMainSettingsTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt, int x, int y, int spacing, int label_w, int val_x) {
    drawTextWhite(renderer, font, "MAIN SETTINGS", x, y);
    y += spacing + 10;
    
    drawTextGray(renderer, font, "Difficulty :", x, y);
    drawTextWhite(renderer, font, "ADVENTURE", val_x, y);
    drawTextGray(renderer, font, "EASY", val_x + 110, y);
    drawTextGray(renderer, font, "HARD", val_x + 180, y);
    y += spacing;
    
    drawTextGray(renderer, font, "Cheats :", x, y);
    drawTextWhite(renderer, font, "ON", val_x, y);
    drawTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    drawTextGray(renderer, font, "Infinite Gold :", x, y);
    drawTextWhite(renderer, font, "ON", val_x, y);
    drawTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    drawTextGray(renderer, font, "Debug :", x, y);
    drawTextWhite(renderer, font, "ON", val_x, y);
    drawTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing + 10;
    
    drawTextGray(renderer, font, "Contrôles :", x, y);
    drawTextWhite(renderer, font, "AZERTY", val_x, y);
    drawTextGray(renderer, font, "QWERTY", val_x + 80, y);
    drawTextGray(renderer, font, "ARROW", val_x + 170, y);
    y += spacing + 10;
}

void renderGraphicSettingsTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt, int x, int y, int spacing, int label_w, int val_x) {
    drawTextWhite(renderer, font, "GRAPHIC SETTINGS", x, y);
    y += spacing + 10;
    
    drawTextGray(renderer, font, "Gamma :", x, y);
    float gamma = 0.5 + 0.4 * sin(dt * 0.5);
    SDL_SetRenderDrawColor(renderer, 40, 40, 60, 200);
    SDL_Rect bar_bg = {val_x, y + 5, 150, 20};
    SDL_RenderFillRect(renderer, &bar_bg);
    SDL_SetRenderDrawColor(renderer, 100, 150, 255, 200);
    SDL_Rect bar_fg = {val_x, y + 5, (int)(150 * gamma), 20};
    SDL_RenderFillRect(renderer, &bar_fg);
    y += spacing;
    
    drawTextGray(renderer, font, "Lock FPS :", x, y);
    drawTextWhite(renderer, font, "ON", val_x, y);
    drawTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    drawTextGray(renderer, font, "Fullscreen :", x, y);
    drawTextGray(renderer, font, "ON", val_x, y);
    drawTextWhite(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    drawTextGray(renderer, font, "VSYNC :", x, y);
    drawTextWhite(renderer, font, "ON", val_x, y);
    drawTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    drawTextGray(renderer, font, "Cinematic Filter:", x, y);
    drawTextWhite(renderer, font, "ON", val_x, y);
    drawTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing + 10;
}

void renderSoundSettingsTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt, int x, int y, int spacing, int label_w, int val_x) {
    drawTextWhite(renderer, font, "SOUND SETTINGS", x, y);
    y += spacing + 10;
    
    drawTextGray(renderer, font, "Volume :", x, y);
    float volume = 0.7 + 0.2 * sin(dt * 0.3);
    SDL_SetRenderDrawColor(renderer, 40, 40, 60, 200);
    SDL_Rect bar_bg = {val_x, y + 5, 150, 20};
    SDL_RenderFillRect(renderer, &bar_bg);
    SDL_SetRenderDrawColor(renderer, 100, 200, 150, 200);
    SDL_Rect bar_fg = {val_x, y + 5, (int)(150 * volume), 20};
    SDL_RenderFillRect(renderer, &bar_fg);
    y += spacing;
    
    drawTextGray(renderer, font, "Musique :", x, y);
    drawTextWhite(renderer, font, "ON", val_x, y);
    drawTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    drawTextGray(renderer, font, "Sounds Effect :", x, y);
    drawTextWhite(renderer, font, "ON", val_x, y);
    drawTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    drawTextGray(renderer, font, "UI Sounds :", x, y);
    drawTextWhite(renderer, font, "ON", val_x, y);
    drawTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
}