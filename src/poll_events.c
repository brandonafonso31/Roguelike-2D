#include "poll_events.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int poll_events(SDL_Event* event){
    int running = 1;
    while (SDL_PollEvent(event)) {
            if (event->type == SDL_QUIT)
                running = 0;
        }
    return running;
}