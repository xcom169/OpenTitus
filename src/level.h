/*   
 * Copyright (C) 2008 - 2011 The OpenTitus team
 *
 * Authors:
 * Eirik Stople
 *
 * "Titus the Fox: To Marrakech and Back" (1992) and
 * "Lagaf': Les Aventures de Moktar - Vol 1: La Zoubida" (1991)
 * was developed by, and is probably copyrighted by Titus Software,
 * which, according to Wikipedia, stopped buisness in 2005.
 *
 * OpenTitus is not affiliated with Titus Software.
 *
 * OpenTitus is  free software; you can redistribute  it and/or modify
 * it under the  terms of the GNU General  Public License as published
 * by the Free  Software Foundation; either version 3  of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
 * MERCHANTABILITY or  FITNESS FOR A PARTICULAR PURPOSE.   See the GNU
 * General Public License for more details.
 */

/* level.h
 * Contains the OpenTitus level format structure, and level functions
 */

#pragma once

#include "SDL2/SDL.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct _TITUS_tile TITUS_tile;
typedef struct _TITUS_sprite TITUS_sprite;
typedef struct _TITUS_spritedata TITUS_spritedata;
typedef struct _TITUS_spritebuffer TITUS_spritebuffer;
typedef struct _TITUS_spritecache TITUS_spritecache;
typedef struct _TITUS_objectdata TITUS_objectdata;
typedef struct _TITUS_object TITUS_object;
typedef struct _TITUS_enemy TITUS_enemy;
typedef struct _TITUS_bonus TITUS_bonus;
typedef struct _TITUS_gate TITUS_gate;
typedef struct _TITUS_elevator TITUS_elevator;
typedef struct _TITUS_player TITUS_player;
typedef struct _TITUS_level TITUS_level;

struct _TITUS_tile {
    SDL_Surface *tiledata; //Malloced
    uint8_t animation[3]; //Index to animation tiles
    bool animated;
    uint8_t horizflag;
    uint8_t floorflag;
    uint8_t ceilflag;
    uint8_t current; //Index of the current (animated) tile
};

struct _TITUS_sprite {
    int16_t x;
    int16_t y;
    int16_t speedX;
    int16_t speedY;
    int16_t number;
    bool visible; //On screen or not on screen (above/below/left/right)
    bool flash;
    bool flipped;
    //bool flash_last;
    //bool flipped_last;
    bool enabled;
    //SDL_Surface *buffer; //Malloced
    TITUS_spritedata *spritedata;
    uint8_t UNDER; //0: big spring, 1: small spring because of another object on top, 2: small spring because player on top
    TITUS_sprite *ONTOP; //Object on top of the spring
    int16_t *animation;
    bool droptobottom;
    bool killing;
    bool invisible; //Set by "hidden" enemies
};

struct _TITUS_spritedata {
    SDL_Surface *data; //Malloced
    uint8_t collheight;
    uint8_t collwidth;
    int16_t refheight;
    uint8_t refwidth;
    TITUS_spritebuffer *spritebuffer[1]; //Not malloced
};

struct _TITUS_spritebuffer {
    SDL_Surface *data; //Malloced
    TITUS_spritedata *spritedata;
    uint8_t index;
};

struct _TITUS_spritecache {
    TITUS_spritebuffer **spritebuffer; //Malloced
    uint16_t count;
    uint16_t tmpcount;
    uint16_t cycle;
    uint16_t cycle2;
};

struct _TITUS_objectdata {
    uint8_t maxspeedY;
    bool support; //not support/support
    bool bounce; //not bounce/bounce against floor + player bounces (ball, all spring, yellow stone, squeezed ball, skateboard)
    bool gravity; //no gravity on throw/gravity (ball, all carpet, trolley, squeezed ball, garbage, grey stone, scooter, yellow bricks between the statues, skateboard, cage)
    bool droptobottom; //on drop, lands on ground/continue below ground(cave spikes, rolling rock, ambolt, safe, dead man with helicopter)
    bool no_damage; //weapon/not weapon(cage)
};

