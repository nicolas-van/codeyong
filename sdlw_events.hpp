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

#ifndef SDLW_EVENTS_HPP
#define SDLW_EVENTS_HPP

#include <SDL/SDL.h>
#include "sdlw_exception.hpp"
#include <boost/signal.hpp>
#include <boost/cstdint.hpp>

namespace sdlw {

	/**
		A clazs containing many boost::signals that can catch
		events from SDL. This class is a singleton, see
		Events::manager.
	*/
	class events {
	private:
		bool auto_close;
		events() : auto_close(true) {};
	public:
		/**
			The only instance of Events.
		*/
		static events manager;

		/**
			Blocking function, it wait for events from SDL
			and redirect them to the many boost::signals.
		*/
		void iterate_events();

		/**
			Default is true. If true, the function "stop()" is called
			when a QuitEvent is launched.
		*/
		void set_auto_close(bool autoclose) {this->auto_close=autoclose;}
		bool get_auto_close() {return auto_close;}

		/**
			Stop the iteration over events. This function should
			only be called within an event handler.
		*/
		void stop();

		/**
			Throw every type of event before all the other signals.
		*/
		boost::signal<void (SDL_Event)> before_all_listener;
		/**
			Throw every type of event after all the other signals.
		*/
		boost::signal<void (SDL_Event)> after_all_listener;

		boost::signal<void (SDL_ActiveEvent)> active_listener;
		boost::signal<void (SDL_KeyboardEvent)> key_down_listener;
		boost::signal<void (SDL_KeyboardEvent)> key_up_listener;
		boost::signal<void (SDL_MouseMotionEvent)> mouse_motion_listener;
		boost::signal<void (SDL_MouseButtonEvent)> mouse_button_down_listener;
		boost::signal<void (SDL_MouseButtonEvent)> mouse_button_up_listener;
		boost::signal<void (SDL_JoyAxisEvent)> joy_axis_listener;
		boost::signal<void (SDL_JoyBallEvent)> joy_ball_listener;
		boost::signal<void (SDL_JoyHatEvent)> joy_hat_listener;
		boost::signal<void (SDL_JoyButtonEvent)> joy_button_down_listener;
		boost::signal<void (SDL_JoyButtonEvent)> joy_button_up_listener;
		boost::signal<void (SDL_QuitEvent)> quit_listener;
		boost::signal<void (SDL_SysWMEvent)> sys_wm_listener;
		boost::signal<void (SDL_ResizeEvent)> resize_listener;
		boost::signal<void (SDL_ExposeEvent)> expose_listener;
		boost::signal<void (SDL_UserEvent)> user_listener;
	};

}

#endif
