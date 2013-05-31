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
#include "Plateau.hpp"

#include <list>
#include <utility>
#include <boost/random.hpp>
#include <ctime>
#include "Minimax.hpp"

Pion Pion::sblack(1);
Pion Pion::swhite(-1);
Pion Pion::sempty(0);

void inline incrementByDirection(int& x, int & y, int direction);

void getNexts(Plateau& plat,Pion& pion,list<Plateau>& l);
float evaluateForReal(Plateau& plat,Pion& pion);
float evaluateByPosition(Plateau& plat,Pion & pion,bool max,int recurse);
pair<Plateau,float> getBestEvaluation(list<Plateau>& lplat,Pion & pion,bool max,int recurse);

struct PNoeud {
	Plateau plat;
	Pion computer;
	bool max;

	PNoeud(Plateau& plateau,Case& c,Pion& p,Pion& computer,bool max)
		: plat(plateau,c,p),computer(computer),max(max) {};

	PNoeud()
		: max(true) {};

	bool isMax() {
		return max;
	}

	void generateAll(vector<PNoeud>& l,bool elseOther=true) {
		PNoeud& n= *this;
		Pion pion = n.max?n.computer:!n.computer;
		for(size_t i=0;i<n.plat.pions.size();i++) {
			for(size_t j=0;j<n.plat.pions[i].size();j++) {
				try {
					Case tmpc((int)i,(int)j);
					l.push_back(PNoeud(n.plat,tmpc,pion,n.computer,!n.max));
				} catch (othelloException&) {
				}
			}
		}
		if(l.empty() && elseOther) {
			n.max = !n.max;
			generateAll(l,false);
		}
	}

	float evaluate() {
		PNoeud& n= *this;
		int nbrc=0;
		int nbrcb=0;
		int nbrp=0;
		int nbrpb=0;
		int nbrv=0;
		for(size_t i=0;i<n.plat.pions.size();i++) {
			for(size_t j=0;j<n.plat.pions[i].size();j++) {
				if(n.plat.pions[i][j]==n.computer) {
					nbrc++;
					if((i==0 && j==0) || (i==0 && j==n.plat.pions[i].size()-1)
						|| (i==n.plat.pions.size()-1 && j==0)
						|| (i==n.plat.pions.size()-1 && j==n.plat.pions[i].size()-1) )
						nbrcb+=50;
				}
				else if(n.plat.pions[i][j]==!n.computer) {
					nbrp++;
					if((i==0 && j==0) || (i==0 && j==n.plat.pions[i].size()-1)
						|| (i==n.plat.pions.size()-1 && j==0)
						|| (i==n.plat.pions.size()-1 && j==n.plat.pions[i].size()-1) )
						nbrpb+=50;
				}
				else
					nbrv++;
			}
		}
		if(nbrv==0 || nbrc==0 || nbrp==0)
			return (float)(nbrc>nbrp?1000:-1000);
		return (float)(nbrc+nbrcb-nbrp-nbrpb);
	}
};


void computerPlay(Plateau& plat,Pion& pion) {
	PNoeud pn;
	pn.plat=plat;
	pn.computer=pion;
	pn.max=true;
	vector<PNoeud> l;
	pn.generateAll(l);
	vector< pair<float,vector<PNoeud>::iterator> > results;
	
	for(vector<PNoeud>::iterator it=l.begin();it!=l.end();it++) {
		float val=minmax::minimax(*it,DIFFICULTY);
		pair<float,vector<PNoeud>::iterator> tmpPair(val,it);
		if(results.empty()) {
			results.push_back(tmpPair);
			continue;
		}
		if(val==results[0].first)
			results.push_back(tmpPair);
		else if(val>results[0].first) {
			results.clear();
			results.push_back(tmpPair);
		}
	}
	boost::minstd_rand ran(clock());
	size_t choice=ran()%results.size();
	plat = results[choice].second->plat;
}

Plateau::Plateau() {
	pions = vector< vector<Pion> >(10);
	vector<Pion> vec(10);
	fill(vec.begin(),vec.end(),Pion::empty());
	fill(pions.begin(),pions.end(),vec);

	pions[4][4]=Pion::black();
	pions[5][5]=Pion::black();
	pions[4][5]=Pion::white();
	pions[5][4]=Pion::white();
}

Plateau::Plateau(Plateau& plat,Case& c,Pion& p) {
	pions = plat.pions;
	if((this->pions[c.x])[c.y] != Pion::empty())
		throw othelloException();
	int total=0;
	for(int i=0;i<8;i++) {
		int nbr = this->getNbrByDirection(c,p,i);
		total+=nbr;
		int tx=c.x;
		int ty=c.y;
		for(int j=0;j<nbr;j++) {
			incrementByDirection(tx,ty,i);
			this->pions[tx][ty] = p;
		}
	}
	if(total==0)
		throw othelloException();
	this->pions[c.x][c.y] = p;
}

Plateau Plateau::putPion(Case& c,Pion& p) {
	return Plateau(*this,c,p);
}


bool Plateau::canDoCoup(Pion p) {
	for(size_t i=0;i<pions.size();i++) {
		for(size_t j=0;j<pions[i].size();j++) {
			if(this->getNbrPionPris(Case((int)i,(int)j),p)>0)
				return true;
		}
	}
	return false;
}

bool Plateau::gameFinished() {
	if(canDoCoup(Pion::white()) || canDoCoup(Pion::black()))
		return false;
	return true;
}

int Plateau::getNbrPionPris(Case tcase,Pion p) {
	if(this->pions[tcase.x][tcase.y] != Pion::empty())
		return 0;
	int gcpt=0;
	for(int i=0;i<8;i++) {
		gcpt+=this->getNbrByDirection(tcase,p,i);
	}
	return gcpt;
}

int Plateau::getNbrByDirection(Case tcase,Pion p, int direction) {
	int x=tcase.x;
	int y=tcase.y;
	int cpt=0;
	bool bord=false;
	while(true) {
		incrementByDirection(x,y,direction);
		if(!(x>=0 && x<10 && y>=0 && y<10) || pions[x][y]==Pion::empty()) {
			bord=true;
			break;
		}
		else if(pions[x][y].inverse(p))
			cpt++;
		else
			break;
	}
	if(bord)
		return 0;
	return cpt;
}

void incrementByDirection(int& x, int & y, int direction) {
	switch(direction) {
		case 0:
			y--;
			break;
		case 1:
			y--;
			x++;
			break;
		case 2:
			x++;
			break;
		case 3:
			x++;
			y++;
			break;
		case 4:
			y++;
			break;
		case 5:
			y++;
			x--;
			break;
		case 6:
			x--;
			break;
		case 7:
			x--;
			y--;
			break;
	}
}

