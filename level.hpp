
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

#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include <string>
#include <climits>

namespace log {

    class level {

        private:

        static const unsigned int _OFF_INT=UINT_MAX ;
        static const unsigned int _FATAL_INT=50000;
        static const unsigned int _ERROR_INT=40000;
        static const unsigned int _WARNING_INT=30000;
        static const unsigned int _INFO_INT=20000;
        static const unsigned int _DEBUG_INT=10000;
        static const unsigned int _TRACE_INT=5000;
        static const unsigned int _ALL_INT=0;

        unsigned int _level_int;
        std::string _name;

        public:

        static const level off;
        static const level fatal;
        static const level error;
        static const level warning;
        static const level info;
        static const level debug;
        static const level trace;
        static const level all;

        level() {
            *this=level(_ALL_INT,"ALL");
        }

        level(unsigned int level_int,const std::string& name) {
            _level_int = level_int;
            _name = name;
        }

        unsigned int level_int() const {
            return _level_int;
        }
        void level_int(unsigned int level_int) {
            _level_int = level_int;
        }
        const std::string& name() const {
            return _name;
        }
        void name(const std::string& name) {
            _name = name;
        }
        bool operator==(const level& o) const {
            return _level_int==o._level_int;
        }
        bool operator!=(const level& o) const {
            return _level_int!=o._level_int;
        }
        bool operator<(const level& o) const {
            return _level_int<o._level_int;
        }
        bool operator>(const level& o) const {
            return _level_int>o._level_int;
        }
        bool operator<=(const level& o) const {
            return _level_int<=o._level_int;
        }
        bool operator>=(const level& o) const {
            return _level_int>=o._level_int;
        }
    };
}

#endif