struct _TITUS_object {
    TITUS_sprite sprite;
    //unsigned char animcycle;
    uint16_t initsprite;
    int initX;
    int initY;
    //unsigned char initanimcycle;
    bool init_enabled;
    uint8_t mass; //momentum, must be >= 10 to cause a falling object to hit an enemy or the player
    TITUS_objectdata *objectdata;
};

struct _TITUS_enemy {
    uint8_t dying; //00: alive, not 00: dying/dead
    uint8_t phase; //the current phase of the enemy
    TITUS_sprite sprite;
    uint16_t type; //What kind of enemy
    int16_t power;
    int centerX;
    unsigned int rangeX;
    unsigned int delay;
    unsigned char direction;
    unsigned int rangeY;
    uint16_t initsprite;
    int initX;
    int initY;
    bool init_enabled;
    int initspeedX;
    int initspeedY;
    int16_t carry_sprite;
    int16_t dead_sprite;
    bool boss;
    bool trigger;
    bool visible;
    uint8_t counter;
    uint8_t walkspeedX;
};

struct _TITUS_bonus {
    unsigned char exists;
    unsigned char bonustile;
    unsigned char replacetile;
    int x;
    int y;
};

struct _TITUS_gate {
    unsigned char exists;
    unsigned int entranceX;
    unsigned int entranceY;
    unsigned int exitX;
    unsigned int exitY;
    unsigned int screenX;
    unsigned int screenY;
    bool noscroll;
};

struct _TITUS_elevator {
    bool enabled;
    TITUS_sprite sprite;
    unsigned int counter;
    unsigned int range;
    unsigned char init_direction;
    bool init_enabled;
    int16_t initspeedX;
    int16_t initspeedY;
    uint16_t initsprite;
    int initX;
    int initY;
};

struct _TITUS_player {
    TITUS_sprite sprite;
    TITUS_sprite sprite2;
    TITUS_sprite sprite3;
    unsigned char animcycle;
    int16_t cageX;
    int16_t cageY;
    int16_t hp;
    int16_t initX;
    int16_t initY;
    unsigned char inithp;
    uint8_t GLISSE; //Friction (0-3). 0: full friction, 3: max sliding

    // Player input this frame
    int8_t x_axis;
    int8_t y_axis;
    bool action_pressed;
};

struct _TITUS_level {
    uint16_t levelnumber;
    uint16_t levelid;
    //char title[41];
    int16_t height;
    int16_t width; //Usually 256
    unsigned char **tilemap; //Malloced, usually 256 * height
    TITUS_tile tile[256];
    TITUS_spritedata **spritedata; //Not malloced (on an original level); pointer to a global spritedata variable
    TITUS_spritecache *spritecache; //Not malloced (on an original level); pointer to a global spritebuffer variable

    TITUS_objectdata **objectdata; //Not malloced (on an original level); pointer to a global objectdata variable
    int finishX, finishY;
    int lives, extrabonus;
    //TITUS_enemy *boss; //Pointer to the boss; NULL if there is no boss
    //TITUS_object *finish_object; //Pointer to the required object to carry to finish; NULL if there is no such object
    SDL_PixelFormat *pixelformat; //Malloced

    TITUS_player player;

    TITUS_object *object; //Malloced
    size_t objectcount;
    TITUS_enemy *enemy; //Malloced
    size_t enemycount;
    TITUS_bonus *bonus; //Malloced
    size_t bonuscount;
    TITUS_gate *gate; //Malloced
    size_t gatecount;
    TITUS_elevator *elevator; //Malloced
    size_t elevatorcount;
    TITUS_sprite *trash; //Malloced
    size_t trashcount;

};

int loadlevel(TITUS_level *level, unsigned char *leveldata, int leveldatasize, TITUS_spritedata **spritedata, TITUS_spritecache *spritecache, TITUS_objectdata **objectdata);
void freelevel(TITUS_level *level);
uint8_t get_horizflag(TITUS_level *level, int16_t tileY, int16_t tileX);
uint8_t get_floorflag(TITUS_level *level, int16_t tileY, int16_t tileX);
uint8_t get_ceilflag(TITUS_level *level, int16_t tileY, int16_t tileX);
