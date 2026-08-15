#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "settings.h"
#include "fps_utils.h"
#include "paths.h"
#include "poll_events.h"
#include "ui.h"

typedef enum {
    MENU_PLAY,
    MENU_SETTINGS,
    MENU_QUIT
} MenuAction;

typedef struct {
    Image* background;
    /*Image* title;
    Image* play_button;
    Image* settings_button;
    Image* quit_button;
    Image* play_button_hover;
    Image* settings_button_hover;
    Image* quit_button_hover;*/
    int selected_index;
    int button_count;
} MainMenu;

void main_menu(SDL_Window* window, SDL_Renderer* renderer, GameSettings* settings);
    
#endif