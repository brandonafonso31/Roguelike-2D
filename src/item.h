#ifndef ITEM_H
#define ITEM_H

#define MAX_NAME_LENGTH 32

typedef enum {
    ITEM_WEAPON,
    ITEM_ARMOR,
    ITEM_HEALING,
    ITEM_KEY,
} ItemType;

typedef struct {
    ItemType type;
    char name[MAX_NAME_LENGTH];
    char description[MAX_NAME_LENGTH*4];
    int value;
    int rarity;       // 0=commun, 1=rare, 2=épique, 3=légendaire
} Item;

typedef struct {
    Item base;
    int damage;
    int attack_speed;
    int range;
} Weapon;

typedef struct {
    Item base;
    int defense;
    int weight;
} Armor;

typedef struct {
    Item base;
    int heal_hp;
    int heal_mp;
    int duration;
} HealingItem;

typedef struct {
    Item base;
    // add a way to describe an imporant event or something ...
}KeyItem;

#endif