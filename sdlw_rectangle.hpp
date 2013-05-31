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
#ifndef SDLW_RECT_HPP
#define SDLW_RECT_HPP

#include <boost/cstdint.hpp>
#include "sdlw_coordinate.hpp"

namespace sdlw {

	/**
		A basic rectangle for blitting.
	*/
	struct rectangle {
		/**
			X coordinate.
		*/
		int16_t x;
		/**
			Y coordinate.
		*/
		int16_t y;
		/**
			Width of the rectangle.
		*/
		uint16_t w;
		/**
			Height of the rectangle.
		*/
		uint16_t h;

		rectangle(int16_t x,int16_t y,int16_t w,int16_t h) {
			this->x=x;this->y=y;this->w=w;this->h=h;
		}
		rectangle() {
			this->x=0;this->y=0;this->w=0;this->h=0;
		}
		rectangle(coordinate first,coordinate second) {
			set_coordinates(first,second);
		}
		rectangle(coordinate coord,int16_t w,int16_t h) {
			x=coord.x;
			y=coord.y;
			this->w=w;
			this->h=h;
		}
		coordinate get_upper_left_coordinate() {
			return coordinate(x,y);
		}
		coordinate get_lower_right_coordinate() {
			return coordinate(x+w,y+h);
		}
		rectangle& set_coordinates(coordinate first,coordinate second) {
			x=first.x<second.x?first.x:second.x;
			y=first.y<second.y?first.y:second.y;
			w=first.x>second.x?first.x-second.x:second.x-first.x;
			h=first.y>second.y?first.y-second.y:second.y-first.y;
			return *this;
		}
		rectangle& set_upper_left_coordinate(coordinate coord) {
			return set_coordinates(coord,get_lower_right_coordinate());
		}
		rectangle& set_lower_right_coordinate(coordinate coord) {
			return set_coordinates(get_upper_left_coordinate(),coord);
		}

		template <typename D,typename S>
		static D exchange_rect(S& s)
		{
			D d;
			d.x=s.x;
			d.y=s.y;
			d.w=s.w;
			d.h=s.h;
			return d;
		}
	};

}

#endif
