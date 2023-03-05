/*
 * libuDraw - Simple lib. to draw in a SDL 1.2 window.
 * Copyright (C) 2023  Mibi88
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/.
 */

#ifndef LIBUDRAW_H
#define LIBUDRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL/SDL.h>

enum {
    KUP    = SDLK_UP,
    KDOWN  = SDLK_DOWN,
    KLEFT  = SDLK_LEFT,
    KRIGHT = SDLK_RIGHT,
    KVALID = SDLK_SPACE
};
#define KEYAMOUNT 8

void uInit(int w, int h, const char *title, int scale, int fps);
void uClear(uint32_t color);
void uPixel(int x, int y, uint32_t color);
void uShow(void);
bool uAskexit(void);
bool uKeydown(int key);
void uWaitnextframe(void);
void uDeinit(void);

#endif
