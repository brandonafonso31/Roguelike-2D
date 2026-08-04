#include "settings.h"
#include <stdio.h>
#include <string.h>
 
void loadSettings(GameSettings* settings)
{
    FILE* file = fopen("settings.cfg", "r");
    if (!file){
        printf("Impossible d'ouvrir settings.cfg\n");
        return;
    }

    char key[50];
    int value;

    while(fscanf(file, "%[^=]=%d\n", key, &value) == 2){
        if(strcmp(key,"WINDOW_WIDTH")==0)
            settings->width = value;

        else if(strcmp(key,"WINDOW_HEIGHT")==0)
            settings->height = value;

        else if(strcmp(key,"FPS")==0)
            settings->fps_limit = value;

        else if(strcmp(key,"VSYNC")==0)
            settings->vsync = value;

        else if(strcmp(key,"VOLUME")==0)
            settings->volume = value;

        else if(strcmp(key,"FULLSCREEN")==0)
            settings->fullscreen = value;
    }
    fclose(file);
    printf("Settings loaded\n");
}