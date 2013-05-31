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
#ifndef SDLW_COLOR_HPP
#define SDLW_COLOR_HPP

#include <boost/cstdint.hpp>

namespace sdlw {

	struct color {
		public:
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		color() {
			*this=color(0,0,0);
		}
		color(uint8_t r,uint8_t g,uint8_t b, uint8_t a = opaque()) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}
		/**
			Convert to uint32_t using the main VideoSurface's PixelFormat.
		*/
		uint32_t map_rgba();
		/**
			Convert to uint32_t using the main VideoSurface's PixelFormat.
		*/
		uint32_t map_rgb();

		/**
			Return the component for transparent.
		*/
		static uint8_t transparent();
		/**
			Return the component for opaque.
		*/
		static uint8_t opaque();

		static color black(){return color(0,0,0);}
		static color red(){return color(255,0,0);}
		static color green(){return color(0,255,0);}
		static color blue(){return color(0,0,255);}
		static color yellow(){return color(255,255,0);}
		static color cyan(){return color(0,255,255);}
		static color magenta(){return color(255,0,255);}
		static color grey(){return color(192,192,192);}
		static color white(){return color(255,255,255);}

		template <typename D,typename S>
		static D exchange_color(const S& s)
		{
			D d;
			d.r=s.r;
			d.g=s.g;
			d.b=s.b;
			return d;
		}
	};

}



#endif
