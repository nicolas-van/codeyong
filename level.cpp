
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

#include "level.hpp"

namespace log {

    const level level::off(level::_OFF_INT,"OFF");
    const level level::fatal(level::_FATAL_INT,"FATAL");
    const level level::error(level::_ERROR_INT,"ERROR");
    const level level::warning(level::_WARNING_INT,"WARNING");
    const level level::info(level::_INFO_INT,"INFO");
    const level level::debug(level::_DEBUG_INT,"DEBUG");
    const level level::trace(level::_TRACE_INT,"TRACE");
    const level level::all(level::_ALL_INT,"ALL");

}
