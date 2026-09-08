#ifndef STATE_H
#define STATE_H

typedef struct {
    int hp;
    int atk;
    int def;
    int speed;
    int atk_speed;
} Statistics;

Statistics* setBasicStats();

#endif