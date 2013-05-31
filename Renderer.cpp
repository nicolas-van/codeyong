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
#include "Renderer.hpp"
#include <boost/lexical_cast.hpp>

using namespace boost;

void Renderer::render(surface& surf, Plateau& plateau) {

	surf.fill(color::black());
	back.blit(surf,100,0);

	int blanc=0;
	int noir=0;
	for(size_t i=0;i<plateau.pions.size();i++) {
		for(size_t j=0;j<plateau.pions[i].size();j++) {
			if(plateau.pions[i][j]==Pion::black()) {
				black.blit(surf,100+((int)i*60),(int)j*60);
				noir++;
			} else if(plateau.pions[i][j]==Pion::white()) {
				white.blit(surf,100+((int)i*60),(int)j*60);
				blanc++;
			}
		}
	}
	if(plateau.gameFinished()) {
		string aff = "Joueur: "
				+lexical_cast<string>(blanc)+" Ordinateur: "
				+lexical_cast<string>(noir);
		surface text = thefont.render_shaded(aff,color::cyan(),color::grey());
			text.blit(surf,(surf.get_width()/2)-(text.get_width()/2)
				,(surf.get_height()/2)-(text.get_height()/2));
	}

	surf.flip();
}


Case Renderer::getCaseByCoordinate(int x,int y) {
	if(x<100 || x>700 || y <0 || y > 600) {
		throw othelloException();
	}
	Case tcase;
	tcase.x=(x-100)/60;
	tcase.y=y/60;
	return tcase;
}
