#include "image.h"

Image* createEmptyImage(SDL_Renderer* renderer) {
    if (!renderer) return NULL;
    
    int width = 200; int height = 75;
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if (!surface) return NULL;
    
    int tile = 8;
    Uint32 purple = SDL_MapRGBA(surface->format, 200, 0, 255, 255);
    Uint32 black = SDL_MapRGBA(surface->format, 0, 0, 0, 255);
    
    for (int y = 0; y < height; y += tile) {
        for (int x = 0; x < width; x += tile) {
            SDL_Rect rect = {x, y, tile, tile};
            Uint32 color = ((x/tile) + (y/tile)) % 2 ? purple : black;
            SDL_FillRect(surface, &rect, color);
        }
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    if (!texture) return NULL;
    
    Image* image = malloc(sizeof(Image));
    if (!image) {
        SDL_DestroyTexture(texture);
        return NULL;
    }
    
    image->texture = texture;
    image->width = width;
    image->height = height;
    image->ratio = 1.0;
    
    return image;
}

Image* loadImageScaled(SDL_Renderer* renderer, const char* path, double ratio) {
    if (!renderer) {
        printf("Erreur: renderer NULL\n");
        return createEmptyImage(renderer);
    }
    
    char full_path[2048];
    snprintf(full_path, sizeof(full_path), "%s/%s", getImagesPath(), path);
    
    SDL_Surface* surface = IMG_Load(full_path);
    if (!surface) {
        printf("Erreur chargement %s: %s\n", full_path, IMG_GetError());
        return createEmptyImage(renderer);
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur création texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return createEmptyImage(renderer);
    }
    
    Image* image = (Image*)malloc(sizeof(Image));
    image->texture = texture;
    image->width = surface->w/ratio;
    image->height = surface->h/ratio;
    image->ratio = ratio;
    
    SDL_FreeSurface(surface);
    
    printf("Image chargée: %s (%dx%d)\n", full_path, image->width, image->height);
    return image;
}

Image* loadImageMenuScaled(SDL_Renderer* renderer, const char* path, double ratio) {
    char full_path[1024];
    snprintf(full_path, 1024, "menu/%s", path);
    return loadImageScaled(renderer, full_path, ratio);
}

Image* loadImageSystemScaled(SDL_Renderer* renderer, const char* path, double ratio) {
    char full_path[1024];
    snprintf(full_path, 1024, "system/%s", path);
    return loadImageScaled(renderer, full_path, ratio);
}

Image* loadImage(SDL_Renderer* renderer, const char* path){
    return loadImageScaled(renderer, path, 1);
}

Image* loadImageMenu(SDL_Renderer* renderer, const char* path){
    return loadImageMenuScaled(renderer, path, 1);
}

Image* loadImageSystem(SDL_Renderer* renderer, const char* path){
    return loadImageSystemScaled(renderer, path, 1);
}

void destroyImage(Image* image) {
    if (image) {
        if (image->texture) {
            SDL_DestroyTexture(image->texture);
        }
        free(image);
    }
}

void renderImage(SDL_Renderer* renderer, Image* image, int x, int y) {
    if (!image || !image->texture) return;
    
    SDL_Rect dest = {x, y, image->width, image->height};
    SDL_RenderCopy(renderer, image->texture, NULL, &dest);
}

void renderImageOrigin(SDL_Renderer* renderer, Image* image) {
    renderImage(renderer, image, 0, 0);
}

void renderScaledImage(SDL_Renderer* renderer, Image* image, int x, int y, int w, int h) {
    if (!image || !image->texture) return;
    
    SDL_Rect dest = {x, y, w, h};
    SDL_RenderCopy(renderer, image->texture, NULL, &dest);
    image->ratio = w;
}

void renderScaledImageOrigin(SDL_Renderer* renderer, Image* image, int w, int h) {
    renderScaledImage(renderer, image, 0, 0, w, h);
}

void renderScaledRatioImage(SDL_Renderer* renderer, Image* image, int x, int y, double ratio) {
    int new_w = image->width/ratio, new_h = image->height/ratio;
    renderScaledImage(renderer, image, x, y, new_w, new_h);
    image->ratio = ratio;
}

void renderScaledWidthImage(SDL_Renderer* renderer, Image* image, int x, int y, int w) {
    if (!image || !image->texture) return;
    
    SDL_Rect dest = {x, y, w, w * image->height / image->width};
    SDL_RenderCopy(renderer, image->texture, NULL, &dest);
    image->ratio = w;
}

void renderScaledWidthImageOrigin(SDL_Renderer* renderer, Image* image,  int w) {
    renderScaledWidthImage(renderer, image, 0, 0, w) ;
}

void renderScaleHeightImage(SDL_Renderer* renderer, Image* image, int x, int y, int h) {
    if (!image || !image->texture) return;

    SDL_Rect dest = {x, y, h * image->width / image->height, h};
    SDL_RenderCopy(renderer, image->texture, NULL, &dest);
    image->ratio = h;
}

void renderScaledHeightImageOrigin(SDL_Renderer* renderer, Image* image,  int h) {
    renderScaleHeightImage(renderer, image, 0, 0, h);
}