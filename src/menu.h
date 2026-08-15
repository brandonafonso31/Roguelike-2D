#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include "settings.h"
#include "image_loader.h"

#define MAX_BUTTONS 3

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

MainMenu* menuCreate(SDL_Renderer* renderer, GameSettings* settings);
void destroyMenu(MainMenu* menu);

#endif