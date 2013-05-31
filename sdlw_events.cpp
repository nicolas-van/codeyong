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
#include "sdlw_events.hpp"

namespace sdlw {

#define SDLW_STOPEVENT 159

	events events::manager;

	void events::stop() {
		SDL_Event evt;
		evt.type=SDLW_STOPEVENT;
		if(SDL_PushEvent(&evt)<0)
			throw exception_sdl();
	}

	void events::iterate_events() {
		bool shouldContinue=true;
		while(shouldContinue) {
			SDL_Event evt;
			if(SDL_WaitEvent(&evt)<1)
				throw exception_sdl();
			if(evt.type!=SDLW_STOPEVENT)
				before_all_listener(evt);
			switch(evt.type) {
				case SDL_ACTIVEEVENT:active_listener(evt.active);break;
				case SDL_KEYDOWN:key_down_listener(evt.key);break;
				case SDL_KEYUP:key_up_listener(evt.key);break;
				case SDL_MOUSEMOTION:mouse_motion_listener(evt.motion);break;
				case SDL_MOUSEBUTTONDOWN:mouse_button_down_listener(evt.button);break;
				case SDL_MOUSEBUTTONUP:mouse_button_up_listener(evt.button);break;
				case SDL_JOYAXISMOTION:joy_axis_listener(evt.jaxis);break;
				case SDL_JOYBALLMOTION:joy_ball_listener(evt.jball);break;
				case SDL_JOYHATMOTION:joy_hat_listener(evt.jhat);break;
				case SDL_JOYBUTTONDOWN:joy_button_down_listener(evt.jbutton);break;
				case SDL_JOYBUTTONUP:joy_button_up_listener(evt.jbutton);break;
				case SDL_QUIT:
					if(auto_close)
						stop();
					else
						quit_listener(evt.quit);
					break;
				case SDL_SYSWMEVENT:sys_wm_listener(evt.syswm);break;
				case SDL_VIDEORESIZE:resize_listener(evt.resize);break;
				case SDL_VIDEOEXPOSE:expose_listener(evt.expose);break;
				case SDL_USEREVENT:user_listener(evt.user);break;
				case SDLW_STOPEVENT:shouldContinue=false;break;
			}
			if(evt.type!=SDLW_STOPEVENT)
				after_all_listener(evt);
		}
	}

}

