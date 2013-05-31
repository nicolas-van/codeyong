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
#include "sdlw_font.hpp"
#include <fstream>
#include <iostream>

namespace sdlw {

	inline TTF_Font* font::get_low(){
		if( this->low.get()==NULL || this->low->ptr==NULL)
			throw exception_sdl("The low level surface does not exist");
		return this->low->ptr;
	}

	font& font::build(TTF_Font* ptrr,auto_ptr<vector<char> > mem) {
		TTF_Font * ptr= (TTF_Font *)ptrr;
		if(ptr==NULL) {
			throw exception_sdl();
		}
		auto_ptr<font_low> low(new font_low());
		low->ptr=ptr;
		low->mem=mem;
		this->low = boost::shared_ptr<font_low>(low);
		return *this;
	}

	font font::open_font(std::string filename, int ptsize,long index) {
		ifstream thefile(filename.c_str(),ios::in|ios::binary);
		font thefont = open_font(thefile,ptsize,index);
		thefile.close();
		return thefont;
	}

	font font::open_font(istream& thefile,int ptsize,long index) {
		thefile.seekg(0,ios::end);
		int filesize=thefile.tellg();
		thefile.seekg(0,ios::beg);
		auto_ptr<vector<char> > filecont(new vector<char>(filesize));
		thefile.read(&(*filecont)[0],filesize);
		SDL_RWops* wop=SDL_RWFromConstMem(&(*filecont)[0],filesize);
		TTF_Font* thefont = TTF_OpenFontIndexRW(wop,true,ptsize,index);
		return font().build(thefont,filecont);
	}

	surface font::render_solid(std::string str, color c) {
		return surface().build(TTF_RenderText_Solid(get_low()
			,str.c_str()
			,color::exchange_color<SDL_Color>(c)));
	}

	surface font::render_shaded(std::string str, color c,color background) {
		return surface().build(TTF_RenderText_Shaded(get_low()
			,str.c_str()
			,color::exchange_color<SDL_Color>(c),color::exchange_color<SDL_Color>(background)));
	}

	surface font::render_blended(std::string str, color c) {
		return surface().surface::build(TTF_RenderText_Blended(get_low()
			,str.c_str()
			,color::exchange_color<SDL_Color>(c)));
	}


	surface font::render_solid(std::basic_string<uint16_t> str, color c) {
		return surface().build(TTF_RenderUNICODE_Solid(get_low()
			,str.c_str()
			,color::exchange_color<SDL_Color>(c)));
	}

	surface font::render_shaded(std::basic_string<uint16_t> str, color c,color background) {
		return surface().build(TTF_RenderUNICODE_Shaded(get_low()
			,str.c_str()
			,color::exchange_color<SDL_Color>(c),color::exchange_color<SDL_Color>(background)));
	}

	surface font::render_blended(std::basic_string<uint16_t> str, color c) {
		return surface().surface::build(TTF_RenderUNICODE_Blended(get_low()
			,str.c_str()
			,color::exchange_color<SDL_Color>(c)));
	}

	font_style font::get_font_style() {
		int style = TTF_GetFontStyle(get_low());
		font_style s;
		s.bold=style&TTF_STYLE_BOLD?true:false;
		s.italic=style&TTF_STYLE_ITALIC?true:false;
		s.underline=style&TTF_STYLE_UNDERLINE?true:false;
		return s;
	}

	void font::set_font_style(font_style style) {
		int s=0;
		if(style.bold)
			s=s|TTF_STYLE_BOLD;
		if(style.italic)
			s=s|TTF_STYLE_ITALIC;
		if(style.underline)
			s=s|TTF_STYLE_UNDERLINE;
		TTF_SetFontStyle(get_low(),s);
	}

}
