#include "ui.h"

static void renderFps(FPSCounter* fps_counter, SDL_Renderer* renderer, TTF_Font* font, GameSettings* settings, double dt) {
    char fps_text[50];
    int average_fps = fpsCounterUpdate(fps_counter, dt);
    int target_fps = settings->vsync ? getMonitorRefreshRate() : settings->fps_limit;
    snprintf(fps_text, sizeof(fps_text), "FPS: %d (target: %d)", average_fps, target_fps);
    renderTextWhite(renderer, font, fps_text, 10, 10);
}

// MainMenu

static void renderMainMenuButtons(MainMenu* menu, SDL_Renderer* renderer) {
    if (!menu || !menu->buttons) return;
    Button** current = (Button**)menu->buttons;
    for (int i = 0; i < NUMBER_OF_MAINMENU_BUTTONS; i++) {
        Button* button = current[i];
        if (button) renderButton(renderer, button);
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

static void renderBlackBackground(SDL_Renderer* renderer, TTF_Font* font, const char* txt){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderTextWhite(renderer, font, txt, 50, 80);
}

static void renderWorldTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt) {
    renderTextWhite(renderer, font, "MONDE", 50, 80);
    renderTextBlack(renderer, font, "Explorez le monde et partez à l'aventure !", 50, 120);
}

static void renderInventoryTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt) {
    renderBlackBackground(renderer, font, "INVENTORY");
}

static void renderShopTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt) {
    renderBlackBackground(renderer, font, "SHOP");
}

static void renderUpgradesTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt, EntityDatabase* db_entities) {
    renderBlackBackground(renderer, font, "UPGRADES");
    if (!db_entities || !db_entities->player || !db_entities->player->stats) {
        renderTextBlack(renderer, font, "Aucun personnage chargé", 50, 120);
        return;
    }

    Entity* player = db_entities->player;
    Statistics* s = player->stats;

    char buffer[128];
    snprintf(buffer, sizeof(buffer), "Personnage : %s", player->name);
    renderTextBlack(renderer, font, buffer, 50, 120);

    int x = width/3;
    int y = height/3;
    int spacing = 35;

    snprintf(buffer, sizeof(buffer), "HP      : %d / %d", player->hp, s->max_hp);
    renderTextWhite(renderer, font, buffer, x, y); y += spacing;

    snprintf(buffer, sizeof(buffer), "Attack: %d     Defense: %d", s->atk, s->def);
    renderTextWhite(renderer, font, buffer, x, y); y += spacing;

    snprintf(buffer, sizeof(buffer), "Speed: %d      Atk Speed : %d",s->speed, s->atk_speed);
    renderTextWhite(renderer, font, buffer, x, y); y += spacing;

}

static void renderWipTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt) {
    renderBlackBackground(renderer, font, "WORK IN PROGRESS");
}

void renderInGameMenuUI(InGameMenu* menu, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings, EntityDatabase* db_entities) {
    int width = settings->width;
    int height = settings->height;
    
    renderScaledImageOrigin(renderer, menu->background, width, height);
    
    // render tabs
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
            renderUpgradesTab(renderer, font, width, height, dt, db_entities);
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

    int nb = menu->nb_tabs;
    const int TAB_PLAY = nb;
    const int TAB_RETURN = nb + 1;
    int* selected = &menu->selected_tab;
    int is_on_special = (*selected == TAB_PLAY || *selected == TAB_RETURN);

    // button and triangle
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
            renderColoredTriangle(x,y_offset,renderer,tab_width,"GREEN");
        }
        
        int text_w = strlen(tabs[i]) * 12;
        int text_x = x + (tab_width - text_w) / 2;
        int text_y = y_offset + (tab_height - 24) / 2;
        
        if (i == menu->selected_tab) {
            renderTextWhite(renderer, font, tabs[i], text_x, text_y);
        } else {
            renderTextBlack(renderer, font, tabs[i], text_x, text_y);
        }
    }
    
    renderFps(fps_counter, renderer, font, settings, dt);
    
    // Play et retour
    if (menu->selected_tab == 2 || is_on_special) {
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
        if (menu->selected_tab == TAB_PLAY)
            renderColoredTriangle(btn_x,btn_y,renderer,btn_w,"GREEN");
        renderTextWhite(renderer, font, "Play", btn_x + 15, btn_y + 8);

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
        if (menu->selected_tab == TAB_RETURN)
            renderColoredTriangle(btn_x,btn_y,renderer,btn_w,"GREEN");
        renderTextWhite(renderer, font, "Retour", btn_x + 15, btn_y + 8);
    }
    SDL_RenderPresent(renderer);
}

// SettingsMenu

