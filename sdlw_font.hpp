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

#ifndef SDLW_FONT_HPP
#define SDLW_FONT_HPP

namespace sdlw {
	class font;
}

#include "sdlw_font_low.hpp"
#include <boost/shared_ptr.hpp>
#include "sdlw_exception.hpp"
#include <string>
#include "sdlw_surface.hpp"
#include "sdlw_color.hpp"


using namespace std;

namespace sdlw {

	struct font_style {
		bool bold;
		bool italic;
		bool underline;
		font_style():bold(false),italic(false),underline(false) {}
		font_style(bool bold2,bool italic2,bool underline2)
            :bold(bold2),italic(italic2),underline(underline2) {}
	};

	class font {
	private:
		boost::shared_ptr<font_low> low;
	public:
		inline TTF_Font* get_low();
		font& build(TTF_Font*,auto_ptr<vector<char> >);
		static font open_font(string filename,int ptsize,long index=0);
		static font open_font(istream& stream,int ptsize,long index=0);
		surface render_solid(string str,color c);
		surface render_shaded(string str,color c,color background);
		surface render_blended(string str,color c);
		surface render_solid(std::basic_string<uint16_t> str,color c);
		surface render_shaded(std::basic_string<uint16_t> str,color c,color background);
		surface render_blended(std::basic_string<uint16_t> str,color c);

		font_style get_font_style();
		void set_font_style(font_style style);
	};

}

#endif

