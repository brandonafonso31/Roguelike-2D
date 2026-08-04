#include "settings.h"
#include <stdio.h>
#include "settings.cfg"

void loadSettings(GameSettings* settings){    
    settings->width = WINDOW_WIDTH;
    settings->height = WINDOW_HEIGHT;
    settings->fps_limit = FPS_;
    settings->vsync = VSYNC;
    settings->volume = VOLUME;

    printf("Settings loaded\n");
}