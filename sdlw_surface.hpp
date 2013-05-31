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
#ifndef SDLW_SURFACE_HPP
#define SDLW_SURFACE_HPP

namespace sdlw {
	class surface;
}

#include "sdlw_exception.hpp"
#include <boost/cstdint.hpp>
#include "sdlw_surface_low.hpp"
#include "sdlw_pixel_format.hpp"
#include "sdlw_rectangle.hpp"
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include "sdlw_font.hpp"

namespace sdlw {

	/**
		The base class for surfaces.
	*/
	class surface {
	private:
		boost::shared_ptr<surface_low> low;
		static surface main_surface;
	public:
        /**
            Return the low level surface.
        */
		inline SDL_Surface* get_low();
		/**
            Init the surface object with a SDL_Surface.
        */
        surface& build(SDL_Surface*,bool shouldDestroy=true);
		/**
			Get the pixel format of this surface.
		*/
		pixel_format get_pixel_format();
		/**
			Copy this surface to another surface using the
			given Rects.
		*/
		void blit(rectangle srcrect, surface& dst, rectangle dstrect);
		/**
			Copy completely this surface to another surface using
			the given coordinates.
		*/
		void blit(surface & dst,int x,int y);
		/**
			Get the width of this surface.
		*/
		int get_width();
		/**
			Get the height of this surface.
		*/
		int get_height();
		/**
			Fill the given rectangle with the given color.
		*/
		void fill(rectangle rect,color color);
		/**
			Fill all the image with the given color.
		*/
		void fill(color color);
		/**
            Load an image from a stream.
        */
		/**
			Load an image from a file.
			See loadImage(std::streambuf*,bool,std::string) for more information.
		*/
		static surface load(std::string filename,std::string type="auto");
		/**
            Load an image form a stream.
			See loadImage(std::streambuf*,bool,std::string) for more information.
        */
        static surface load(std::istream& strea,std::string type="auto");
		/**
			Load an image from a buffer. The stream must be in binary mode. If 'convert' is
			true, this method will convert the loaded image to the current video format.
			This function can auto detect the type of the file except for tga files. You can
			also specify the type of the image by using one of these values for 'type':
			"TGA","BMP","PNM","XPM","XCF","PCX","GIF","JPG","TIF","LBM" and "PNG".
		*/
		static surface load(std::streambuf* buf,std::string type="auto");
		/**
			Create an empty surface with same pixel format that the main Surface.
		*/
		static surface create_surface(int w,int h);
		/**
			Create an empty surface with given pixel format.
		*/
		static surface create_surface(int w,int h,pixel_format& pf);
		/**
			Create an empty surface.
		*/
		static surface create_surface(uint32_t flags, int width, int height, int depth,
			uint32_t Rmask, uint32_t Gmask, uint32_t Bmask, uint32_t Amask);
		/**
			Create a video surface. It uses the same paramters than SDL_SetVideoMode().
		*/
		static surface& set_video_mode(int width, int height, int bpp, uint32_t flags);
		/**
			Create a video surface using hardware acceleration,
			24 bits pixels and double buffer. The height and width
			of this surface can be specified.
		*/
		static surface& set_video_as_hard_dbl(int width,int height,bool full_screen=false);
		/**
			Create a video surface using hardware acceleration,
			32 bits pixels and double buffer. The height and width
			of this surface can be specified.
		*/
		static surface& set_video_as_hard_dbl_alpha(int width,int height,bool full_screen=false);
		/**
			Return the main video surface if it was initialized.
		*/
		static surface& get_video_surface();
		/**
			Refresh the surface by fliping the two buffers.
		*/
		void flip();
		/**
			Convert to display format.
		*/
		surface to_display_format();
		/**
			Set the key color for transparency.
		*/
		surface& set_color_key(color key,bool rleaccel=true);

		/*
		// méthodes pas implémentées
		static SDL_VideoInfo * getVideoInfo();
		static std::string videoDriverName();
		static bool videoModeOK(int width, int height, int bpp, uint32_t flags);
		void updateRect(int32_t x, int32_t y, int32_t w, int32_t h);
		void updateRects(std::vector<SDL_Rect> & rects);
		void setColors(std::vector<SDL_Color> & colors);
		void setPalette(int flags,std::vector<SDL_Color> & colors);
		static void setGamma(float redgamma, float greengamma, float bluegamma);
		static std::vector<uint16_t> & getGammaRampRed();
		static std::vector<uint16_t> & getGammaRampGreen();
		static std::vector<uint16_t> & getGammaRampBlue();
		static void setGammaRamp(std::vector<uint16_t> & redtable,std::vector<uint16_t> & greentable,std::vector<uint16_t> & bluetable);

		Surface & convertSurface(Surface & src,PixelFormat & fmt, uint32_t flags);

		static Surface & createRGBSurface(uint32_t flags, int width, int height, int depth, uint32_t Rmask,
			uint32_t Gmask, uint32_t Bmask, uint32_t Amask);
		static Surface & createRGBSurfaceFrom(void *pixels, int width, int height, int depth, int pitch, uint32_t Rmask,
			uint32_t Gmask, uint32_t Bmask, uint32_t Amask);
		void lock();
		void unlock();
		void saveBMP(std::string);
		void setColorKey(uint32_t flag, uint32_t key);
		void setAlpha(uint32_t flag, uint8_t alpha);
		void setClipRect(SDL_Rect *rect);
		void getClipRect(SDL_Rect *rect);
		void fillrect(SDL_Rect *dstrect, uint32_t color);
		Surface & displayFormat(Surface & surface);
		Surface & displayFormatAlpha(Surface & surface);
		// fin méthodes pas implémentées
		*/
	};
}


#endif

