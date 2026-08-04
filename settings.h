#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct{
    int width;
    int height;
    int fps_limit;
    int vsync;
    int volume;

} GameSettings;


void loadSettings(GameSettings* settings);

#endif