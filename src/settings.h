#include <string.h>

#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct{
    int width;
    int height;
    int fps_limit;
    int vsync;
    int volume;
    int fullscreen;
    char font[1024];

} GameSettings;


void loadSettings(GameSettings* settings);

#endif