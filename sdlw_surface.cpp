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
#include "sdlw_surface.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fstream>
#include "sdlw_stream.hpp"
#include <memory>

using namespace std;

namespace sdlw {

	surface surface::main_surface;

	inline SDL_Surface* surface::get_low(){
		if( this->low.get()==NULL || this->low->ptr==NULL)
			throw exception_sdl("The low level surface does not exist");
		return this->low->ptr;
	}

	surface& surface::build(SDL_Surface* ptr,bool shouldDestroy) {
		if(ptr==NULL)
			throw exception_sdl();
		auto_ptr<surface_low> low(new surface_low());
		low->ptr=ptr;
		low->should_destroy=shouldDestroy;
		this->low = boost::shared_ptr<surface_low>(low);
		return *this;
	}

	pixel_format surface::get_pixel_format(){
		get_low();
		pixel_format format;
		format.low = boost::weak_ptr<surface_low>(this->low);
		return format;
	}

	void surface::blit(rectangle srcrect, surface& dst, rectangle dstrect) {
		SDL_Surface* ptr = get_low();
		SDL_Rect srcr = rectangle::exchange_rect<SDL_Rect>(srcrect);
		SDL_Rect dstr = rectangle::exchange_rect<SDL_Rect>(dstrect);
		SDL_Surface* ptrd = dst.get_low();
		if(SDL_BlitSurface(ptr,&srcr,ptrd,&dstr)<0)
			throw exception_sdl();
	}

	void surface::blit(surface& dst,int x,int y) {
		rectangle srcrect;
		rectangle dstrect;
		srcrect.h=this->get_height();
		srcrect.w=this->get_width();
		srcrect.x=0;
		srcrect.y=0;
		dstrect.h=this->get_height();
		dstrect.w=this->get_width();
		dstrect.x=x;
		dstrect.y=y;
		this->blit(srcrect,dst,dstrect);
	}

	int surface::get_width() {
		SDL_Surface* ptr = get_low();
		return ptr->w;
	}

	int surface::get_height(){
		SDL_Surface* ptr = get_low();
		return ptr->h;
	}

	void surface::fill(rectangle rect,color col) {
		SDL_Surface* ptr = get_low();
		SDL_Rect r = rectangle::exchange_rect<SDL_Rect>(rect);
		uint32_t c = col.map_rgba();
		if(SDL_FillRect(ptr,&r,c)==-1)
			throw exception_sdl();
	}

	void surface::fill(color color) {
		rectangle r(0,0,get_height(),get_width());
		fill(r,color);
	}

	surface surface::load(std::string filename,string type) {
		std::ifstream strea(filename.c_str(),ios::binary|ios::in);
		surface surf = sdlw::surface::load(strea.rdbuf(),type);
		strea.close();
		return surf;
	}

	surface surface::load(std::istream& strea,string type) {
		return load(strea.rdbuf(),type);
	}

	surface surface::load(std::streambuf* buf,string type) {
		surface surface;
		SDL_RWops* wop = build_rwops_stream(buf);
		struct noname {
            SDL_RWops* woop;
            ~noname() {
                if(woop!=NULL)
                    SDL_RWclose(woop);
            }
        } destroyer;
        destroyer.woop = wop;
		if(type=="auto")
			surface.build(IMG_Load_RW(wop,false));
		else
			surface.build(IMG_LoadTyped_RW(wop,false,(char*)type.c_str()));
        return surface;
		/*int beg = strea.tellg();
		strea.seekg(0,ios::end);
		int size = ((int)strea.tellg())-beg;
		strea.seekg(beg,ios::beg);
		vector<char> vec(size);
		strea.read(&vec[0],size);
		SDL_RWops* wop = SDL_RWFromConstMem(&vec[0],size);
		if(wop == NULL)
			throw exception_sdl();
		if(type=="auto")
			surface.build(IMG_Load_RW(wop,true));
		else
			surface.build(IMG_LoadTyped_RW(wop,true,(char*)type.c_str()));
		return surface;*/
	}

	surface surface::create_surface(int w, int h) {
		pixel_format pf = get_video_surface().get_pixel_format();
		return create_surface(w,h,pf);
	}

	surface surface::create_surface(int w, int h,pixel_format& pf) {
		return create_surface(pf.get_flags(),w,h,pf.get_bits_per_pixel()
			,pf.get_rmask(),pf.get_gmask(),pf.get_bmask(),pf.get_amask());
	}

	surface surface::create_surface(uint32_t flags, int width, int height, int depth,
		uint32_t Rmask, uint32_t Gmask, uint32_t Bmask, uint32_t Amask) {
		return surface().build(SDL_CreateRGBSurface(flags,width,height,depth
			,Rmask,Gmask,Bmask,Amask));
	}

	surface& surface::set_video_mode(int width, int height, int bpp, uint32_t flags) {
		main_surface.build(SDL_SetVideoMode(width,height,bpp,flags),false);
		return main_surface;
	}

	surface& surface::set_video_as_hard_dbl(int width,int height,bool full_screen) {
		uint32_t flags=SDL_HWSURFACE|SDL_DOUBLEBUF;
		if(full_screen)
			flags|=SDL_FULLSCREEN;
		return set_video_mode(width,height,24,flags);
	}

	surface& surface::set_video_as_hard_dbl_alpha(int width,int height,bool full_screen) {
		uint32_t flags=SDL_HWSURFACE|SDL_DOUBLEBUF;
		if(full_screen)
			flags|=SDL_FULLSCREEN;
		return set_video_mode(width,height,32,flags);
	}

	surface& surface::get_video_surface() {
		bool init=false;
		try {
			main_surface.get_low();
		} catch (sdlw::exception_sdl&) {
			init=true;
		}
		if(init)
			main_surface.build(SDL_GetVideoSurface(),false);
		return main_surface;
	}

	void surface::flip() {
		SDL_Surface* ptr = get_low();
		if(SDL_Flip(ptr)<0)
			throw exception_sdl();
	}

	surface surface::to_display_format() {
		return surface().build(SDL_DisplayFormat(get_low()));
	}

	surface& surface::set_color_key(color key,bool rleaccel) {
		SDL_Surface* ptr = get_low();
		int r;
		if(rleaccel)
			r=SDL_SetColorKey(ptr,SDL_SRCCOLORKEY|SDL_RLEACCEL,get_pixel_format().map_rgb(key));
		else
			r=SDL_SetColorKey(ptr,SDL_SRCCOLORKEY,get_pixel_format().map_rgb(key));
		if(r!=0)
			throw exception_sdl();
		return *this;
	}
}