static void renderMainSettingsTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt, int x, int y, int spacing, int label_w, int val_x) {
    renderTextWhite(renderer, font, "MAIN SETTINGS", x, y);
    y += spacing + 10;
    
    renderTextGray(renderer, font, "Difficulty :", x, y);
    renderTextWhite(renderer, font, "ADVENTURE", val_x, y);
    renderTextGray(renderer, font, "EASY", val_x + 110, y);
    renderTextGray(renderer, font, "HARD", val_x + 180, y);
    y += spacing;
    
    renderTextGray(renderer, font, "Cheats :", x, y);
    renderTextWhite(renderer, font, "ON", val_x, y);
    renderTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    renderTextGray(renderer, font, "Infinite Gold :", x, y);
    renderTextWhite(renderer, font, "ON", val_x, y);
    renderTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    renderTextGray(renderer, font, "Debug :", x, y);
    renderTextWhite(renderer, font, "ON", val_x, y);
    renderTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing + 10;
    
    renderTextGray(renderer, font, "Contrôles :", x, y);
    renderTextWhite(renderer, font, "AZERTY", val_x, y);
    renderTextGray(renderer, font, "QWERTY", val_x + 80, y);
    renderTextGray(renderer, font, "ARROW", val_x + 170, y);
    y += spacing + 10;
}

static void renderGraphicSettingsTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt, int x, int y, int spacing, int label_w, int val_x) {
    renderTextWhite(renderer, font, "GRAPHIC SETTINGS", x, y);
    y += spacing + 10;
    
    renderTextGray(renderer, font, "Gamma :", x, y);
    float gamma = 0.5 + 0.4 * sin(dt * 0.5);
    SDL_SetRenderDrawColor(renderer, 40, 40, 60, 200);
    SDL_Rect bar_bg = {val_x, y + 5, 150, 20};
    SDL_RenderFillRect(renderer, &bar_bg);
    SDL_SetRenderDrawColor(renderer, 100, 150, 255, 200);
    SDL_Rect bar_fg = {val_x, y + 5, (int)(150 * gamma), 20};
    SDL_RenderFillRect(renderer, &bar_fg);
    y += spacing;
    
    renderTextGray(renderer, font, "Lock FPS :", x, y);
    renderTextWhite(renderer, font, "ON", val_x, y);
    renderTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    renderTextGray(renderer, font, "Fullscreen :", x, y);
    renderTextGray(renderer, font, "ON", val_x, y);
    renderTextWhite(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    renderTextGray(renderer, font, "VSYNC :", x, y);
    renderTextWhite(renderer, font, "ON", val_x, y);
    renderTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    renderTextGray(renderer, font, "Cinematic Filter:", x, y);
    renderTextWhite(renderer, font, "ON", val_x, y);
    renderTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing + 10;
}

static void renderSoundSettingsTab(SDL_Renderer* renderer, TTF_Font* font, int width, int height, double dt, int x, int y, int spacing, int label_w, int val_x) {
    renderTextWhite(renderer, font, "SOUND SETTINGS", x, y);
    y += spacing + 10;
    
    renderTextGray(renderer, font, "Volume :", x, y);
    float volume = 0.7 + 0.2 * sin(dt * 0.3);
    SDL_SetRenderDrawColor(renderer, 40, 40, 60, 200);
    SDL_Rect bar_bg = {val_x, y + 5, 150, 20};
    SDL_RenderFillRect(renderer, &bar_bg);
    SDL_SetRenderDrawColor(renderer, 100, 200, 150, 200);
    SDL_Rect bar_fg = {val_x, y + 5, (int)(150 * volume), 20};
    SDL_RenderFillRect(renderer, &bar_fg);
    y += spacing;
    
    renderTextGray(renderer, font, "Musique :", x, y);
    renderTextWhite(renderer, font, "ON", val_x, y);
    renderTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    renderTextGray(renderer, font, "Sounds Effect :", x, y);
    renderTextWhite(renderer, font, "ON", val_x, y);
    renderTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
    
    renderTextGray(renderer, font, "UI Sounds :", x, y);
    renderTextWhite(renderer, font, "ON", val_x, y);
    renderTextGray(renderer, font, "OFF", val_x + 60, y);
    y += spacing;
}

static void switchSettings(int id, SettingsMenu* menu, SDL_Renderer* renderer, double dt, TTF_Font* font, int width, int height, int content_x, int content_y, int line_spacing, int label_width, int value_x){
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
            renderTextWhite(renderer, font, tabs[i], text_x, text_y);
        } else {
            renderTextGray(renderer, font, tabs[i], text_x, text_y);
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
    renderTextWhite(renderer, font, "Retour", btn_x + 15, btn_y + 8);
    
    SDL_RenderPresent(renderer);
}

//void renderInterfaceInGame(Interface interface, FPSCounter* fps_counter, SDL_Renderer* renderer, double dt, TTF_Font* font, GameSettings* settings, EntityDatabase* db_entities){}