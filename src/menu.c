#include "menu.h"

MainMenuButtons* initMainMenuButtons(SDL_Renderer* renderer, GameSettings* settings) {
    MainMenuButtons* buttons = (MainMenuButtons*)malloc(sizeof(MainMenuButtons));
    if (!buttons) return NULL;
        
    int ratio = 3;
    Image* image_newgame = loadImageMenuScaled(renderer, "newgame.png", ratio);
    int width = image_newgame->width, height = image_newgame->height;
    int screen_w = settings->width;
    int screen_h = settings->height;
    int spacing = settings->spacing;
    int start_x = screen_w - width - spacing;
    int start_y = screen_h - NUMBER_OF_MAINMENU_BUTTONS * (spacing + height) - 2*spacing;
        
    const char* button_names[] = { 
        #define X(name,action) #name,
        MAIN_MENU_BUTTONS
        #undef X 
    };

    Button** buttons_ptrs[] = { 
        #define X(name,action) &buttons->name, 
        MAIN_MENU_BUTTONS 
        #undef X 
    };

    for (int i = 0; i < NUMBER_OF_MAINMENU_BUTTONS; i++) {
        char path[256];
        Image* normal = NULL;
        Image* clicked = NULL;
        Image* hover = NULL;
        
        snprintf(path, sizeof(path), "%s.png", button_names[i]);
        normal = loadImageMenuScaled(renderer, path, ratio);
        
        snprintf(path, sizeof(path), "%s_clicked.png", button_names[i]);
        clicked = loadImageMenuScaled(renderer, path, ratio);
        
        snprintf(path, sizeof(path), "%s_hover.png", button_names[i]);
        hover = loadImageMenuScaled(renderer, path, ratio);

        *buttons_ptrs[i] = createButton(normal, clicked, hover, start_x, \
                                        start_y + i * (spacing + height), width, height);
    }

    return buttons;
}

MainMenu* menuCreate(SDL_Renderer* renderer, GameSettings* settings) {
    MainMenu* menu = (MainMenu*)malloc(sizeof(MainMenu));
    if (!menu) return NULL;

    menu->background = loadImageMenu(renderer, "background.jpg");
    menu->cursor = loadImageSystem(renderer, "cursor.png");
    
    menu->buttons = initMainMenuButtons(renderer, settings);
    menu->selected_index = 0;
    menu->button_count = NUMBER_OF_MAINMENU_BUTTONS;
    
    return menu;
}

void changeButtonFromIndex(MainMenu* menu, int index) {
    if (!menu || !menu->buttons) return;

    MainMenuButtons* buttons = menu->buttons;
    buttons->newgame->is_hovered = 0;
    buttons->continue_game->is_hovered = 0;
    buttons->settings->is_hovered = 0;
    buttons->quit->is_hovered = 0;
    
    switch (index) {
        case 0:
            buttons->newgame->is_hovered = 1;
            break;
        case 1:
            buttons->continue_game->is_hovered = 1;
            break;
        case 2:
            buttons->settings->is_hovered = 1;
            break;
        case 3:
            buttons->quit->is_hovered = 1;
            break;
        default:
            break;
    }
}

void destroyMenu(MainMenu* menu) {
    if (!menu) return;
    
    destroyImage(menu->background);
    destroyImage(menu->cursor);
    
    #define X(name, action) \
        if (menu->buttons.name) { \
            destroyButton(menu->buttons.name); \
            menu->buttons.name = NULL; \
        } \
    MAIN_MENU_BUTTONS
    #undef X
    
    menu->selected_index = -1;
    
    free(menu);
}

MainMenuAction getSelectedActionMenu(MainMenu* menu) {
    if (!menu) return MENU_QUIT;

    MainMenuAction actions[] = {
        #define X(name, action) action,
        MAIN_MENU_BUTTONS
        #undef X
    };
    
    int count = NUMBER_OF_MAINMENU_BUTTONS;
    
    if (menu->selected_index >= 0 && menu->selected_index < count) {
        return actions[menu->selected_index];
    }
    
    return MENU_QUIT;
}

InGameMenu* inGameMenuCreate(SDL_Renderer* renderer, GameSettings* settings) {
    InGameMenu* menu = (InGameMenu*)malloc(sizeof(InGameMenu));
    if (!menu) return NULL;

    menu->background = loadImageMenu(renderer, "world1.png");
    
    /*Button* Dungeon = NULL;
    Button* play = NULL;
    Button* pp = NULL;
    Button* donjon = NULL;
    Button* quest = NULL;
    Button* shop = NULL;
    Button* options = NULL;
    Button* Upgrades = NULL;*/
    
    menu->selected_tab = 2;
    menu->last_tab_id = 2;
    menu->nb_tabs = 5;
    
    return menu;
}

void destroyInGameMenu(InGameMenu* menu) {
    if (!menu) return;
    
    destroyImage(menu->background);
    
    free(menu);
}

InGameMenuAction getSelectedActionInGameMenu(InGameMenu* menu) {
    if (!menu) return MENU_QUIT;
        
    switch(menu->selected_tab) {
        case 0: return SHOP;
        case 1: return INVENTORY;
        case 2: return WORLD;
        case 3: return UPGRADES;
        case 4: return WIP;

        case 5: return INGAME_PLAY;
        case 6: return INGAME_BACK;
        case 7: return INGAME_QUIT;
        default: return WORLD;
    }
}

SettingsMenu* settingsMenuCreate(SDL_Renderer* renderer, GameSettings* settings){
    SettingsMenu* menu = (SettingsMenu*)malloc(sizeof(SettingsMenu));
    if (!menu) return NULL;
    menu->background = loadImageMenu(renderer, "world1.png");
    return menu;
}

void destroySettingsMenu(SettingsMenu* menu) {
    if (!menu) return;
    
    destroyImage(menu->background);
    
    free(menu);
}