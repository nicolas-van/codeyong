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

#ifndef MY_PLATEAU_HPP
#define MY_PLATEAU_HPP

#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class Pion;
struct Case;
class Plateau;

#define DIFFICULTY 3

void computerPlay(Plateau& plat,Pion& p);

class othelloException : public std::runtime_error {
public:
	othelloException() : std::runtime_error("othelloException") {};
	othelloException(std::string msg) : std::runtime_error(msg.c_str()) {};
};

class Plateau {
public:
	vector<vector<Pion> > pions;
	/**
		Initialise un plateau avec 4 pions.
	*/
	Plateau();
	/**
		Equivalent de putPion mais dans un constructeur.
	*/
	Plateau(Plateau& plat,Case& c,Pion& p);
	/**
		Crée un fork du plateau en y placant un nouveau pion.
	*/
	Plateau putPion(Case& c,Pion& p);
	/**
		V�rifie qu'un joueur a la possibilit� de jouer.
	*/
	bool canDoCoup(Pion p);
	/**
		V�rifie qu'aucun des joueurs n'a la possibilit� de jouer.
	*/
	bool gameFinished();

	/**
		Calcule le nombre de pions pris par un coup.
	*/
	int getNbrPionPris(Case tcase,Pion p);
	/**
		Calcule le nombre de pions pris par un coup dans
		une direction donn�e.
	*/
	int getNbrByDirection(Case tcase,Pion p,int direction);
};

class Pion {
private:
	Pion(int v){value=v;}
	int value;
	static Pion sblack;
	static Pion swhite;
	static Pion sempty;
public:
	Pion(){value=0;}
	static Pion& black() {return sblack;}
	static Pion& white() {return swhite;}
	static Pion& empty() {return sempty;}
	bool operator==(Pion o) {
		return this->value==o.value?true:false;
	}
	bool operator!=(Pion o) {
		return !(*this==o);
	}
	Pion operator!() {
		if(*this==black())
			return white();
		if(*this==white())
			return black();
		throw othelloException();
	}
	bool inverse(Pion & o) {
		if((*this==white() && o==black()) || (*this==black() && o==white()))
			return true;
		return false;
	}
};

struct Case {
	Case() {x=0;y=0;}
	Case(int x,int y) {this->x=x;this->y=y;}
	int x;
	int y;
};

#endif

