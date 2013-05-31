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
#define SDLW_LOW_IMP
#include "sdlw_pixel_format.hpp"
#include <SDL/SDL.h>

namespace sdlw {

	inline SDL_Surface* pixel_format::get_low(){
		if(this->low.expired() || this->low.lock()->ptr==NULL)
			throw exception_sdl("The low level pixel format does not exist");
		return this->low.lock()->ptr;
	}

	uint32_t pixel_format::map_rgba(color c) {
		SDL_Surface* ptr = get_low();
		return SDL_MapRGBA(ptr->format,c.r,c.g,c.b,c.a);
	}

	uint32_t pixel_format::map_rgb(sdlw::color c) {
		SDL_Surface* ptr = get_low();
		return SDL_MapRGB(ptr->format,c.r,c.g,c.b);
	}

	uint8_t pixel_format::get_bits_per_pixel(){return get_low()->format->BitsPerPixel;}
	uint8_t pixel_format::get_bytes_per_pixel(){return get_low()->format->BytesPerPixel;}
	uint8_t pixel_format::get_rloss(){return get_low()->format->Rloss;}
	uint8_t pixel_format::get_gloss(){return get_low()->format->Gloss;}
	uint8_t pixel_format::get_bloss(){return get_low()->format->Bloss;}
	uint8_t pixel_format::get_aloss(){return get_low()->format->Aloss;}
	uint8_t pixel_format::get_rshift(){return get_low()->format->Rshift;}
	uint8_t pixel_format::get_gshift(){return get_low()->format->Gshift;}
	uint8_t pixel_format::get_bshift(){return get_low()->format->Bshift;}
	uint8_t pixel_format::get_ashift(){return get_low()->format->Ashift;}
	uint8_t pixel_format::get_alpha(){return get_low()->format->alpha;}
	uint32_t pixel_format::get_rmask(){return get_low()->format->Rmask;}
	uint32_t pixel_format::get_gmask(){return get_low()->format->Gmask;}
	uint32_t pixel_format::get_bmask(){return get_low()->format->Bmask;}
	uint32_t pixel_format::get_amask(){return get_low()->format->Amask;}
	uint32_t pixel_format::get_colorkey(){return get_low()->format->colorkey;}
	uint32_t pixel_format::get_flags(){return get_low()->flags;}


}

