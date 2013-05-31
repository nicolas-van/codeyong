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
#include "Application.hpp"
#include <fstream>
#include <functional>
#include "logger.hpp"
#include "formatters.hpp"

Application Application::application;

void Application::Main(vector<string>) {
	try{

		Application::application = Application();

		sdlw::init();

		log::logger log;
		log.handlers().connect(log::console_handler());
		log.handlers().connect(log::file_handler("truc.txt"));
		log.formatters().connect(log::level_formatter());
		log.trace() << endl << string("bidule") << "truc" << endl << "salut le monde!!!" << "re salut!!!";

		this->mainSurf=sdlw::surface::set_video_as_hard_dbl(800,600);

		this->renderer.back = sdlw::surface::load("othello.jpg");
		this->renderer.white = sdlw::surface::load("white.png").to_display_format().set_color_key(color::magenta());
		this->renderer.black = sdlw::surface::load("black.png").to_display_format().set_color_key(color::magenta());
		this->renderer.thefont = sdlw::font::open_font("com",40);
		font_style style;
		style.bold=true;
		this->renderer.thefont.set_font_style(style);

		renderer.render(this->mainSurf,this->plateau);

		events::manager.mouse_button_down_listener.connect(bind1st(mem_fun(&Application::click),this));

		// iteration
		events::manager.iterate_events();

		sdlw::quit();

	} catch( exception & e ) {
		cout << e.what() << endl;
	}
}

void Application::click(SDL_MouseButtonEvent evt) {
	bool valid = true;
	Case tcase;
	try {
		tcase=this->renderer.getCaseByCoordinate(evt.x,evt.y);
	} catch(othelloException&) {
		valid = false;
	}
	if(valid) {
		bool good=true;
		try {
			this->plateau=plateau.putPion(tcase,Pion::white());
		} catch (othelloException &) {
			good=false;
		}
		if(good) {
			this->renderer.render(this->mainSurf,this->plateau);
			do {
				if(this->plateau.canDoCoup(Pion::black())) {
					computerPlay(this->plateau,Pion::black());
					this->renderer.render(this->mainSurf,this->plateau);
				} else
					break;
			} while (!this->plateau.canDoCoup(Pion::white()));
		}
		if(this->plateau.gameFinished())
				return;
	}
}




