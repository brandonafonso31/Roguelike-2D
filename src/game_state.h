#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    STATE_MAIN_MENU = 0,
    STATE_IN_GAME_MENU,
    STATE_GAME_PLAY,
    STATE_GAME_PAUSE,
    STATE_GAME_OVER,
    STATE_QUIT
} GameState;

#endif