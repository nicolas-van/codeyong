/*
	Yong Master: a small game that looks like othello.
	Copyright (C) 2006 Nicolas Vanhoren

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

	Nicolas Vanhoren
	nicolasvnh-0@yahoo.fr
*/
#include "sdlw_init.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

namespace sdlw {

	void init() {
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)<0)
		   throw exception_sdl();
		if(TTF_Init()==-1)
			throw exception_sdl();
	}

	void quit() {
		TTF_Quit();
		SDL_Quit();
	}
}

