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

/* sprites.h
 * Sprite functions
 */

#pragma once
#include "SDL2/SDL.h"

#include "level.h"
#include <stdbool.h>
#include <stdint.h>

// TODO: port level.c to get rid of these
SDL_Surface * load_tile_c(unsigned char * first, int i, SDL_PixelFormat * pixelformat);
void flush_sprite_cache_c();
void copypixelformat(SDL_PixelFormat * destformat, SDL_PixelFormat * srcformat);
void updatesprite(TITUS_level *level, TITUS_sprite *spr, int16_t number, bool clearflags);
void copysprite(TITUS_level *level, TITUS_sprite *dest, TITUS_sprite *src);

void SPRITES_ANIMATION(TITUS_level *level);
