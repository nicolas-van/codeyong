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
#include <string>
#include <vector>
#include "Application.hpp"
#include "logger.hpp"



using namespace std;

int cpp_main(int argc,char** argv) {
    return main(argc,argv);
}

int main(int argc,char** argv) {
	vector<string> args(argc);
	for(int i=0;i<argc;i++) {
		args[i]=argv[i];
	}
	Application::application.Main(args);
	return 0;
}
