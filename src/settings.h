#ifndef SETTINGS_H
#define SETTINGS_H

#include <stdio.h>
#include <string.h>
#include "paths.h"


typedef struct{
    int width;
    int height;
    int fps_limit;
    int vsync;
    int volume;
    int fullscreen;
    char font[1024];

    int spacing;
} GameSettings;

void loadSettings(GameSettings* settings);

#endif