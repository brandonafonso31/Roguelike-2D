#include "menu.h"

MainMenu* menuCreate(SDL_Renderer* renderer, GameSettings* settings) {
    MainMenu* menu = (MainMenu*)malloc(sizeof(MainMenu));
    if (!menu) return NULL;

    menu->background = loadImageMenu(renderer, "background.jpg");
    /*menu->title = LoadImage(renderer, "menu/title.png");
    menu->play_button = LoadImage(renderer, "menu/buttons/play.png");
    menu->settings_button = LoadImage(renderer, "menu/buttons/settings.png");
    menu->quit_button = LoadImage(renderer, "menu/buttons/quit.png");
    
    menu->play_button_hover = LoadImage(renderer, "menu/buttons/play_hover.png");
    menu->settings_button_hover = LoadImage(renderer, "menu/buttons/settings_hover.png");
    menu->quit_button_hover = LoadImage(renderer, "menu/buttons/quit_hover.png");*/
    
    menu->selected_index = -1;
    menu->button_count = MAX_BUTTONS;
    
    return menu;
}

void destroyMenu(MainMenu* menu) {
    if (!menu) return;
    
    destroyImage(menu->background);

    /*ImageDestroy(menu->title);
    ImageDestroy(menu->play_button);
    ImageDestroy(menu->settings_button);
    ImageDestroy(menu->quit_button);
    ImageDestroy(menu->play_button_hover);
    ImageDestroy(menu->settings_button_hover);
    ImageDestroy(menu->quit_button_hover);*/
    
    free(menu);
}