// game_state.h
#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef enum {
    // États des menus
    STATE_MAIN_MENU,          // Menu principal (avant le jeu)
    STATE_INGAME_MENU,        // Interface du jeu (après lancement)
    
    // États du jeu
    STATE_GAME_PLAY,          // Le jeu lui-même (monde, combat)
    STATE_GAME_PAUSE,         // Pause
    STATE_GAME_OVER,          // Game Over
    
    // Autres
    STATE_SETTINGS,           // Options
    STATE_QUIT                // Quitter
} GameState;

#endif