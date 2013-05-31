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

#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include <list>

namespace minmax {

#define INFINI 100000000

	template <typename T>
	float minimax(T& p,int recurse,float a=-INFINI,float b=INFINI) {
		if(recurse==0)
			return p.evaluate();
		vector<T> l;
		p.generateAll(l);
		if(l.empty())
			return p.evaluate();

		bool max = p.isMax();
		float alpha=-INFINI;
		float beta=INFINI;

		if(!max) {
			for( unsigned int i=0;i<l.size();i++ ) {
				float val=minimax(l[i],recurse-1,a,b<beta?b:beta);
				beta=beta<val?beta:val;
				if(a>=beta)
					return beta;
			}
			return beta;
		} else {
			for( unsigned int i=0;i<l.size();i++ ) {
				float val=minimax(l[i],recurse-1,a>alpha?a:alpha,b);
				alpha=alpha>val?alpha:val;
				if(alpha>=b)
					return alpha;
			}
			return alpha;
		}
	}

}

#endif
