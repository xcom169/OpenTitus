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

/* original.h
 * Contains data from the original game
 */

#pragma once

#include "SDL2/SDL.h"

#include <stdbool.h>
#include <stdint.h>


void initoriginal();
uint16_t getlevelid(uint16_t levelnumber);

#define SPRITECOUNT 356
extern uint8_t spritewidth[SPRITECOUNT];
extern uint8_t spriteheight[SPRITECOUNT];
extern uint8_t spritecollwidth[SPRITECOUNT];
extern uint8_t spritecollheight[SPRITECOUNT];
extern uint8_t spriterefwidth[SPRITECOUNT];
extern uint8_t spriterefheight[SPRITECOUNT];

#define ANIM_PLAYER_MAX 15
#define ANIM_PLAYER_COUNT 30
extern int16_t anim_player[ANIM_PLAYER_COUNT][ANIM_PLAYER_MAX];

#define NMI_ANIM_TABLE_COUNT 879 //1758
extern int16_t anim_enemy[NMI_ANIM_TABLE_COUNT];

#define ORIG_LEVEL_COUNT 20
extern uint8_t NMI_POWER[ORIG_LEVEL_COUNT];
extern uint8_t LEVEL_MUSIC[ORIG_LEVEL_COUNT];

#define ORIG_ANIM_MAX 20
extern int16_t anim_zoubida[ORIG_ANIM_MAX];
extern int16_t anim_moktar[ORIG_ANIM_MAX];
extern int16_t anim_smoke[ORIG_ANIM_MAX];

#define ORIG_OBJECT_COUNT 71
