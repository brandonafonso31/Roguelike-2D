#include "paths.h"
#include "settings.h"
#include <stdio.h>
#include <string.h>

void loadSettings(GameSettings* settings) {
    char config_file[2048];
    snprintf(config_file, sizeof(config_file), "%s/settings.cfg", GetConfigPath());
    
    printf("Tentative de chargement: %s\n", config_file);
    
    FILE* file = fopen(config_file, "r");
    if (!file) {
        printf("Impossible d'ouvrir %s, utilisation des valeurs par défaut\n", config_file);
        settings->width = 640;
        settings->height = 480;
        settings->fps_limit = 30;
        settings->vsync = 0;
        settings->volume = 80;
        settings->fullscreen = 0;
        strcpy(settings->font, "pokemon_BW2.otf");
        return;
    }
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        
        if (strstr(line, "WINDOW_WIDTH=")) {
            sscanf(line, "WINDOW_WIDTH=%d", &settings->width);
        } else if (strstr(line, "WINDOW_HEIGHT=")) {
            sscanf(line, "WINDOW_HEIGHT=%d", &settings->height);
        } else if (strstr(line, "FPS=")) {
            sscanf(line, "FPS=%d", &settings->fps_limit);
        } else if (strstr(line, "VSYNC=")) {
            sscanf(line, "VSYNC=%d", &settings->vsync);
        } else if (strstr(line, "VOLUME=")) {
            sscanf(line, "VOLUME=%d", &settings->volume);
        } else if (strstr(line, "FULLSCREEN=")) {
            sscanf(line, "FULLSCREEN=%d", &settings->fullscreen);
        } else if (strstr(line, "FONT=")) {
            char temp[1024];
            if (sscanf(line, "FONT=%s", temp) == 1) {
                strcpy(settings->font, temp);
            }
        }
    }
    
    fclose(file);
    
    printf("Configuration chargée depuis: %s\n", config_file);
    printf("  WINDOW_WIDTH = %d\n", settings->width);
    printf("  WINDOW_HEIGHT = %d\n", settings->height);
    printf("  FPS = %d\n", settings->fps_limit);
    printf("  VSYNC = %d\n", settings->vsync);
    printf("  VOLUME = %d\n", settings->volume);
    printf("  FULLSCREEN = %d\n", settings->fullscreen);
    printf("  FONT = %s\n", settings->font);

}