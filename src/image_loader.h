// image_loader.h
#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "paths.h"


typedef struct {
    SDL_Texture* texture;
    int width;
    int height;
} Image;

// Charger une image depuis le dossier assets/images/
Image* loadImage(SDL_Renderer* renderer, const char* path);
Image* loadImageMenu(SDL_Renderer* renderer, const char* path);
Image* loadImageSystem(SDL_Renderer* renderer, const char* path);
void destroyImage(Image* image);
void renderImage(SDL_Renderer* renderer, Image* image, int x, int y);
void renderImageOrigin(SDL_Renderer* renderer, Image* image);
void renderScaledImage(SDL_Renderer* renderer, Image* image, int x, int y, int w, int h);
void renderScaledImageOrigin(SDL_Renderer* renderer, Image* image, int w, int h);
void renderScaledRatioImage(SDL_Renderer* renderer, Image* image, int x, int y, double ratio);

void renderScaledWidthImage(SDL_Renderer* renderer, Image* image, int x, int y, int w);
void renderScaledHeightImage(SDL_Renderer* renderer, Image* image, int x, int y, int h);
void renderScaledWidthImageOrigin(SDL_Renderer* renderer, Image* image,  int w);
void renderScaledHeightImageOrigin(SDL_Renderer* renderer, Image* image,  int h);

#endif