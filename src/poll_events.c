#include "poll_events.h"

int poll_events(SDL_Event* event){
    int running = 1;
    while (SDL_PollEvent(event)) {
            if (event->type == SDL_QUIT)
                running = 0;
        }
    printf("running: %d\n", running);
    return running;
}