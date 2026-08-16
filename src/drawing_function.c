#include "drawing_function.h"

void drawText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst_rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void drawTextWhite(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color color = readColor("WHITE");
    drawText(renderer, font, text, x, y, color);
}

void drawTextGray(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color color = readColor("GRAY");
    drawText(renderer, font, text, x, y, color);
}

void drawTextBlack(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
    SDL_Color color = readColor("BLACK");
    drawText(renderer, font, text, x, y, color);
}

SDL_Color readColor(const char* color_name) {
    SDL_Color default_color = {255, 255, 255, 255};
    
    char colors_file[1024];
    snprintf(colors_file, sizeof(colors_file), "%s/colors.cfg", getConfigPath());
    
    FILE* file = fopen(colors_file, "r");
    if (!file) return default_color;
    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        
        char name[64];
        int r, g, b, a = 255;
        
        if (sscanf(line, " %63[^=] = %d , %d , %d , %d", name, &r, &g, &b, &a) >= 4) {

            //printf("%s and %s : %d\n",color_name,name,strcmp(name, color_name));
            if (strcmp(name, color_name) == 0) {
                fclose(file);
                return (SDL_Color){r, g, b, a};
            }
        }
    }
    
    fclose(file);
    return default_color;
}

void drawTriangle(int x, int y, SDL_Renderer* renderer, int width) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    int tri_x = x + width / 2;
    int tri_y = y;
    for (int j = 0; j < 8; j++) {
        SDL_RenderDrawPoint(renderer, tri_x - j, tri_y - j);
        SDL_RenderDrawPoint(renderer, tri_x + j, tri_y - j);
    }
}

void drawColoredTriangle(int x, int y, SDL_Renderer* renderer, int width, const char* color_name) {
    SDL_Color color = readColor(color_name);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    int tri_x = x + width / 2;
    int tri_y = y;
    for (int j = 0; j < 8; j++) {
        SDL_RenderDrawPoint(renderer, tri_x - j, tri_y - j);
        SDL_RenderDrawPoint(renderer, tri_x + j, tri_y - j);
    }
}