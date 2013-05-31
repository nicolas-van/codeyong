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

#ifndef SDLW_PIXELFORMAT_HPP
#define SDLW_PIXELFORMAT_HPP

#include <boost/weak_ptr.hpp>
#include <vector>
#include "sdlw_color.hpp"
#include <boost/cstdint.hpp>

namespace sdlw {
	class pixel_format;
}

#include "sdlw_surface.hpp"

namespace sdlw {

	/**
		Represents the format of a Surface.
	*/
	class pixel_format {
	private:
		boost::weak_ptr<surface_low> low;
	protected:
		pixel_format() {};
	public:
		friend class surface;

		inline SDL_Surface* get_low();
		/**
			Convert a color into a uint32_t with alpha using this
			format.
		*/
		uint32_t map_rgba(sdlw::color c);
		/**
			Convert a color into a uint32_t using this
			format.
		*/
		uint32_t map_rgb(sdlw::color c);
		uint8_t get_bits_per_pixel();
		uint8_t get_bytes_per_pixel();
		uint8_t get_rloss();
		uint8_t get_gloss();
		uint8_t get_bloss();
		uint8_t get_aloss();
		uint8_t get_rshift();
		uint8_t get_gshift();
		uint8_t get_bshift();
		uint8_t get_ashift();
		uint8_t get_alpha();
		uint32_t get_rmask();
		uint32_t get_gmask();
		uint32_t get_bmask();
		uint32_t get_amask();
		uint32_t get_colorkey();
		uint32_t get_flags();

		/*
		std::vector<SDL_Rect *> & listModes(uint32_t flags);
		uint32_t mapRGB(uint8_t r, uint8_t g, uint8_t b);
		uint8_t getRGBRed(uint32_t pixel);
		uint8_t getRGBGreen(uint32_t pixel);
		uint8_t getRGBBlue(uint32_t pixel);
		uint8_t getRGBAlpha(uint32_t pixel);
		*/
	};
}

#endif
