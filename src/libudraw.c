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

#include "../include/libudraw/libudraw.h"

SDL_Surface *_surface;
int _scale, _w, _h, _fps;
Uint32 _last_t;
Uint8 *_kbuffer;

void uInit(int w, int h, const char *title, int scale, int fps) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        puts("[uDraw] Failed to initialize the SDL !");
        exit(-1);
    }
    SDL_WM_SetCaption(title, title);
    _surface = SDL_SetVideoMode(w*scale, h*scale, 32, 0);
    if(!_surface){
        puts("[uDraw] Failed to get the surface from the SDL window !");
        exit(-1);
    }
    if(SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL) < 0){
        puts("[uDraw] Can't enable key repeat !");
        exit(-1);
    }
    _w = w;
    _h = h;
    _scale = scale;
    _fps = fps;
    if(_scale<1){
    	_scale = 1;
    }
    if(_fps<1){
    	_fps = 50;
    }
    SDL_LockSurface(_surface);
    uClear();
    _last_t = SDL_GetTicks();
}

void uClear(void) {
    SDL_FillRect(_surface, NULL, 0x00000000);
}

void uPixel(int x, int y, uint32_t color) {
    Uint32 *target_pixel;
    int sx, sy;
    if(x>=0 && x<_w && y>=0 && y<_h){
        for(sy=0;sy<_scale;sy++){
            for(sx=0;sx<_scale;sx++){
                target_pixel = (Uint32 *)((Uint8 *)_surface->pixels +
                (y*_scale+sy) * _surface->pitch + (x*_scale+sx) *
                _surface->format->BytesPerPixel);
                *target_pixel = color;
            }
        }
    }
}

void uShow(void) {
    SDL_UnlockSurface(_surface);
    SDL_Flip(_surface);
    SDL_LockSurface(_surface);
}

bool uAskexit(void) {
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            return 1;
        }
    }
    return 0;
}

bool uKeydown(int key) {
    SDL_PumpEvents();
    _kbuffer = SDL_GetKeyState(NULL);
    return _kbuffer[key];
}

void uWaitnextframe(void) {
    Uint32 ticks;
    if(SDL_GetTicks() <= _last_t){
        _last_t = SDL_GetTicks();
        return;
    }
    ticks = 1000/(Uint32)_fps;
    while(SDL_GetTicks() - _last_t < ticks);
    _last_t = SDL_GetTicks();
}

void uDeinit(void) {
    SDL_FreeSurface(_surface);
    SDL_Quit();
}
