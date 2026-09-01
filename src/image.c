#include "image.h"

Image* loadImageRatio(SDL_Renderer* renderer, const char* path, double ratio) {
    if (!renderer) {
        printf("Erreur: renderer NULL\n");
        return NULL;
    }
    
    char full_path[2048];
    snprintf(full_path, sizeof(full_path), "%s/%s", getImagesPath(), path);
    
    SDL_Surface* surface = IMG_Load(full_path);
    if (!surface) {
        printf("Erreur chargement %s: %s\n", full_path, IMG_GetError());
        return NULL;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur création texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
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

Image* loadImageMenuRatio(SDL_Renderer* renderer, const char* path, double ratio) {
    char full_path[1024];
    snprintf(full_path, 1024, "menu/%s", path);
    return loadImageRatio(renderer, full_path, ratio);
}

Image* loadImageSystemRatio(SDL_Renderer* renderer, const char* path, double ratio) {
    char full_path[1024];
    snprintf(full_path, 1024, "system/%s", path);
    return loadImageRatio(renderer, full_path, ratio);
}

Image* loadImage(SDL_Renderer* renderer, const char* path){
    return loadImageRatio(renderer, path, 1);
}

Image* loadImageMenu(SDL_Renderer* renderer, const char* path){
    return loadImageMenuRatio(renderer, path, 1);
}

Image* loadImageSystem(SDL_Renderer* renderer, const char* path){
    return loadImageSystemRatio(renderer, path, 1);
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